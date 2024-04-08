package com.autonomy.eduction.samples;

import com.autonomy.eduction.*;
import com.autonomy.eduction.jni.EDKJNIInputStream;
import com.autonomy.eduction.jni.EDKJNIVersion;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.logging.Logger;

public class FromConfig {

    private static final Logger LOG = Logger.getLogger(FromConfig.class.getName());

    // Parses, checks and stores the arguments to the program
    static class Args {
        private static int CONFIG_IDX = 0;
        private static int DOC_IDX = 1;
        private static int OUTPUTFILE_IDX = 2;
        private static int MAXMATCHESPERDOC_IDX = 3;
        private static int MINSCORE_IDX = 4;
        private static int POSTPROCESSINGTHRESHOLD_IDX = 5;
        private static int OPTIONAL_PARAMS_IDX = 6;

        final Path configPath;                                          // Path to the configuration file
        final Path inputFilePath;                                       // Path to the input file
        final Path outputFilePath;                                      // Path to the desired output JSON file
        OptionalInt maxMatchesPerDoc = OptionalInt.empty();             // Updated MaxMatchesPerDoc for the session. Setting to zero means no limit.
        OptionalDouble minScore = OptionalDouble.empty();               // Updated MinScore for the session. Setting to -1 means no update.
        OptionalDouble postProcessingThreshold = OptionalDouble.empty();// Updated PostProcessThreshold for the session.
        Map<String,Integer> entityMatchLimits;

        private void printUsage() {
            EDKJNIVersion version = EDKJNIVersion.getInstance();
            System.console().printf(String.format("Eduction SDK Sample for SDK version v%s.%d%n", version.getVersionString(),
                    version.getVChangeSet()));
            System.console().printf("Arguments: <configPath> <inputFilePath> <outputFilePath> [<maxMatchesPerDoc>] [<minScore>] [<postProcessingThreshold>] [--limit <entity>=<limit> ...] %n");
        }

        private void checkFileExists(final Path p) throws FileNotFoundException {
            if (!p.toFile().exists() || p.toFile().isDirectory()) {
                throw new FileNotFoundException("File " + p + " does not exist!");
            }
        }

        Args(final String[] stringArgs) throws FileNotFoundException, IOException {
            if (stringArgs.length <= OUTPUTFILE_IDX) {
                printUsage();
                throw new IllegalArgumentException("Wrong number of arguments (at least three required).");
            }

            configPath = Paths.get(stringArgs[CONFIG_IDX]);
            inputFilePath = Paths.get(stringArgs[DOC_IDX]);
            outputFilePath = Paths.get(stringArgs[OUTPUTFILE_IDX]);

            if (stringArgs.length > MAXMATCHESPERDOC_IDX)
            {
                try
                {
                    maxMatchesPerDoc = OptionalInt.of(Integer.parseInt(stringArgs[MAXMATCHESPERDOC_IDX]));
                }
                catch (NumberFormatException e)
                {
                    throw new NumberFormatException("Max matches per doc must be an integer. Got "+stringArgs[MAXMATCHESPERDOC_IDX]);
                }
                catch (Exception e)
                {
                    LOG.severe("Error parsing session max matches per doc");
                    throw new IllegalArgumentException(e);
                }
            }
            if (stringArgs.length > MINSCORE_IDX)
            {
                try
                {
                    minScore = OptionalDouble.of(Double.parseDouble(stringArgs[MINSCORE_IDX]));
                }
                catch (NumberFormatException e)
                {
                    throw new NumberFormatException("Min score must be a double");
                }
                catch (Exception e)
                {
                    LOG.severe("Error parsing session min score");
                    throw new IllegalArgumentException(e);
                }
            }
            if (stringArgs.length > POSTPROCESSINGTHRESHOLD_IDX)
            {
                try
                {
                    postProcessingThreshold = OptionalDouble.of(Double.parseDouble(stringArgs[POSTPROCESSINGTHRESHOLD_IDX]));
                }
                catch (NumberFormatException e)
                {
                    throw new NumberFormatException("Post-processing threshold must be a double");
                }
                catch (Exception e)
                {
                    LOG.severe("Error parsing session post-processing threshold");
                    throw new IllegalArgumentException(e);
                }
            }
            entityMatchLimits = new HashMap<String,Integer>();
            if (stringArgs.length > OPTIONAL_PARAMS_IDX)
            {
                int ii = OPTIONAL_PARAMS_IDX;
                while (ii < stringArgs.length)
                {
                    if (stringArgs[ii].equals("--limit") && ii+1<stringArgs.length)
                    {
                        ++ii;
                        String[] entity_limit = stringArgs[ii].split("=");
                        if (2==entity_limit.length)
                        {
                            try{
                                entityMatchLimits.put(entity_limit[0], Integer.parseInt(entity_limit[1]));
                            }
                            catch (Exception e)
                            {
                                LOG.severe("Error parsing session entity match limit");
                                throw new IllegalArgumentException(e);
                            }
                        }
                    }
                    ++ii;
                }
            }

            checkFileExists(configPath);
            checkFileExists(inputFilePath);

            LOG.info("Parameters valid.");
        }
    }

