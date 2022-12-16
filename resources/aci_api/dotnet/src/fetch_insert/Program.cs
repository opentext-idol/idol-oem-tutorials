using System;
using System.Text;
using System.Xml;
using Autonomy.Aci;

namespace fetchInsert
{
    class Program
    {
        private const Boolean USE_IDOL_OEM_ENCRYPTION = true;
        private const String IDOL_OEM_ENCRYPTION_KEY_ENV_VAR = "ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY";
        private const String IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE = "REPLACE_WITH_MY_LONG_KEY_STRING";
        private const String IDOL_OEM_ENCRYPTION_KEY = IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE;

        private const int EXPECTED_NUM_ARGS = 4;

        static void DisplayUsageInfo()
        {
            Console.WriteLine("Usage: fetchInsert <HOSTNAME/IP> <ACI_PORT_#> <TASK_NAME> <INSERT_XML_FILE>\n");
            Console.WriteLine("Parameters:\n");
            Console.WriteLine("    <HOSTNAME/IP>    Hostname / IP address of ACI service.\n");
            Console.WriteLine("    <ACI_PORT_#>     ACI port number of ACI service.\n");
            Console.WriteLine("    <TASK_NAME>      Fetch task name.\n");
            Console.WriteLine("    <INSERT_XML_FILE>      Insert XML file.\n");
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

        static void FetchInsert(String[] args)
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
                connection = AciClient.CreateBteaConnection(args[0], Int32.Parse(args[1]), key);
            }
            else
            {
                connection = AciClient.CreateUnsecuredConnection(args[0], Int32.Parse(args[1]));
            }
			
			// get insertXML data
			String insertXML = System.IO.File.ReadAllText(args[3]);

            Command fetch = new Command("FETCH");
            //Command fetch = new Command("INGEST");
            fetch.Set("fetchAction", "insert");
            fetch.Set("configSection", args[2]);
            fetch.Set("insertXML", insertXML);
            fetch.Set("responseFormat", "xml");

            Console.WriteLine("\nExecuting action...");

            try
            {
                response = connection.Execute(fetch);
            }
            catch (Exception e)
            {
                Console.WriteLine("\nUnable to execute action.\n");
                throw (e);
            }

            Console.WriteLine("\nHandling response...\n");

            Console.WriteLine(GetStringFromDocument(response));

            // Get <response> and print it
            XmlNamespaceManager namespaces =
                new XmlNamespaceManager(response.Data.NameTable);
            namespaces.AddNamespace(
                "autn", "http://schemas.autonomy.com/aci/");
            XmlNode root = response.Data.DocumentElement;

            Console.WriteLine("\nresponse: {0}\n", root.SelectSingleNode("/autnresponse/response").InnerText);

            Console.WriteLine("Token: {0}\n", root.SelectSingleNode("/autnresponse/responsedata/token").InnerText);
        }
        static void Main(string[] args)
        {
            Console.WriteLine("Program loaded.\n");

            if (args.Length != EXPECTED_NUM_ARGS)
            {
                Console.WriteLine("Error: Wrong number of arguments (4 required).\n");
                DisplayUsageInfo();
                Environment.Exit(1);
            }

            Console.WriteLine("ACI Host: {0}", args[0]);
            Console.WriteLine("ACI Port: {0}", args[1]);
            Console.WriteLine("Task Name: {0}", args[2]);
            Console.WriteLine("InsertXML file: {0}", args[3]);

            try
            {
                FetchInsert(args);
            }
            catch (Exception e)
            {
                Console.WriteLine("Scary exception happened: " + e.Message);
                Environment.Exit(1);
            }

        }
    }
}

