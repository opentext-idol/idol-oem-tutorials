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

import java.util.Optional;

public class QueueinfoGetstatus {

	private static final Logger LOG = Logger.getLogger(QueueinfoGetstatus.class.getName());
	private static boolean USE_IDOL_OEM_ENCRYPTION = true;
	private static final String IDOL_OEM_ENCRYPTION_KEY_ENV_VAR = "ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY";
	private static final String IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE = "REPLACE_WITH_MY_LONG_KEY_STRING";
	private static final String IDOL_OEM_ENCRYPTION_KEY = IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE;

	static class Args {
        static final int EXPECTED_MIN_NUM_ARGS = 3;
        static final int EXPECTED_MAX_NUM_ARGS = 4;
		final String aciHost;
		final Integer aciPort;
		final String queueName;
		Optional<String> token = Optional.empty();
		
		//Prints program usage information to standard output
		private void displayusageinfo()
		{
			System.console().printf("Usage: QueueinfoGetstatus <HOSTNAME/IP> <ACI_PORT_#> <QUEUE_NAME> [<TOKEN>]\n");
			System.console().printf("Parameters:\n");
			System.console().printf("    <HOSTNAME/IP>	Hostname / IP address of ACI service.\n");
			System.console().printf("    <ACI_PORT_#>	ACI port number of ACI service.\n");
			System.console().printf("    <QUEUE_NAME>	Queue name - e.g. fetch.\n");
			System.console().printf("    [<TOKEN>]		Optional. Asynchronous action token.\n");
		}


		Args(final String[] stringArgs) throws IllegalArgumentException {
			if ((stringArgs.length < EXPECTED_MIN_NUM_ARGS) && (stringArgs.length > EXPECTED_MAX_NUM_ARGS)) {
				displayusageinfo();
				throw new IllegalArgumentException("Wrong number of arguments (three required, fourth is optional).");
			}
			
			aciHost = stringArgs[0];
			aciPort = Integer.parseInt(stringArgs[1]);
			queueName = stringArgs[2];

			System.console().printf("ACI Host: %s\n", aciHost);
			System.console().printf("ACI Port: %d\n", aciPort);
			System.console().printf("Queue Name: %s\n", queueName);
			if (stringArgs.length == EXPECTED_MAX_NUM_ARGS)
			{
				token = Optional.of(stringArgs[3]);
				System.console().printf("Token: %s\n", token);
			}
		}
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

    private void queueinfo_getstatus(String[] args) throws Exception
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
			// Set action parameters
			parameters = new ActionParameters("QUEUEINFO");
			parameters.add("queueAction", "getStatus");
			parameters.add("queueName", parsedArgs.queueName);
			if (parsedArgs.token.isPresent())
			{
				parameters.add("token", parsedArgs.token.get());
			}
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

			if (parsedArgs.token.isPresent())
			{
				System.console().printf("Queue Name: %s.\nToken: %s.\nStatus: %s\n", parsedArgs.queueName, parsedArgs.token.get(), xpath.evaluate("/autnresponse/responsedata/actions/action/status", response));
			}
		} catch(Exception e) {
			LOG.severe("Unable to handle response.\n");
			throw e;
		}
    }

    public static void main(String[] args) throws Exception
    {
		LOG.info("Program loaded");

		QueueinfoGetstatus obj = new QueueinfoGetstatus();

        try {
            obj.queueinfo_getstatus(args);
        } catch(Exception e) {
            LOG.severe("Scary exception happened: " + e.getMessage());
            throw e;
        }
    }	
}
