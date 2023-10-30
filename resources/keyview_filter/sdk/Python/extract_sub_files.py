import sys
import os
import pathlib
import uuid
import shutil
import keyview.filter as kv

platform = "WINDOWS_X86_64"
#platform = "MACOS_M1"
#platform = "LINUX_X86_64"
filterSDK_home = "C:\\OpenText\\KeyViewFilterSDK_23.4.0_" + platform
exportSDK_home= "C:\\OpenText\\KeyViewExportSDK_23.4.0_" + platform + "\\"
tutorials_home= "C:\\OpenText\\idol-oem-tutorials\\"

if (platform == "MACOS_M1"):
    filterSDK_home = "/Users/ec2-user/OpenText/KeyviewFilterSDK_23.4.0_" + platform
    exportSDK_home= "../../../KeyViewExportSDK_23.4.0_" + platform
if (platform == "LINUX_X86_64"):
    filterSDK_home = "/home/username/OpenText/KeyviewFilterSDK_23.4.0_" + platform
    exportSDK_home= "../../../KeyviewExportSDK_23.4.0_" + platform
filterSDK_bin = os.path.join(filterSDK_home, platform, "bin")

input_filepath = os.path.join(filterSDK_home, "javaapi", "KeyView.jar")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "Annual_Report.docx")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "freezer2.ppt")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "FreshDinner.doc")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "frshfrozen.xls")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "Investment_Portfolio.xlsx")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "Onboarding.msg")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "Report_Template.pdf")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "SquaresTemplate.zip")

# add exclusions for extraction as appropriate for use case
#subfile_extract_exclusions = [kv.DocFormat.MS_WORD_2007]
subfile_extract_exclusions = []

output_root = "C:\\OpenText\\_Work\\output"

# process the descendant sub-files for more sub-files or not
process_recursively = False

def get_keyview_license():
    try:
        with open(os.environ["KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"], "r") as lic_file:
            lic = lic_file.read()
            return lic
    except KeyError as k:
        print("Unable to read license file.")
        sys.exit()


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

def extract_sub_file(subfile, out_dir):
    try:
        extract_path = get_safe_extract_path(out_dir, subfile.name)

        print("\nFound other SubFileTypes to extract. Extracting to " + str(extract_path) + "\n")
        print("Extracting " + subfile.name)
        print("\tType: " + subfile.type.name.capitalize())
        print("\tIndex: " + str(subfile.index))
        print("\tParent: " + str(subfile.parent))
        print("\tSize (bytes): " + str(subfile.size))
        print("\tTime: " + str(subfile.time))       # all extracted files may not have a meaningful time
        
        extract_path.parent.mkdir(parents=True, exist_ok=True)
        subfile.extract(extract_path)            
        
        if process_recursively:
            process_file(extract_path, str(extract_path) + ".KV_EXTRACT", process_recursively)
    except OSError as o:
        # this should maybe be a fatal error
        print("Unable to create extract to folder " + str(extract_path) + ". Error: " + o.strerror)
        return False
    except kv.ExternalSubfileError as e: 
        #print("Ignoring external sub-file extraction exception.")
        return True     
    except kv.KeyViewError as e:
        print("KeyView error: " + str(e))
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
                extract_sub_file(subfile, out_dir)
        except kv.KeyViewError as e:
            print("Unable extract sub file(s). KeyView error: " + str(e) + "\n")
            return

# Remove prior sub-file extract folder and create new one
# Removal of old is done out of a convenience
try:
    shutil.rmtree(output_root)
except OSError as o:
    print("ignoring error")

try:
    os.mkdir(output_root)
except OSError as o:
    print(f"Unable to create output folder {output_root}. Error: {o.strerror}")
    sys.exit()

try:
    session = kv.FilterSession(filterSDK_bin, get_keyview_license())
    session.config.extract_images(False)
    session.config.extraction_timeout(300)      # here to illustrate relevant config option
except kv.KeyViewError as e:
    print("Unable to create filter session. KeyView error: " + str(e) + "\n")
    #print(e.error_code())
    sys.exit()

keyview_file(input_filepath, session, output_root, process_recursively)
