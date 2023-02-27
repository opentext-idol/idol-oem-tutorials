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
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class EduceRedact {

    private static final Logger LOG = Logger.getLogger(EduceRedact.class.getName());

	private static boolean USE_IDOL_OEM_ENCRYPTION = true;
	private static final String IDOL_OEM_ENCRYPTION_KEY_ENV_VAR = "ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY";
	private static final String IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE = "REPLACE_WITH_MY_LONG_KEY_STRING";
	private static final String IDOL_OEM_ENCRYPTION_KEY = IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE;

	static class Args {
        static final int EXPECTED_NUM_ARGS = 5;
		final String aciHost;
		final Integer aciPort;
		final String mode;
		final String entities;
		final String text;
		
		//Prints program usage information to standard output
		private void displayusageinfo()
		{
			System.console().printf("Usage: educeRedact e|r <HOSTNAME/IP> <ACI_PORT_#> <ENTITIES_CSV> <TEXT>\n");
			System.console().printf("Parameters:\n");
			System.console().printf("    e|r	Selection mode e(duce) or r(redact).\n");
			System.console().printf("    <HOSTNAME/IP>	Hostname / IP address of ACI service.\n");
			System.console().printf("    <ACI_PORT_#>	ACI port number of ACI service.\n");
			System.console().printf("    <ENTITIES_CSV>	CSV of entities to use.\n");
			System.console().printf("    <TEXT>	Text to process.\n");
		}


		Args(final String[] stringArgs) throws IllegalArgumentException {
			if (stringArgs.length != EXPECTED_NUM_ARGS) {
				displayusageinfo();
				throw new IllegalArgumentException("Wrong number of arguments (5 required).");
			}
			
			aciHost = stringArgs[1];
			aciPort = Integer.parseInt(stringArgs[2]);
			mode = stringArgs[0];
			entities = stringArgs[3];
			text = stringArgs[4];
			
			System.console().printf("ACI Host: %s\n", aciHost);
			System.console().printf("ACI Port: %d\n", aciPort);
			System.console().printf("Mode: %s\n", mode);
			System.console().printf("Entities: %s\n", entities);
			System.console().printf("Text: %s\n", text);
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

	private BteaEncryptionCodec get_encryptionCodec(String key)
	{
		BteaEncryptionCodec encryptionCodec = null;
		
		try {
			LOG.info("OEM encryption key(s): " + key);
			Pattern pattern = Pattern.compile("(\\d*),(\\d*),(\\d*),(\\d*)", Pattern.CASE_INSENSITIVE);
			Matcher matcher = pattern.matcher(key);
			if (matcher.find())
			{
				long[] keys = new long[4];
				keys[0] = Long.parseLong(matcher.group(1));
				keys[1] = Long.parseLong(matcher.group(2));
				keys[2] = Long.parseLong(matcher.group(3));
				keys[3] = Long.parseLong(matcher.group(4));
		
				encryptionCodec = new BteaEncryptionCodec(keys);
			} else {
				encryptionCodec = new BteaEncryptionCodec(key);
			}
		} catch(Exception e) {
			LOG.severe("Unable to set up API encryption.\n");
			throw e;
		} finally {
			return encryptionCodec;
		}
	}
	
    private void educe_redact(String[] args) throws Exception
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
						LOG.warning("Don't forget to correctly set " + IDOL_OEM_ENCRYPTION_KEY_ENV_VAR);
						throw new Exception("Invalid OEM encryption key");
					} else {
						encryptionCodec = get_encryptionCodec(key);
					}
				} else {
					LOG.info("Using OEM encryption key from constant IDOL_OEM_ENCRYPTION_KEY");
					if (IDOL_OEM_ENCRYPTION_KEY.equals(IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE)) {
						LOG.warning("Don't forget to correctly set constant: IDOL_OEM_ENCRYPTION_KEY");
						throw new Exception("Invalid OEM encryption key");
					} else {
						encryptionCodec = get_encryptionCodec(IDOL_OEM_ENCRYPTION_KEY);
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
			// Get command to execute
			String command;
			if ("e".equalsIgnoreCase(parsedArgs.mode))
			{
				command = "EDUCEFROMTEXT";
			}
			else if ("r".equalsIgnoreCase(parsedArgs.mode))
			{
				command = "REDACTFROMTEXT";
			} else {
				throw new Exception("Invalid mode");
			}

			// Set action parameters
			parameters = new ActionParameters(command);
			parameters.add("entities", parsedArgs.entities);
			parameters.add("text", parsedArgs.text);
			parameters.add("responseFormat", "xml");	// TODO: Switch to JSON by using JSON response handler vs XML
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
		} catch(Exception e) {
			LOG.severe("Unable to handle response.\n");
			throw e;
		}
    }

    public static void main(String[] args) throws Exception
    {
		LOG.info("Program loaded");

        EduceRedact obj = new EduceRedact();
        try {
            obj.educe_redact(args);
        } catch (Exception e) {
            LOG.severe("Scary exception happened: " + e.getMessage());
            throw e;
        }
    }	
}
