import os
import sys
import keyview.filter as kv

platform = "WINDOWS_X86_64"
#platform = "MACOS_M1"
#platform = "LINUX_X86_64"
filterSDK_home = "C:\\OpenText\\KeyViewFilterSDK_24.1.0_" + platform
exportSDK_home= "C:\\OpenText\\KeyViewExportSDK_24.1.0_" + platform + "\\"
tutorials_home= "C:\\OpenText\\idol-oem-tutorials\\"

output_root = "C:\\OpenText\\_Work\\output"

# add exclusions for extraction as appropriate for use case
#subfile_extract_exclusions = [kv.DocFormat.MS_WORD_2007]
subfile_extract_exclusions = []

# process the descendant sub-files for more sub-files or not
process_recursively = False

if (platform == "MACOS_M1"):
    filterSDK_home = "/Users/ec2-user/OpenText/KeyviewFilterSDK_24.1.0_" + platform
    exportSDK_home= "../../../KeyViewExportSDK_24.1.0_" + platform + "/"
    tutorials_home= "../../../idol-oem-tutorials/"
    output_root = "/Users/ec2-user/OpenText/_Work/output"
if (platform == "LINUX_X86_64"):
    filterSDK_home = "/home/username/OpenText/KeyviewFilterSDK_24.1.0_" + platform
    exportSDK_home= "../../../KeyViewExportSDK_24.1.0_" + platform + "/"
    tutorials_home= "../../../idol-oem-tutorials/"
    output_root = "/home/username/OpenText/_Work/output"
filterSDK_bin = os.path.join(filterSDK_home, platform, "bin")

starting_dir = os.path.join(tutorials_home, "resources", "keyview_filter")

def get_keyview_license():
    try:
        with open(os.environ["KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"], "r") as lic_file:
            lic = lic_file.read()
            return lic
    except KeyError as k:
        print("Unable to read license file.")
        sys.exit()

def get_output_path(input_file):
    input_path = os.path.dirname(input_file)
    #print("input_path: " + input_path)
    output_path = os.path.join(output_root, input_path)
    #print("output_path: " + output_path)
    os.makedirs(output_path, exist_ok=True)
    return os.path.join(output_root, input_file)

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

def keyview_file(input_file, session, out_dir, process_recursively):
    print('KeyViewing file: ' + input_file)
   
    doc = session.open(input_file)
    print(doc.info.doc_format)
    
    session.config.extract_images(False)
    session.config.extraction_timeout(300)      # here to illustrate relevant config option
    

    extract_dir = get_safe_extract_path(output_root, 

    print("output_file : " + output_file)
    # decide based on doc.info whether application wants to extract sub-files or not
    if doc.info.doc_format in subfile_extract_exclusions:
        print ("Skipping sub-file extraction because of format code: " + str(doc.info.doc_format) + "\n")
    else:
        try:
            for subfile in doc.subfiles:
                if (subfile.type == kv.SubfileType.FOLDER):
                    print("Found a folder: " + subfile.name)
                    print("\tIndex: " + str(subfile.index))
                    print("\tChildren: " + str(subfile.children))
                    continue

                extract_path = get_safe_extract_path(out_dir, subfile.name)

                print("Found other SubFileTypes to extract. Extracting to " + str(extract_path) + "\n")
                print("Extracting " + subfile.name)
                print("\tType: " + subfile.type.name.capitalize())
                print("\tIndex: " + str(subfile.index))
                print("\tParent: " + str(subfile.parent))
                print("\tSize (bytes): " + str(subfile.size))
                print("\tTime: " + str(subfile.time))       # not all extracted files have a meaningful time
            
                extract_path.parent.mkdir(parents=True, exist_ok=True)
                subfile.extract_to_file(extract_path)            
            
                if process_recursively:
                    process_file(extract_path, str(extract_path) + ".KV_EXTRACT", process_recursively)



def listdirs(rootdir, session, out_dir, process_recursively):
    try:

        for it in os.scandir(rootdir):
            if it.is_dir():
                print('got dir: ' + it.path)
                listdirs(it)
            else:
                keyview_file(it.path, session, out_dir, process_recursively)
    except Exception as e:
        print(e)
        
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
    session=kv.FilterSession(filterSDK_bin, get_keyview_license())
except Exception as e:
    print(e)
    sys.exit()

listdirs(starting_dir, session, output_root, process_recursively)