    private String getLicense() throws IOException {
        Properties props = new Properties();
        try(InputStream propstream = getClass().getResourceAsStream("/license.properties")) {
            props.load(propstream);
        }
        Optional<String> license = Optional.empty();
        try(InputStream keystream = getClass().getResourceAsStream("/license/" + props.getProperty("edk.licensekey.file"));
            InputStreamReader reader = new InputStreamReader(keystream, StandardCharsets.UTF_8);
            BufferedReader buffered = new BufferedReader(reader);
            ) {
            license = buffered.lines().reduce(String::concat);
        }
        if(!license.isPresent()) {
            throw new IOException("Could not read license file.");
        }
		
        return license.get();
    }

    private String getVersionKey() throws IOException {
        Properties props = new Properties();
        try(InputStream propstream = getClass().getResourceAsStream("/license.properties")) {
            props.load(propstream);
        }
        Optional<String> license = Optional.empty();
        try(InputStream keystream = getClass().getResourceAsStream("/license/" + props.getProperty("edk.versionkey.file"));
            InputStreamReader reader = new InputStreamReader(keystream, StandardCharsets.UTF_8);
            BufferedReader buffered = new BufferedReader(reader);
            ) {
            license = buffered.lines().reduce(String::concat);
        }
        if(!license.isPresent()) {
            throw new IOException("Could not read versionkey file.");
        }
		
        return license.get();
    }
	
    // Gets matches from the session and produces lines of JSON to write to the output file
    private List<String> getJsonLines(TextExtractionSession<EDKMatch> session) throws Exception {
        List<String> lines = new ArrayList<>();
        lines.add("{");
        lines.add("\t\"matches\": [");
        int numMatches = 0;
        for (final EDKMatch match : session) {
            final double match_score = match.getScore();
            if (numMatches != 0) {
                lines.add("\t\t},");
            }
            lines.add("\t\t{");
            lines.add(String.format("\t\t\t\"matched_text\": \"%s\",\n\t\t\t\"entity_name\": \"%s\",\n\t\t\t\"offset\":"
                            + " %d,\n\t\t\t\"offset_length\": %d,\n\t\t\t\"matched_text_length\": %d,\n\t\t\t"
                            + "\"matched_text_size\": %d,\n\t\t\t\"normalized_text\": \"%s\",\n\t\t\t"
                            + "\"normalized_text_length\": %d,\n\t\t\t\"normalized_text_size\": %d,\n\t\t\t"
                            + "\"score\": %.2f,\n\t\t\t\"components\": [",
                    match.getOrigText(), match.getEntityName(),
                    match.getOrigOffset(), match.getOrigOffsetLength(), match.getOrigLength(),
                    match.getOrigSize(), match.getText(),
                    match.getTextLength(), match.getTextSize(),
                    match_score));
            boolean firstComponent = true;
            for (final EDKComponent component : match.getComponents()) {
                if (!firstComponent) {
                    lines.add("\t\t\t\t},");
                }
                lines.add("\t\t\t\t{");
                lines.add(String.format("\t\t\t\t\t\"name\": \"%s\",\n\t\t\t\t\t\"normalized_text\": \"%s\",\n\t\t\t\t\t"
                                + "\"normalized_text_length\": %d,\n\t\t\t\t\t\"normalized_text_size\": %d,\n\t\t\t\t\t"
                                + "\"normalized_text_offset\": %d,\n\t\t\t\t\t\"normalized_text_offset_length\": %d",
                        component.getName(), component.getText(),
                        component.getLength(), component.getSize(), 
                        component.getOffset(), component.getOffsetLength()));
                firstComponent = false;
            }
            lines.add("\t\t\t\t}");
            lines.add("\t\t\t]");
            numMatches++;

            if (match.getTimedOut() || session.getTimedOut())
            {
                LOG.warning("Warning: eduction session timed out while searching for matches\n");
                // if we don't break here then looping again could clear
                // timeout if we have exhausted the buffer 
                break;
            }
        }
        lines.add("\t\t}");
        lines.add("\t]");
        lines.add("}");

        // Check if timeout with zero matches
        if (session.getTimedOut())
        {
            LOG.warning("Warning: eduction session timed out while searching for matches\n");
        }

        LOG.log(java.util.logging.Level.INFO, "Got {0} matches", numMatches);
        return lines;
    }

