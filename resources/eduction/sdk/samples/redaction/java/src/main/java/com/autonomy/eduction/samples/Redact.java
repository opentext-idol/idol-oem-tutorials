package com.autonomy.eduction.samples;

import com.autonomy.eduction.EDKFactory;
import com.autonomy.eduction.EDKMatch;
import com.autonomy.eduction.TextExtractionEngine;
import com.autonomy.eduction.TextExtractionFactory;
import com.autonomy.eduction.jni.EDKJNIVersion;

import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Map;
import java.util.Optional;
import java.util.Properties;
import java.util.logging.Logger;
import java.util.logging.Level;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class Redact {

    private static final Logger LOG = Logger.getLogger(Redact.class.getName());

    static class Args {
        static final int NUM_ARGS = 3;
        final Path config;
        final Path document;
        final Path output;

        private void displayUsageInfo() {
            EDKJNIVersion version = EDKJNIVersion.getInstance();
            System.console().printf(String.format("Eduction SDK sample for SDK version v%s.%d%n", version.getVersionString(),
                    version.getVChangeSet()));
            System.console().printf(String.format("SDK built: %s%n", version.getBuildTime()));
            System.console().printf(String.format("Copyright %s%n", version.getCopyright()));
            System.console().printf("Arguments: <configpath> <documentpath> <outputfile>%n");
        }

        Args(final String[] args) throws IOException {
            if (args.length < NUM_ARGS) {
                displayUsageInfo();
                throw new IllegalArgumentException(String.format("Program requires %d arguments", Args.NUM_ARGS));
            }

            config = Paths.get(args[0]);
            document = Paths.get(args[1]);
            output = Paths.get(args[2]);
            
            if (!config.toFile().exists()) {
                throw new IllegalArgumentException("Config path does not exist");
            }
            
            if (!document.toFile().exists()) {
                throw new IllegalArgumentException("Document path does not exist");
            }
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
	
    public void redact(String[] args) throws Exception {
        System.loadLibrary("edkjni");

        Args parsedArgs = new Args(args);
        LOG.info("Parameters valid.");

        String license = getLicense();
        LOG.info("Read license.");

        try ( TextExtractionFactory<EDKMatch> factory = EDKFactory.fromLicenseKey(getLicense() + ";" + getVersionKey());
            TextExtractionEngine<EDKMatch> engine = factory.createEngineFromConfigFile(parsedArgs.config);)
        {
            LOG.info("Engine created.");
            
            // Read document
            final Optional<String> document = Files.readAllLines(parsedArgs.document, StandardCharsets.UTF_8)
                    .stream().reduce((s1, s2) -> s1 + "\n" + s2);

            if (!document.isPresent()) {
                throw new FileNotFoundException("Unable to read input document");
            }
            
            // Do the actual redaction - if you want to configure the redaction replacement
            // string, set the RedactionOutputString parameter in the config file. 
            // This will only have an effect when not using RedactionType = Entity.
            String result = engine.redactText(document.get());
            Map<String, Long> counts = engine.getMatchCounts(document.get());
            LOG.log(Level.INFO, "Printing result to {0} ...", parsedArgs.output);
            StringBuilder sb = new StringBuilder();
            sb.append(result);
            for(Map.Entry<String, Long> entry : counts.entrySet())
            {
                sb.append("\n");
                sb.append(entry.getKey());
                sb.append(",");
                sb.append(entry.getValue());
            }
            Files.write(parsedArgs.output, sb.toString().getBytes());

            LOG.info("Program completed without error");
        }
    }

    public static void main(String[] args) throws Exception {
        Redact obj = new Redact();
        try {
            obj.redact(args);
        }
        catch(Exception e) {
            LOG.severe("Exception occurred: " + e.getMessage());
            throw e;
        }
    }
}