import argparse
import json
import io
import os
import sys

import keyview.filter as kv

from edk.sdk import EdkFactory
from edk.error import EdkException

def get_keyview_license():
    try:
        with open(os.environ["KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"], "r") as lic_file:
            print("Using the license key: " + os.environ["KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"])
            lic = lic_file.read()
            return lic
    except KeyError as k:
        print("Unable to read license file." + os.environ["KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"] + "\n")
        sys.exit()
    except IOError as e_io:
        print("Unable to read license file." + os.environ["KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"] + "\n")
        sys.exit()
        
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
    p = argparse.ArgumentParser(description="Perform Eduction on any file type supported by the Filter SDK",
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("filterSDK_bin", help='Filter SDK bin folder.', type=str)
    p.add_argument("configpath", help='Eduction engine configuration file path.', type=str)
    p.add_argument("input_filepath", help='Input file to process.', type=str)
    p.add_argument("outputfile", help='Output file path.', type=str)

    return p.parse_args()


# read Eduction configuration and input/output file paths from command line
program_args = parse_args()
   
try:
    print("Creating the Filter SDK session.")
    kv_session = kv.FilterSession(program_args.filterSDK_bin, get_keyview_license())
except kv.KeyViewError as e:
    print("Unable to create filter session. Filter SDK error: " + str(e))
    sys.exit()

kv_session.config.hidden_text(True)
kv_session.config.revision_marks(True)
kv_session.config.custom_pdf_metadata(True)
kv_session.config.ocr(False)  


try:
    print("Creating EDK Factory.")
    with EdkFactory.create_with_license_key(licensekey=get_eduction_licenseKey() + ";" + get_eduction_versionKey()) as factory:
        try:
            print("Creating EDK Engine from config: " + program_args.configpath)
            with factory.engine(configpath=program_args.configpath) as edk_engine:
                try:
                    doc = kv_session.open(program_args.input_filepath)
                    print("Creating EDK Session and processing input stream.")
                    with open(program_args.outputfile, 'w', encoding="UTF-8") as output_file:
                        output_file.write('{\n"matches": [\n')
                        with edk_engine.session(input=doc.text) as edk_session:
                            match_cnt = 0
                            for match in edk_session:
                                json_formatted_str = json.dumps(match.asdict(full=True), indent=2)
                                output_file.write(json_formatted_str)
                                output_file.write(",\n")
                                match_cnt = match_cnt + 1
                                        
                            # if there's matches then back up some to remove the last ,\n
                            if (match_cnt > 0):
                                output_file.seek(output_file.tell()-3)
                            output_file.write('\n]}')
                except EdkException as e_edk:
                    sys.stderr.write("EDK problem during extraction. Edk error: " + str(e_edk) + "\n")
                    sys.exit()
                except kv.KeyViewError as e:
                    print("Unable to open Filter SDK session. Filter SDK error: " + str(e))
                    sys.exit()
        except EdkException as e_edk:   
            sys.stderr.write("Unable to create EdkEngine. Edk error: " + str(e_edk) + "\n")
            sys.exit()

except EdkException as e_edk:   
    sys.stderr.write("Unable to create EdkFactory. Edk error: " + str(e_edk) + "\n")
    sys.exit()