    // The main extraction method
    private void extract(String[] args) throws Exception {
        System.loadLibrary("edkjni");

        Args parsedArgs = new Args(args);

        try (   TextExtractionFactory<EDKMatch> factory = EDKFactory.fromLicenseKey(getLicense() + ";" + getVersionKey());
                TextExtractionEngine<EDKMatch> engine = factory.createEngineFromConfigFile(parsedArgs.configPath);
                TextExtractionSession<EDKMatch> session = engine.createSession();
                InputStream is = Files.newInputStream(parsedArgs.inputFilePath);
        ){
            // Call session.setRequestTimeoutPrecise() or session.setMatchTimeoutPrecise() to override any timeout settings from the config file.
            // The former only has any effect if the session has a specified start time.

            // Set start time
            long start_time = System.currentTimeMillis();
            session.setStartTime(start_time);

            // MaxMatchesPerDoc can be set for a session rather than through the config if necessary
            // If the session has returned matches, it must be reset with session.resetInputText before the setting can be changed.
            // a setting of zero means no limit
            if (parsedArgs.maxMatchesPerDoc.isPresent())
            {
                session.setMaxMatchesPerDoc(parsedArgs.maxMatchesPerDoc.getAsInt());
            }

            //Can set MinScore for a session, overriding the config setting
            //If the session has returned matches, it must be reset with session.resetInputText before the setting can be changed.
            //Setting to -1 via the command line means do not update (useful if you want to just update the post-processing threshold).
            if (parsedArgs.minScore.isPresent())
            {
                double dMinScore = parsedArgs.minScore.getAsDouble();
                if (dMinScore != -1)
                {
                    session.setMinScore(dMinScore);
                }
            }

            //Can set PostProcessingThreshold for a session, overriding the config setting
            //If the session has returned matches, it must be reset with session.resetInputText before the setting can be changed.
            if (parsedArgs.postProcessingThreshold.isPresent())
            {
                session.setPostProcessingThreshold(parsedArgs.postProcessingThreshold.getAsDouble());
            }

            //To limit the amount of text processed by the prefilter, set the 
            //PrefilterMaxReturnedBytes in the config or use the session method
            //e.g. session.setMaxPrefilterBytesPerDoc(max_prefilter_bytes_per_doc);
            //(a prefilter task must be set)

            // Can set EntityMatchLimit for an entity for a session, overriding the config settings
            // If the session has returned matches, it must be reset with session.resetInputText before the setting can be changed.
            
            parsedArgs.entityMatchLimits.forEach( (entity,limit) ->  {
                try {
                    session.setEntityMatchLimit(entity, limit);
                }
                catch (Exception ex) {
                    throw new RuntimeException(ex);
                }
            });

            // Read and input data
            ReadableInputStream stream = new EDKJNIInputStream(is);
            session.setInputStream(stream);
            LOG.info("Input data file opened.");

            // Process data and write JSON to output file
            LOG.log(java.util.logging.Level.INFO, "Printing results to {0}...", parsedArgs.outputFilePath);
            final List<String> lines = getJsonLines(session);
            Files.write(parsedArgs.outputFilePath, lines, StandardCharsets.UTF_8);
        }
    }

    public static void main(String[] args) throws Exception
    {
        FromConfig obj = new FromConfig();
        try {
            obj.extract(args);
        }
        catch(Exception e) {
            LOG.severe("Exception occurred: " + e.getMessage());
            throw e;
        }
    }
}
