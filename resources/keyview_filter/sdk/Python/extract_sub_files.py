import argparse
import os
import pathlib
import shutil
import sys
import uuid

import keyview.filter as kv

# add exclusions for extraction as appropriate for use case
#subfile_extract_exclusions = [kv.DocFormat.MS_WORD_2007]
subfile_extract_exclusions = []

# process the descendant sub-files for more sub-files or not
process_recursively = False

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
    p = argparse.ArgumentParser(description="Perform KeyView Filter SDK detection and sub-file extraction.",
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("filterSDK_bin", help='KeyView Filter SDK bin folder.', type=str)
    p.add_argument("input_filepath", help='Input file to process.', type=str)
    p.add_argument("output_root_filepath", help='Output root file path.', type=str)
    p.add_argument("--recurse", help="Recursively process input file", action='store_true', required=False)
    return p.parse_args()
    
def get_safe_extract_path(extract_dir, subfile_name):
    abs_extract_dir = pathlib.Path(extract_dir).resolve()
    abs_extract_path = (abs_extract_dir / subfile_name).resolve()
    if abs_extract_dir in abs_extract_path.parents:
        # path is inside extract dir 
        # it's already safe so return it
        return abs_extract_path
    # path is outside extract_dir, so create a safe name
    # TODO logging
    return abs_extract_dir / f"kv_escape_{uuid.uuid4().hex}_{abs_extract_path.name}"

def extract_sub_file(session, subfile, out_dir, process_recursively):
    try:
        extract_path = get_safe_extract_path(out_dir, subfile.name)

        print("\nFound other SubFileTypes to extract.")
        print("Extracting " + subfile.name)
        print("to " + str(extract_path))
        print("\tType: " + subfile.type.name.capitalize())
        print("\tIndex: " + str(subfile.index))
        print("\tParent: " + str(subfile.parent))
        print("\tSize (bytes): " + str(subfile.size))
        print("\tTime: " + str(subfile.time))       # all extracted files may not have a meaningful time
        
        extract_path.parent.mkdir(parents=True, exist_ok=True)
        subfile.extract(extract_path)            
        
        if process_recursively:
            keyview_file(str(extract_path), session, str(extract_path) + ".KV_EXTRACT", process_recursively)
    except OSError as o:
        # this should maybe be a fatal error
        print("Unable to create extract to folder " + str(extract_path) + ". Error: " + o.strerror + "\n")
        return False
    except kv.ExternalSubfileError as e: 
        print("Skipping external sub-file extraction.")
        return True     
    except kv.KeyViewError as e:
        print("KeyView error: " + str(e) + "\n")
        print(e.error_code)
        return False

def keyview_file(input_filepath, session, out_dir, process_recursively):
    print("---------------\n")
    print("KeyViewing file: " + input_filepath)

    try:
        doc = session.open(input_filepath)
        print(str(doc.info))
    except kv.KeyViewError as e:
        print("Unable to open session. KeyView error: " + str(e) + "\n")
        return

    # decide based on doc.info whether application wants to extract sub-files or not
    if doc.info.doc_format in subfile_extract_exclusions:
        print ("Skipping sub-file extraction because of format code: " + str(doc.info.doc_format) + "\n")
    else:
        try:
            for subfile in doc.subfiles:
                if (subfile.type == kv.SubfileType.Folder):
                    print("Found a folder: " + subfile.name)
                    print("\tIndex: " + str(subfile.index))
                    print("\tChildren: " + str(subfile.children))
                    continue
                extract_sub_file(session, subfile, out_dir, process_recursively)
        except kv.KeyViewError as e:
            print("Unable extract sub file(s). KeyView error: " + str(e) + "\n")
            return


# read bin path and input / output file paths from command line
program_args = parse_args()
if program_args.recurse:
    process_recursively = program_args.recurse

# Remove prior sub-file extract folder and create new one
# Removal of old is done out of a convenience
try:
    shutil.rmtree(program_args.output_root_filepath)
except OSError as o:
    #print("ignoring error")
    pass

try:
    os.mkdir(program_args.output_root_filepath)
except OSError as o:
    print(f"Unable to create output folder {program_args.output_root_filepath}. Error: {o.strerror}" + "\n")
    sys.exit()

try:
    session = kv.FilterSession(program_args.filterSDK_bin, get_keyview_license())
    session.config.extract_images(False)
    session.config.extraction_timeout(300)      # here to illustrate relevant config option
except kv.KeyViewError as e:
    print("Unable to create filter session. KeyView error: " + str(e) + "\n")
    sys.exit()

keyview_file(program_args.input_filepath, session, program_args.output_root_filepath, process_recursively)
