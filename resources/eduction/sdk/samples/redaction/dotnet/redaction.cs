using System;
using System.IO;
using System.Collections.Generic;
using Eduction;

class RedactionSample
{
    private static void displayusageinfo()
    {
        Console.WriteLine("Eduction C# SDK Sample");
        Console.WriteLine("Usage: " + System.AppDomain.CurrentDomain.FriendlyName + " <configpath> <documentpath> <outputfile>");
        Console.WriteLine("\t<configpath>\tPath to the config file containing engine settings.");
        Console.WriteLine("\t<documentpath>\tPath to the document to be parsed.");
        Console.WriteLine("\t<outputfile>\tPath to the output file, where results will be written.");
    }

    private static string licensekey()
    {
        var assem = typeof(RedactionSample).Assembly;
        using (Stream stream = assem.GetManifestResourceStream("edk.licensekey.dat"))
        using (var reader = new StreamReader(stream))
		using (Stream versionStream = assem.GetManifestResourceStream("edk.versionkey.dat"))
        using (var versionReader = new StreamReader(versionStream))
        {
            return licenseReader.ReadToEnd() + ";" + versionReader.ReadToEnd();
        }
    }

    private static bool checkargs(string[] args)
    {
        if (args.Length != 3)
        {
            Console.WriteLine("Error: program requires three arguments.");
            displayusageinfo();
            return false;
        }
        return true;
    }

    static int Main(string[] args)
    {
        if (!checkargs(args))
        {
            return -1;
        }
        Console.WriteLine("Parameters valid.");

        try
        {
            using (ITextExtractionEngine engine = EDKFactory.FromLicenseKey(licensekey()).GetTextExtractionEngine(args[0]))
            {
                Console.WriteLine("Engine created.");
                using (StreamWriter output_stream = new StreamWriter(args[2]))
                {
                    Console.WriteLine("Printing results to " + args[2] + "...");
                    string input_text = File.ReadAllText(args[1]);
                    string redacted_text = engine.RedactText(input_text);
                    Dictionary<string, int> match_counts = engine.GetMatchCounts(input_text);
                    output_stream.Write(redacted_text);
                    foreach(KeyValuePair<string, int> entityname_matchcount in match_counts)
                    {
                        output_stream.Write("\n" + entityname_matchcount.Key + "," + entityname_matchcount.Value);
                    }
                }
            }
        }
        catch (EDKException ex)
        {
            Console.WriteLine(ex.ToString());
            return -2;
        }

        Console.WriteLine("Program completed without an error.\n");
        return 0;
    }

}
