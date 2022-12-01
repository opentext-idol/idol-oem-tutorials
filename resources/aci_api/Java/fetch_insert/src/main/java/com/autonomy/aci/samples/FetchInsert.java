package com.autonomy.aci.samples;

import com.autonomy.aci.client.services.AciServiceException;
import com.autonomy.aci.client.services.AciErrorException;
import com.autonomy.aci.client.services.AciService;
import com.autonomy.aci.client.services.impl.AciServiceImpl;
import com.autonomy.aci.client.services.impl.DocumentProcessor;
import com.autonomy.aci.client.transport.AciParameter;
import com.autonomy.aci.client.transport.AciServerDetails;
import com.autonomy.aci.client.transport.InputStreamActionParameter;
import com.autonomy.aci.client.transport.impl.AciHttpClientImpl;
import com.autonomy.aci.client.transport.impl.BteaEncryptionCodec;
import com.autonomy.aci.client.util.ActionParameters;
import org.apache.http.impl.client.HttpClientBuilder;
import org.w3c.dom.Document;
import java.io.StringWriter;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathFactory;
import org.xml.sax.SAXException;
import java.util.logging.Logger;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FetchInsert {

    private static final Logger LOG = Logger.getLogger(FetchInsert.class.getName());

	private static boolean USE_IDOL_OEM_ENCRYPTION = true;
	private static final String IDOL_OEM_ENCRYPTION_KEY_ENV_VAR = "ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY";
	private static final String IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE = "REPLACE_WITH_MY_LONG_KEY_STRING";
	private static final String IDOL_OEM_ENCRYPTION_KEY = IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE;

	static class Args {
        static final int EXPECTED_NUM_ARGS = 4;
		static final int MAX_INSERT_XML_SIZE_BYTES = 10000;

		final String aciHost;
		final Integer aciPort;
		final String taskName;
		final String insertXML_file;
		
		//Prints program usage information to standard output
		private void displayusageinfo()
		{
			System.console().printf("Usage: FetchInsert <HOSTNAME/IP> <ACI_PORT_#> <TASK_NAME> <INSERT_XML_FILE>\n");
			System.console().printf("Parameters:\n");
			System.console().printf("    <HOSTNAME/IP>	Hostname / IP address of ACI service.\n");
			System.console().printf("    <ACI_PORT_#>	ACI port number of ACI service.\n");
			System.console().printf("    <TASK_NAME>	Fetch task name.\n");
			System.console().printf("    <INSERT_XML_FILE>	Insert XML file.\n");
		}


		Args(final String[] stringArgs) throws IllegalArgumentException {
			if (stringArgs.length != EXPECTED_NUM_ARGS) {
				displayusageinfo();
				throw new IllegalArgumentException("Wrong number of arguments (4 required).");
			}
			
			aciHost = stringArgs[0];
			aciPort = Integer.parseInt(stringArgs[1]);
			taskName = stringArgs[2];
			insertXML_file = stringArgs[3];

			System.console().printf("ACI Host: %s\n", aciHost);
			System.console().printf("ACI Port: %d\n", aciPort);
			System.console().printf("Task Name: %s\n", taskName);
			System.console().printf("InsertXML file: %s\n", insertXML_file);
		}
	}

	private String get_insertXML_file(String pathStr) throws Exception
	{
		String insertXML;

		try {
			insertXML = new String(Files.readAllBytes(Paths.get(pathStr)));
		} catch(Exception e) {
			LOG.severe("Unable read insert.\n");
			throw e;
		}

		return insertXML;
	}

	private static String getStringFromDocument(Document doc) throws Exception
	{
		StringWriter writer = new StringWriter();
		StreamResult result = new StreamResult(writer);
		
		TransformerFactory tf = TransformerFactory.newInstance();
		Transformer transformer = tf.newTransformer();
		transformer.setOutputProperty(OutputKeys.INDENT, "yes");
		transformer.setOutputProperty(OutputKeys.ENCODING, "UTF-8");
		transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");		
		transformer.transform(new DOMSource(doc), result);

		return writer.toString();
	}

    private void fetch_insert(String[] args) throws Exception
	{
		Args parsedArgs;
		final AciService aciService;
		final ActionParameters parameters;
		final Document response;

		try {
			parsedArgs = new Args(args);
		} catch(Exception e) {
			LOG.severe("Unable to parse arguments.\n");
			throw e;
		}
		
		try {
			final AciServerDetails aciServerDetails = new AciServerDetails(parsedArgs.aciHost, parsedArgs.aciPort);
			final BteaEncryptionCodec encryptionCodec;

			// Initialize OEM licensing
			if (USE_IDOL_OEM_ENCRYPTION)
			{
				String key = System.getenv(IDOL_OEM_ENCRYPTION_KEY_ENV_VAR);

				if (key != null)
				{
					LOG.info("Using OEM encryption key from environment variable: " + IDOL_OEM_ENCRYPTION_KEY_ENV_VAR);
					if (key.equals(IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE)) {
						LOG.info("Don't forget to correctly set " + IDOL_OEM_ENCRYPTION_KEY_ENV_VAR);
						throw new Exception("Invalid OEM encryption key");
					} else {
						encryptionCodec = new BteaEncryptionCodec(key);
					}
				} else {
					LOG.info("Using OEM encryption key from constant IDOL_OEM_ENCRYPTION_KEY");
					if (IDOL_OEM_ENCRYPTION_KEY.equals(IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE)) {
						LOG.info("Don't forget to correctly set constant: IDOL_OEM_ENCRYPTION_KEY");
						throw new Exception("Invalid OEM encryption key");
					} else {
						encryptionCodec = new BteaEncryptionCodec(IDOL_OEM_ENCRYPTION_KEY);
					}
				}

				aciServerDetails.setEncryptionCodec(encryptionCodec);				
			}
		
			aciService = new AciServiceImpl(new AciHttpClientImpl(HttpClientBuilder.create().build()), aciServerDetails);			
		} catch(Exception e) {
			LOG.severe("Unable to set up AciService.\n");
			throw e;
		}

		try {
			// get insertXML data
			String insertXML = get_insertXML_file(parsedArgs.insertXML_file);
			
			// Set action parameters
			parameters = new ActionParameters("FETCH");
			//parameters = new ActionParameters("INGEST");
			parameters.add("fetchAction", "insert");
			parameters.add("configSection", parsedArgs.taskName);
			parameters.add("destination", insertXML);
			parameters.add("responseFormat", "xml");
		} catch(Exception e) {
			LOG.severe("Unable to set up ActionParameters.\n");
			throw e;
		}

		try {
			LOG.info("Executing action...");

			response = aciService.executeAction(parameters, new DocumentProcessor());
		} catch(Exception e) {
			LOG.severe("Unable to execute action.\n");
			throw e;
		}

		try {
			LOG.info("Handling response...");

			String responseStr = getStringFromDocument(response);
			System.console().printf("\n" + responseStr + "\n");
			
			// Get <response> and print it
			final XPath xpath = XPathFactory.newInstance().newXPath();

			System.console().printf("response: %s\n", xpath.evaluate("/autnresponse/response", response));

			System.console().printf("Token: %s\n", xpath.evaluate("/autnresponse/responsedata/token", response));
		} catch(Exception e) {
			LOG.severe("Unable to handle response.\n");
			throw e;
		}
    }

    public static void main(String[] args) throws Exception
    {
		LOG.info("Program loaded");

        FetchInsert obj = new FetchInsert();

        try {
            obj.fetch_insert(args);
        } catch(Exception e) {
            LOG.severe("Scary exception happened: " + e.getMessage());
            throw e;
        }
    }
}
