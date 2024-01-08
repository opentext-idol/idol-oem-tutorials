import sys
import os
import io
import keyview.filter as kv

platform = "WINDOWS_X86_64"
#platform = "MACOS_M1"
#platform = "LINUX_X86_64"
filterSDK_home = "C:\\OpenText\\KeyViewFilterSDK_24.1.0_" + platform
exportSDK_home= "C:\\OpenText\\KeyViewExportSDK_24.1.0_" + platform + "\\"
tutorials_home= "C:\\OpenText\\idol-oem-tutorials\\"

# add exclusions for extraction as appropriate for use case
#text_extract_exclusions = [kv.DocFormat.APACHE_PARQUET, kv.DocFormat.POWERPOINT_97, kv.DocFormat.ASCII_TEXT]
text_extract_exclusions = []

output_root = "C:\\OpenText\\_Work\\output"

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

starting_dir = os.path.join(tutorials_home, "resources", "keyview_filter", "")

def get_keyview_license():
    try:
        with open(os.environ["KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"], "r") as lic_file:
            lic = lic_file.read()
            return lic
    except KeyError as k:
        print("Unable to read license file.")
        sys.exit()

def get_output_path(output_root, input_root, input_file):
    input_path = os.path.dirname(input_file)
    input_path = os.path.join(input_path, "")

    output_path = os.path.join(output_root, input_path.replace(str(input_root), ""))
    os.makedirs(output_path, exist_ok=True)
    return os.path.join(output_path, os.path.basename(input_file))

def keyview_file(input_filepath, input_root, session, out_dir):
    print("\nKeyViewing file: " + input_filepath)

    try:
        doc = session.open(input_filepath)
        print(str(doc.info))
    except kv.KeyViewError as e:
        print("Unable to open session. KeyView error: " + str(e))
        return

    output_path = get_output_path(output_root, input_root, input_filepath)

    # Get metadata separately from text, since sometimes this is what's supported
    try:
        # open metadata output file
        output_metadata = output_path + "_KV_METADATA.TXT"
        with io.open(output_metadata, "w", encoding = "utf-8") as file_metadata:
            print("Extracting metadata to: " + output_metadata)
            for m in doc.metadata:
                file_metadata.write(m.key + ": " + str(m.value) + "\n")

    except kv.KeyViewError as e_kv:
        print("Unable to complete processing of file. KeyView error: " + str(e_kv))
        # could delete the likely empty file, since it was a KeyView error
    except IOError as e_io:
        print("IO error writing metadata / text. " + str(e_io))

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
        print("Unable to complete processing of file. KeyView error: " + str(e_kv))
        # could delete the likely empty file, since it was a KeyView error
    except IOError as e_io:
        print("IO error writing metadata / text. " + str(e_io))

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
        print(e)

try:
    session=kv.FilterSession(filterSDK_bin, get_keyview_license())
    session.config.hidden_text(True)
    session.config.revision_marks(True)
    session.config.custom_pdf_metadata(True)
    session.config.ocr(False)
except Exception as e:
    print(e)
    sys.exit()

listdirs(starting_dir, starting_dir, session, output_root)