using System;
using System.IO;

using Eduction;

class CompileExample
{
    private class CommandArgs
    {
        // Prints program usage information to console
        private static void DisplayUsageInfo()
        {
            Console.WriteLine("INFO: Usage: compile <input> <output>");
            Console.WriteLine("INFO: Parameters:");
            Console.WriteLine("INFO:     <input>       Path to the input grammar source file");
            Console.WriteLine("INFO:     <output>      Path to the output compiled grammar file");
        }
        
        public CommandArgs(string[] args)
        {
            if (args.Length != 2)
            {
                DisplayUsageInfo();
                throw new ArgumentException("Program requires two arguments");
            }
            InputPath = args[0];
            OutputPath = args[1];
            // InputPath may have wildcards, so not literally exist as a file
            if (File.Exists(OutputPath))
            {
                throw new ArgumentException("Output path already exists");
            }
        }
        
        public string InputPath { get; }
        public string OutputPath { get; }
    }

    private static string licensekey()
    {
        var assem = typeof(CompileExample).Assembly;
        using (Stream licenseStream = assem.GetManifestResourceStream("edk.licensekey.dat"))
        using (var licenseReader = new StreamReader(licenseStream))
        using (Stream versionStream = assem.GetManifestResourceStream("edk.versionkey.dat"))
        using (var versionReader = new StreamReader(versionStream))
        {
            return licenseReader.ReadToEnd() + ";" + versionReader.ReadToEnd();
        }
    }

    public static int Main(string[] args)
    {
        Console.WriteLine("Program loaded.");
        
        try
        {
            // Parse arguments
            var arguments = new CommandArgs(args);
            Console.WriteLine("Parameters valid.");
            Console.WriteLine("INFO: Grammar Path:  {0}", arguments.InputPath);
            Console.WriteLine("INFO: Output Path:   {0}", arguments.OutputPath);
            
            // Create the compiler
            ICompiler compiler = EDKFactory.FromLicenseKey(licensekey()).GetCompiler();
            Console.WriteLine("Compiler created.");
            
            // Compile from file path
            compiler.CompileFile(arguments.InputPath, arguments.OutputPath);
            Console.WriteLine("Grammar source file compiled and saved.");
        }
        catch (ArgumentException ex)
        {
            Console.WriteLine("FAIL: {0}.", ex.Message);
            return -1;
        }
        catch (EDKException ex)
        {
            Console.WriteLine("FAIL: {0} ({1})", ex.Message, ex.ErrorCode);
            return -1;
        }

        Console.WriteLine("Program completed without an error.");
        return 0;
    }
}