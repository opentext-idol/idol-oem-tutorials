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
    p = argparse.ArgumentParser(description="Perform KeyView Filter SDK detection and metadata/text extraction on a folder.",
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("filterSDK_bin", help='KeyView Filter SDK bin folder.', type=str)
    p.add_argument("input_folderpath", help='Input folder path to process.', type=str)
    p.add_argument("output_root_filepath", help='Output root file path.', type=str)
    
    return p.parse_args()
    
def get_output_path(output_root, input_root, input_file):
    input_path = os.path.dirname(input_file)
    input_path = os.path.join(input_path, "")
    input_root = os.path.join(input_root, "")

    output_path = os.path.join(output_root, input_path.replace(str(input_root), ""))

    os.makedirs(output_path, exist_ok=True)
    return os.path.join(output_path, os.path.basename(input_file))

def keyview_file(input_filepath, input_root, session, out_dir):
    print("\nKeyViewing file: " + input_filepath)

    try:
        doc = session.open(input_filepath)
        print(str(doc.info))
    except kv.KeyViewError as e:
        print("Unable to open session. KeyView error: " + str(e) + "\n")
        return

    output_path = get_output_path(out_dir, input_root, input_filepath)

    # Get metadata separately from text, since sometimes this is what's supported
    try:
        # open metadata output file
        output_metadata = output_path + "_KV_METADATA.TXT"
        with io.open(output_metadata, "w", encoding = "utf-8") as file_metadata:
            print("Extracting metadata to: " + output_metadata)
            for m in doc.metadata:
                file_metadata.write(m.key + ": " + str(m.value) + "\n")

    except kv.KeyViewError as e_kv:
        print("Unable to complete processing of file. KeyView error: " + str(e_kv) + "\n")
        # could delete the likely empty file, since it was a KeyView error
    except IOError as e_io:
        print("IO error writing metadata / text. " + str(e_io) + "\n")

    # Get text separately from metadata, since sometimes this is what's supported
    try:
        # decide based on doc.info whether application wants to extract text or not
        if doc.info.doc_format in text_extract_exclusions:
            print ("Skipping text extraction because of format code: " + str(doc.info.doc_format) + "\n")
        else:
            # open text output file
            output_text = output_path + "_KV_TEXT.TXT"
            with io.open(output_text, "w", encoding = "utf-8") as file_text:
                print("Extracting text to: " + output_text)
                doc.filter_to_file(file_text)

    except kv.KeyViewError as e_kv:
        print("Unable to complete processing of file. KeyView error: " + str(e_kv) + "\n")
        # could delete the likely empty file, since it was a KeyView error
    except IOError as e_io:
        print("IO error writing metadata / text. " + str(e_io) + "\n")

def listdirs(starting_dir, current_dir, session, out_dir):
    print("\nScanning directory: " + current_dir)
    try:
        for it in os.scandir(current_dir):
            if it.is_dir():
                print("got dir: " + it.path)
                listdirs(starting_dir, it.path, session, out_dir)
            else:
                keyview_file(it.path, starting_dir, session, out_dir)
    except Exception as e:
        print(e + "\n")

# read bin path and input / output file paths from command line
program_args = parse_args()

try:
    session=kv.FilterSession(program_args.filterSDK_bin, get_keyview_license())
    session.config.hidden_text(True)
    session.config.revision_marks(True)
    session.config.custom_pdf_metadata(True)
    session.config.ocr(False)
except kv.KeyViewError as e:
    print("Unable to create filter session. KeyView error: " + str(e))
    sys.exit()

listdirs(program_args.input_folderpath, program_args.input_folderpath, session, program_args.output_root_filepath)