import argparse
import io
import os
import sys

import keyview.filter as kv


# add exclusions for extraction as appropriate for use case
#text_extract_exclusions = [kv.DocFormat.APACHE_PARQUET, kv.DocFormat.POWERPOINT_97, kv.DocFormat.ASCII_TEXT]
text_extract_exclusions = []

def get_keyview_license():
    try:
        with open(os.environ["KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"], "r") as lic_file:
            print("Using KeyView license key: " + os.environ["KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"])
            lic = lic_file.read()
            return lic
    except KeyError as k:
        print("Unable to read license file." + os.environ["KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"] + "\n")
        sys.exit()
    except IOError as e_io:
        print("Unable to read license file." + os.environ["KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"] + "\n")
        sys.exit()

def parse_args():
    p = argparse.ArgumentParser(description="Perform KeyView Filter SDK detection and metadata/text extraction.",
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("filterSDK_bin", help='KeyView Filter SDK bin folder.', type=str)
    p.add_argument("input_filepath", help='Input file to process.', type=str)
    p.add_argument("metadata_output_filepath", help='Metadata output file path.', type=str)
    p.add_argument("text_output_filepath", help='Text output file path.', type=str)
    
    return p.parse_args()

# read bin path and input / output file paths from command line
program_args = parse_args()

try:
    session = kv.FilterSession(program_args.filterSDK_bin, get_keyview_license())
except kv.KeyViewError as e:
    print("Unable to create filter session. KeyView error: " + str(e) + "\n")
    sys.exit()

session.config.hidden_text(True)
session.config.revision_marks(True)
session.config.custom_pdf_metadata(True)
session.config.ocr(False)

try:
    input_filepath = program_args.input_filepath
    print('Processing input document: ' + input_filepath)
    doc = session.open(input_filepath)
    print("\n" + str(doc.info) + "\n")
except kv.KeyViewError as e:
    print("Unable to open session. KeyView error: " + str(e) + "\n")
    sys.exit()

# Get metadata separately from text, since sometimes this is what's supported
try:
    # open metadata output file
    output_metadata = program_args.metadata_output_filepath
    with io.open(output_metadata, "w", encoding = "utf-8") as file_metadata:
        print("Extracting metadata to: " + output_metadata)
        for m in doc.metadata:
            file_metadata.write(m.key + ": " + str(m.value) + "\n")

except kv.KeyViewError as e_kv:
    print("Unable to complete processing of file. KeyView error: " + str(e_kv) + "\n")
    # could delete the likely empty file, since it was a KeyView error
except IOError as e_io:
    print("IO error writing metadata / text. " + str(e_io) + "\n")
    sys.exit()

# Get text separately from metadata, since sometimes this is what's supported
try:
    # decide based on doc.info whether application wants to extract text or not
    if doc.info.doc_format in text_extract_exclusions:
        print ("Skipping text extraction because of format code: " + str(doc.info.doc_format) + "\n")
    else:
        # open text output file
        output_text = program_args.text_output_filepath
        with io.open(output_text, "w", encoding = "utf-8") as file_text:
            print("Extracting text to: " + output_text)
            doc.filter_to_file(file_text)

except kv.KeyViewError as e_kv:
    print("Unable to complete processing of file. KeyView error: " + str(e_kv) + "\n")
    # could delete the likely empty file, since it was a KeyView error
except IOError as e_io:
    print("IO error writing metadata / text. " + str(e_io) + "\n")
    sys.exit()