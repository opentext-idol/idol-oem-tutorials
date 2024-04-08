using System;
using System.IO;
using Eduction;

class EductionFromConfigSample
{
    private const int CONFIG_IDX = 0;
    private const int DOC_IDX = 1;
    private const int OUTPUTFILE_IDX = 2;
    private const int MAXMATCHESPERDOC_IDX = 3;
    private const int MINSCORE_IDX = 4;
    private const int POSTPROCESSINGTHRESHOLD_IDX = 5;
    private const int OPTIONAL_PARAMS_IDX = 6;

    private static void displayusageinfo()
    {
        Console.WriteLine("Eduction C# SDK Sample");
        Console.WriteLine("Usage: " + System.AppDomain.CurrentDomain.FriendlyName + " <configpath> <documentpath> <outputfile>");
        Console.WriteLine("\t<configpath>\tPath to the config file containing engine settings.");
        Console.WriteLine("\t<documentpath>\tPath to the document to be parsed.");
        Console.WriteLine("\t<outputfile>\tPath to the output file, where results will be written.");
        Console.WriteLine("\t[<maxmatchesperdoc>]\t.Update the MaxMatchesPerDoc for the session. Setting to zero means no limit");
        Console.WriteLine("\t[<minscore>]\t.Update the MinScore for the session. Setting to -1 means no update.");
        Console.WriteLine("\t[<postprocessthreshold>]\t.Update the PostProcessThreshold for the session.");
        Console.WriteLine("\t[--limit <entity>=<limit> ...]\t.Set EntityMatchLimit for the session (can be repeated).");
    }

    private static bool checkargs(string[] args)
    {
        if (args.Length < 3)
        {
            Console.WriteLine("Error: program requires at least three arguments.");
            displayusageinfo(); 
            return false;
        }
        return true;
    }

