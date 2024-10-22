import argparse
import json
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
    p = argparse.ArgumentParser(description="Perform Eduction extraction.",
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("configpath", help='Eduction engine configuration file path.', type=str)
    p.add_argument("documentpath", help='Input UTF-8 text file path.', type=str)
    p.add_argument("outputfile", help='Output file path.', type=str)
    
    return p.parse_args()
    
# for sample program convenience licensekey and version key are read from file. in practice, it's recommended to "embed" into code

# read Eduction configuration and input/output file paths from command line
program_args = parse_args()

# open input and output files before doing anything with EductionSDK
try:
    input_file = open(program_args.documentpath)
except IOError as e_io:
    sys.stderr.write("IO error reading: " + program_args.documentpath + " " + str(e_io) + "\n")
    sys.exit()

try:
    output_file = open(program_args.outputfile, 'w', encoding="UTF-8")
except IOError as e_io:
    sys.stderr.write("IO error writing: " + program_args.outputfile + " " + str(e_io) + "\n")
    sys.exit()

# Use Eduction APIs to process text input file
try:
    print("Creating EDK Factory.")
    with EdkFactory.create_with_license_key(licensekey=get_eduction_licenseKey() + ";" + get_eduction_versionKey()) as factory:
        # create an engine from config
        print("Creating EDK Engine from config: " + program_args.configpath)
        with factory.engine(configpath=program_args.configpath) as engine:
            try:
                output_file.write('{\n"matches": [\n')
                try:
                    with engine.session(input=input_file) as session:
                        match_cnt = 0
                        for match in session:
                            # chose to output matches to JSON incrementally rather than JSON pretty print them all at the end
                            json_formatted_str = json.dumps(match.asdict(full=True), indent=2)
                            output_file.write(json_formatted_str)
                            output_file.write(",\n")
                            match_cnt = match_cnt + 1
                            
                        # if there's matches then back up some to remove the last ,\n
                        if (match_cnt > 0):
                            output_file.seek(output_file.tell()-3)
                        output_file.write('\n]}')
                except EdkException as e_edk:
                    # processing time exceptions are less common relative setup 
                    sys.stderr.write("EDK problem during extraction. " + str(e_edk) + "\n")
                    sys.exit() 
            except EdkException as e_edk:   
                sys.stderr.write("Unable to create Engine. " + str(e_edk) + "\n")
                sys.exit()
except EdkException as e_edk:   
    sys.stderr.write("Unable to create EdkFactory " + str(e_edk) + "\n")
    sys.exit()
