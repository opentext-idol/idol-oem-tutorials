using System;
using System.Text;
using System.Xml;
using Autonomy.Aci;

namespace educeRedact
{
    class Program
    {
        private const Boolean USE_IDOL_OEM_ENCRYPTION = true;
        private const String IDOL_OEM_ENCRYPTION_KEY_ENV_VAR = "ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY";
    	private const String IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE = "REPLACE_WITH_MY_LONG_KEY_STRING";
	    private const String IDOL_OEM_ENCRYPTION_KEY = IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE;

		private const Int16 EXPECTED_NUM_ARGS = 5;
		
        static void DisplayUsageInfo()
        {
            Console.WriteLine("Usage: educeRedact e|r <HOSTNAME/IP> <ACI_PORT_#> <ENTITIES_CSV> <TEXT>\n");
            Console.WriteLine("Parameters:\n");
            Console.WriteLine("    e|r              Selection mode e(duce) or r(redact).\n");
            Console.WriteLine("    <HOSTNAME/IP>    Hostname / IP address of ACI service.\n");
            Console.WriteLine("    <ACI_PORT_#>     ACI port number of ACI service.\n");
            Console.WriteLine("    <ENTITIES_CSV>   CSV of entities to use.\n");
            Console.WriteLine("    <TEXT>           Text to process.\n");
        }

        static String GetStringFromDocument(Response response)
        {
            var stringBuilder = new StringBuilder();

            var settings = new XmlWriterSettings();
            settings.OmitXmlDeclaration = true;
            settings.Indent = true;
            settings.NewLineOnAttributes = true;

            using (var xmlWriter = XmlWriter.Create(stringBuilder, settings))
            {
                response.Data.Save(xmlWriter);
            }

            return stringBuilder.ToString();
        }

        static void EduceRedact(String[] args)
        {
            IConnection connection;
            Response response;

            if (USE_IDOL_OEM_ENCRYPTION)
            {
                string key = Environment.GetEnvironmentVariable(IDOL_OEM_ENCRYPTION_KEY_ENV_VAR);

                if (key != null)
                {
                    Console.WriteLine("\nUsing OEM encryption key from environment variable: " + IDOL_OEM_ENCRYPTION_KEY_ENV_VAR);
                    if (key.Equals(IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE))
                    {
                        Console.WriteLine("\nDon't forget to correctly set " + IDOL_OEM_ENCRYPTION_KEY_ENV_VAR);
                        throw new Exception("Invalid OEM encryption key");
                    }
                }
                else
                {
                    Console.WriteLine("\nUsing OEM encryption key from constant IDOL_OEM_ENCRYPTION_KEY");
                    if (IDOL_OEM_ENCRYPTION_KEY.Equals(IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE))
                    {
                        Console.WriteLine("\nDon't forget to correctly set constant: IDOL_OEM_ENCRYPTION_KEY");
                        throw new Exception("Invalid OEM encryption key");
                    }
                }
                connection = AciClient.CreateBteaConnection(args[1], Int32.Parse(args[2]), key);
            }
            else 
            {
                connection = AciClient.CreateUnsecuredConnection(args[1], Int32.Parse(args[2]));
            }

            // Get command to execute
            String command;
            if (string.Equals("e", args[0], StringComparison.OrdinalIgnoreCase))
            {
                command = "EDUCEFROMTEXT";
            } else if (string.Equals("r", args[0], StringComparison.OrdinalIgnoreCase))
            {
                command = "REDACTFROMTEXT";
            } else {
                throw new Exception("Invalid mode");
            }

            Command educeRedact = new Command(command);
            educeRedact.Set("entities", args[3]);
            educeRedact.Set("text", args[4]);
            educeRedact.Set("responseFormat", "xml");

            Console.WriteLine("\nExecuting action...");

            try
            {
                response = connection.Execute(educeRedact);
            } catch (Exception e)
            {
                Console.WriteLine("\nUnable to execute action.\n");
                throw (e);
            }

            Console.WriteLine("\nHandling response...\n");

            Console.WriteLine(GetStringFromDocument(response));
        }
        static void Main(string[] args)
        {
            Console.WriteLine("Program loaded.\n");

            if (args.Length != EXPECTED_NUM_ARGS)
            {
                Console.WriteLine("Error: Wrong number of arguments (5 required).\n");
                DisplayUsageInfo();
                Environment.Exit(1);
            }

            Console.WriteLine("ACI Host: {0}", args[1]);
            Console.WriteLine("ACI Port: {0}", args[2]);
            Console.WriteLine("Mode: {0}", args[0]);
            Console.WriteLine("Entities: {0}", args[3]);
            Console.WriteLine("Text: {0}", args[4]);

            try
            {
                EduceRedact(args);
            }
            catch (Exception e)
            {
                Console.WriteLine("Scary exception happened: " + e.Message);
                Environment.Exit(1);
            }

        }
    }
}
