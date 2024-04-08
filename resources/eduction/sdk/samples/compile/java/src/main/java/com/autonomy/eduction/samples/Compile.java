package com.autonomy.eduction.samples;

import com.autonomy.eduction.EDKError;
import com.autonomy.eduction.EDKFactory;
import com.autonomy.eduction.EDKMatch;
import com.autonomy.eduction.TextExtractionEngine;
import com.autonomy.eduction.TextExtractionFactory;
import com.autonomy.eduction.jni.EDKJNIVersion;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Optional;
import java.util.Properties;
import java.util.logging.Logger;

public class Compile {

    private static final Logger LOG = Logger.getLogger(Compile.class.getName());

    static class Args {
        static final int NUM_ARGS = 2;
        final Path input;
        final Path output;

        private void displayUsageInfo() {
            EDKJNIVersion version = EDKJNIVersion.getInstance();
            System.console().printf(String.format("Eduction SDK sample for SDK version v%s.%d%n", version.getVersionString(),
                    version.getVChangeSet()));
            System.console().printf(String.format("SDK built: %s%n", version.getBuildTime()));
            System.console().printf(String.format("Copyright %s%n", version.getCopyright()));
            System.console().printf("Arguments: <input> <output>%n");
        }

        Args(final String[] args) {
            if (args.length != NUM_ARGS) {
                displayUsageInfo();
                throw new IllegalArgumentException("Program requires 2 arguments");
            }

            input = Paths.get(args[0]);
            output = Paths.get(args[1]);

            if (output.toFile().exists()) {
                throw new IllegalArgumentException("Output path already exists");
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
    private void save(String[] args) throws Exception {
        System.loadLibrary("edkjni");

        Args parsedArgs = new Args(args);
        LOG.info("Parameters valid.");

        // Get the license
        String license = getLicense();
        LOG.info("License read.");
        String versionKey = getVersionKey();
        LOG.info("Version key read.");
		
        try(TextExtractionFactory<EDKMatch> factory = EDKFactory.fromLicenseKey(license + ";" + versionKey);
            TextExtractionEngine<EDKMatch> engine = factory.createEngine()
            ) {
            LOG.info("Engine created.");

            try {
                // Load the grammar source file, which compiles it as part of the process
                engine.loadResourceFile(parsedArgs.input.toString());
                LOG.info("Grammar source file loaded and compiled");
                // Save the compiled version of the grammar to a new file
                engine.saveResourceFile(parsedArgs.output.toString());
            }
            catch (Exception e) {
                EDKError err = new EDKError();
                engine.getLastError(err);
                LOG.severe(() -> String.format("FAIL: %s (%d)", err.getErrorMessage(), err.getErrorCode()));
                throw e;
            }
            LOG.info("Compiled grammar file saved");
        }
    }

    public static void main(String[] args) throws Exception {
        Compile obj = new Compile();
        try {
            obj.save(args);
        }
        catch(Exception e) {
            LOG.severe("Exception occurred: " + e.getMessage());
            throw e;
        }
    }
}