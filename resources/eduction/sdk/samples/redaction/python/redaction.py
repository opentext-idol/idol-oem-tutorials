import argparse
import os
import sys

from edk.sdk import EdkFactory
from edk.error import EdkException

def get_eduction_licenseKey():
    try:
        with open(os.environ["EDK_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"], "r") as lic_file:
            print("Using Eduction license key: " + os.environ["EDK_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"])
            lic = lic_file.read()
            return lic
    except IOError as e_io:
        sys.stderr.write("Unable to read license file: " + os.environ["EDK_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"] + "\n")
        sys.exit()
        
def get_eduction_versionKey():
    try:
        with open(os.environ["EDK_SAMPLE_PROGRAM_VERSIONKEY_FROM_FILEPATH"], "r") as verkey_file:
            print("Using Eduction version key: " + os.environ["EDK_SAMPLE_PROGRAM_VERSIONKEY_FROM_FILEPATH"])
            verkey = verkey_file.read()
            return verkey
    except IOError as e_io:
        sys.stderr.write("Unable to read version key file: " + os.environ["EDK_SAMPLE_PROGRAM_VERSIONKEY_FROM_FILEPATH"] + "\n")
        sys.exit()

def parse_args():
    p = argparse.ArgumentParser(description="Perform Eduction redaction.",
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("configpath", help='Eduction engine configuration file path.', type=str)
    p.add_argument("documentpath", help='Input UTF-8 text file path.', type=str)
    p.add_argument("outputfile", help='Output file path.', type=str)
    
    return p.parse_args()
    
# for sample program convenience licensekey and version key are read from file. in practice, it's recommended to "embed" into code

# read Named Entity Recognition configuration and input/output file paths from command line
program_args = parse_args()

try:
    print("Creating EDK Factory.")
    with EdkFactory.create_with_license_key(licensekey=get_eduction_licenseKey() + ";" + get_eduction_versionKey()) as factory:
        # create an engine from config
        print("Creating EDK Engine from config: " + program_args.configpath)
        with factory.engine(configpath=program_args.configpath) as engine:
            try:
                with open(program_args.documentpath) as input_file:
                    # read input filepath, redact and write to stdout
                    print("Redacting input: " + program_args.documentpath)
                    with open(program_args.outputfile, "w") as output_file:
                        output_file.write(engine.redact(input_file.read()))
            except EdkException as e_edk:
                # processing time exceptions are less common relative setup 
                sys.stderr.write("EDK problem during redaction. " + str(e_edk) + "\n")
                sys.exit()                     
            except IOError as e_io:
                sys.stderr.write("IO error reading/writing. " + str(e_io) + "\n")
                sys.exit()
except EdkException as e_edk:   
    sys.stderr.write("Unable to create EdkFactory/Engine. " + str(e_edk) + "\n")
    sys.exit()
