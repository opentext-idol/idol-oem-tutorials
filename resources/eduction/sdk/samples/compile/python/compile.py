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
    p = argparse.ArgumentParser(description="Perform Eduction grammar compile.",
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("input", help='Grammar XML source filepath.', type=str)
    p.add_argument("output", help='Grammar ECR destination filepath.', type=str)
    
    return p.parse_args()
    
# for sample program convenience licensekey and version key are read from file. in practice, it's recommended to embed into code

# read grammar input XML and output ECR file paths from command line
program_args = parse_args()

try:
    print("Creating EDK Factory.")
    with EdkFactory.create_with_license_key(licensekey=get_eduction_licenseKey() + ";" + get_eduction_versionKey()) as factory:
        # create an engine from config
        print("Creating EDK Engine")
        with factory.engine() as engine:
            try:
                print("Compiling grammar: " + program_args.input)
                engine.load(grammarpath = program_args.input)
                engine.save(grammarpath = program_args.output)
            except EdkException as e_edk:
                sys.stderr.write("EDK problem during compile. " + str(e_edk) + "\n")
                sys.exit()                     
except EdkException as e_edk:   
    sys.stderr.write("Unable to create EdkFactory/Engine. " + str(e_edk) + "\n")
    sys.exit()