    private static string licensekey()
    {
        var assem = typeof(EductionFromConfigSample).Assembly;
        using (Stream licenseStream = assem.GetManifestResourceStream("edk.licensekey.dat"))
        using (var licenseReader = new StreamReader(licenseStream))
        using (Stream versionStream = assem.GetManifestResourceStream("edk.versionkey.dat"))
        using (var versionReader = new StreamReader(versionStream))
        {
            return licenseReader.ReadToEnd() + ";" + versionReader.ReadToEnd();
        }
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
            using (ITextExtractionSession session = engine.GetSession())
            {
                Console.WriteLine("Engine and session created.");

                //Can set MaxMatchesPerDoc for a session for performance, overriding the config/engine setting
                //If the session has returned matches, it must be reset with session.resetInputText before the setting can be changed.
                //Setting to zero means no limit.
                if (args.Length > MAXMATCHESPERDOC_IDX)
                {
                    uint max_matches_per_doc;
                    if (UInt32.TryParse(args[MAXMATCHESPERDOC_IDX], out max_matches_per_doc))
                    {
                        session.SetMaxMatchesPerDoc(max_matches_per_doc);
                        Console.WriteLine("Session max matches per doc set to: " + max_matches_per_doc);
                    }
                    else
                    {
                        Console.WriteLine("Cannot convert session match matches per doc '{0}' to a UInt32.", args[3]);
                    }
                }

                //Can set MinScore for a session, overriding the config setting
                //If the session has returned matches, it must be reset with session.resetInputText before the setting can be changed.
                //Setting to -1 via the command line means do not update (useful if you want to just update the post-processing threshold).
                if (args.Length > MINSCORE_IDX)
                {
                    double min_score;
                    if (Double.TryParse(args[MINSCORE_IDX], out min_score))
                    {
                        if (min_score != -1)
                        {
                            session.SetMinScore(min_score);
                            Console.WriteLine("Session min score set to: " + min_score);
                        }
                    }
                    else
                    {
                        Console.WriteLine("Cannot convert session min score '{0}' to a Double.", args[4]);
                    }
                }

                //Can set PostProcessingThreshold for a session, overriding the config setting
                //If the session has returned matches, it must be reset with session.resetInputText before the setting can be changed.
                if (args.Length > POSTPROCESSINGTHRESHOLD_IDX)
                {
                    double post_processing_threshold;
                    if (Double.TryParse(args[POSTPROCESSINGTHRESHOLD_IDX], out post_processing_threshold))
                    {
                        session.SetPostProcessingThreshold(post_processing_threshold);
                        Console.WriteLine("Session post-processing threshold set to: " + post_processing_threshold);
                    }
                    else
                    {
                        Console.WriteLine("Cannot convert session post-processing threshold '{0}' to a Double.", args[5]);
                    }
                }

                if (args.Length > OPTIONAL_PARAMS_IDX)
                {
                    int ii = OPTIONAL_PARAMS_IDX;
                    while (ii < args.Length)
                    {
                        // Can set EntityMatchLimit for an entity for a session, overriding the config settings
                        // If the session has returned matches, it must be reset with session.resetInputText before the setting can be changed.
                        if (args[ii] == "--limit" && ii+1<args.Length)
                        {
                            ++ii;
                            string[] entity_limit = args[ii].Split("=");
                            if (2==entity_limit.Length)
                            {
                                session.SetEntityMatchLimit(entity_limit[0], Int32.Parse(entity_limit[1]));
                            }
                        }
                        ++ii;
                    }

                }
                //To limit the amount of text processed by the prefilter, set the 
                //PrefilterMaxReturnedBytes in the config or use the session method
                //(a prefilter task must be set)
                //ulong max_prefilter_bytes_per_doc = 0;
                //session.SetMaxPrefilterBytesPerDoc(max_prefilter_bytes_per_doc);

                DateTimeOffset now = (DateTimeOffset)DateTime.UtcNow;
                long now_millis = (long)(now.ToUnixTimeMilliseconds());
                session.SetStartTimePrecise(now_millis);
                Console.WriteLine("Session start time set to: " + now_millis);

                using (FileStream input_stream = File.OpenRead(args[1]))
                using (StreamWriter output_stream = new StreamWriter(args[2]))
                {
                    uint match_num = 0;
                    session.SetInputStream(input_stream);
                    Console.WriteLine("Input stream set for session");
                    Console.WriteLine("Printing results to " + args[2] + "...");
                    output_stream.Write("{\n");
                    output_stream.Write("\t\"matches\": [\n");
                    foreach (IExtractionMatch match in session)
                    {
                        int component_num = 0;
                        if (match_num > 0)
                        {
                            output_stream.Write("\t\t},\n");
                        }
                        ++match_num;
                        output_stream.Write("\t\t{\n");
                        output_stream.Write($"\t\t\t\"matched_text\": \"{match.MatchedText}\",\n\t\t\t\"entity_name\": \"{match.Entity}\",\n\t\t\t\"offset\": {match.OffsetChars},\n\t\t\t\"offset_length\": {match.OffsetBytes},\n\t\t\t\"matched_text_length\": {match.MatchedTextNumBytes},\n\t\t\t\"matched_text_size\": {match.MatchedText.Length},\n\t\t\t\"normalized_text\": \"{match.Text}\",\n\t\t\t\"normalized_text_length\": {match.TextNumBytes},\n\t\t\t\"normalized_text_size\": {match.Text.Length},\n\t\t\t\"score\": {String.Format("{0:F2}", Math.Round(match.Score, 2))},\n\t\t\t\"components\": [");
                        foreach (IExtractionMatchComponent comp in match)
                        {
                            if (component_num > 0)
                            {
                                output_stream.Write("\n\t\t\t\t},");
                            }
                            ++component_num;
                            output_stream.Write("\n\t\t\t\t{\n");
                            output_stream.Write($"\t\t\t\t\t\"name\": \"{comp.Name}\",\n\t\t\t\t\t\"normalized_text\": \"{comp.Text}\",\n\t\t\t\t\t\"normalized_text_length\": {comp.TextNumBytes},\n\t\t\t\t\t\"normalized_text_size\": {comp.Text.Length},\n\t\t\t\t\t\"normalized_text_offset\": {comp.OffsetBytes},\n\t\t\t\t\t\"normalized_text_offset_length\": {comp.OffsetChars}");
                        }
                        output_stream.Write("\n\t\t\t\t}\n");
                        output_stream.Write("\t\t\t]\n");

                        if (session.LastMatchTimedOut())
                        {
                            Console.WriteLine("Warning: eduction session timed out while searching for matches\n");
                            break;
                        }
                    }
                    output_stream.Write("\t\t}\n");
                    output_stream.Write("\t]\n");
                    output_stream.Write("}\n");

                    // Check if timeout with zero matches
                    if (session.LastMatchTimedOut())
                    {
                        Console.WriteLine("Warning: eduction session timed out while searching for matches\n");
                    }
                }
            }
        }
        catch (EDKException ex)
        {
            Console.WriteLine(ex.ToString());
            return -2;
        }
        Console.WriteLine("Extraction complete.");
        return 0;
    }

}
