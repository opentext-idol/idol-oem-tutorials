import sys
import os
import pathlib
import uuid
import shutil
import keyview.filter as kv

platform = "WINDOWS_X86_64"
#platform = "MACOS_M1"
#platform = "LINUX_X86_64"
filterSDK_home = "C:\\Opentext\\KeyViewFilterSDK_23.3.0_" + platform
exportSDK_home= "C:\\Opentext\\KeyViewExportSDK_23.3.0_" + platform
if (platform == "MACOS_M1"):
    filterSDK_home = "/Users/ec2-user/OpenText/KeyviewFilterSDK_23.3.0_" + platform
    exportSDK_home= "../../../KeyViewExportSDK_23.3.0_" + platform
if (platform == "LINUX_X86_64"):
    filterSDK_home = "/home/username/OpenText/KeyviewFilterSDK_23.3.0_" + platform
    exportSDK_home= "../../../KeyViewExportSDK_23.3.0_" + platform
filterSDK_bin = os.path.join(filterSDK_home, platform, "bin")
    
#input_filepath = "../../javaapi/KeyView.jar"
#input_filepath = exportSDK_home + "/testdocs/Annual_Report.docx"
#input_filepath = exportSDK_home + "/testdocs/freezer2.ppt"
#input_filepath = exportSDK_home + "/testdocs/FreshDinner.doc"
#input_filepath = exportSDK_home + "/testdocs/frshfrozen.xls"
#input_filepath = exportSDK_home + "/testdocs/Investment_Portfolio.xlsx"
#input_filepath = exportSDK_home + /testdocs/Onboarding.msg"
#input_filepath = exportSDK_home + "/testdocs/Report_Template.pdf"
input_filepath = exportSDK_home + "/testdocs/SquaresTemplate.zip"

out_dir = "_extract"


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

try:
    session = kv.FilterSession(filterSDK_bin, get_keyview_license())
except kv.KeyViewError as e:
    print("Unable to create filter session. KeyView error: " + str(e))
    #print(e.error_code())
    sys.exit()

session.config.extract_images(True)
session.config.extraction_timeout(300)      # here to illustrate relevant config option

# Remove prior sub-file extract folder and create new one
# Removal of old is done out of a convenience
try:
    shutil.rmtree(out_dir)
except OSError as o:
    print("ignoring error")

try:
    os.mkdir(out_dir)
except OSError as o:
    print(f"Unable to create output folder {out_dir}. Error: {o.strerror}")
    sys.exit()

try:
    print('Processing input document: ' + input_filepath)
    doc = session.open(input_filepath)
except kv.KeyViewError as e:
    print("Unable to open session. KeyView error: " + str(e))
    sys.exit()

print("\n" + str(doc.info) + "\n")

try:
    n = 0
    for subfile in doc.subfiles:
        if (subfile.type == kv.SubfileType.FOLDER):
            print("Found a folder: " + subfile.name)
            print("\tIndex: " + str(subfile.index))
            print("\tChildren: " + str(subfile.children))
            continue

        n += 1
        extract_path = get_safe_extract_path(out_dir, subfile.name)

        print("Found other SubFileTypes to extract. Extracting to " + str(extract_path))
        print("Extracting " + subfile.name)
        print("\tType: " + subfile.type.name.capitalize())
        print("\tIndex: " + str(subfile.index))
        print("\tParent: " + str(subfile.parent))
        print("\tSize (bytes): " + str(subfile.size))
        print("\tTime: " + str(subfile.time))       # not all extracted files have a meaningful time
        
        extract_path.parent.mkdir(parents=True, exist_ok=True)
        subfile.extract_to_file(extract_path)

    print(str(n) + " sub-files extracted.")

except OSError as o:
    # this should probably be a fatal error
    print("Unable to create extract to folder " + str(extract_path) + ". Error: " + o.strerror)
    
except kv.KeyViewError as e:
    print("KeyView error: " + str(e))
