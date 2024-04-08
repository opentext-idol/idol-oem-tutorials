import sys
import os
import io
import keyview.filter as kv

platform = "WINDOWS_X86_64"
#platform = "MACOS_M1"
#platform = "LINUX_X86_64"
filterSDK_home = "C:\\OpenText\\KeyViewFilterSDK_24.2.0_" + platform
exportSDK_home= "C:\\OpenText\\KeyViewExportSDK_24.2.0_" + platform + "\\"
tutorials_home= "C:\\OpenText\\idol-oem-tutorials\\"
if (platform == "MACOS_M1"):
    filterSDK_home = "/Users/ec2-user/OpenText/KeyviewFilterSDK_24.2.0_" + platform
    exportSDK_home= "../../../KeyViewExportSDK_24.2.0_" + platform + "/"
    tutorials_home= "../../../idol-oem-tutorials/"
if (platform == "LINUX_X86_64"):
    filterSDK_home = "/home/username/OpenText/KeyviewFilterSDK_24.2.0_" + platform
    exportSDK_home= "../../../KeyViewExportSDK_24.2.0_" + platform + "/"
    tutorials_home= "../../../idol-oem-tutorials/"
filterSDK_bin = os.path.join(filterSDK_home, platform, "bin")

input_filepath = os.path.join(tutorials_home + "resources", "keyview_filter", "2022_calendar_HIDDEN_TEXT.docx")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "Annual_Report.docx")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "freezer2.ppt")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "FreshDinner.doc")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "frshfrozen.xls")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "Investment_Portfolio.xlsx")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "Report_Template.pdf")
#input_filepath = os.path.join(exportSDK_home, "testdocs", "SquaresLetterHead.tif")

# add exclusions for extraction as appropriate for use case
#text_extract_exclusions = [kv.DocFormat.APACHE_PARQUET, kv.DocFormat.POWERPOINT_97, kv.DocFormat.ASCII_TEXT]
text_extract_exclusions = []

def get_keyview_license():
    try:
        with open(os.environ["KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH"], "r") as lic_file:
            lic = lic_file.read()
            return lic
    except KeyError as k:
        print("Unable to read license file.")
        sys.exit()

try:
    session = kv.FilterSession(filterSDK_bin, get_keyview_license())
except kv.KeyViewError as e:
    print("Unable to create filter session. KeyView error: " + str(e))
    sys.exit()

session.config.hidden_text(True)
session.config.revision_marks(True)
session.config.custom_pdf_metadata(True)
session.config.ocr(False)

try:
    print('Processing input document: ' + input_filepath)
    doc = session.open(input_filepath)
    print("\n" + str(doc.info) + "\n")
except kv.KeyViewError as e:
    print("Unable to open session. KeyView error: " + str(e))
    sys.exit()

# Get metadata separately from text, since sometimes this is what's supported
try:
    # open metadata output file
    output_metadata = input_filepath + "_KV_METADATA.TXT"
    with io.open(output_metadata, "w", encoding = "utf-8") as file_metadata:
        print("Extracting metadata to: " + output_metadata)
        for m in doc.metadata:
            file_metadata.write(m.key + ": " + str(m.value) + "\n")

except kv.KeyViewError as e_kv:
    print("Unable to complete processing of file. KeyView error: " + str(e_kv))
    # could delete the likely empty file, since it was a KeyView error
except IOError as e_io:
    print("IO error writing metadata / text. " + str(e_io))
    sys.exit()

# Get text separately from metadata, since sometimes this is what's supported
try:
    # decide based on doc.info whether application wants to extract text or not
    if doc.info.doc_format in text_extract_exclusions:
        print ("Skipping text extraction because of format code: " + str(doc.info.doc_format) + "\n")
    else:
        # open text output file
        output_text = input_filepath + "_KV_TEXT.TXT"
        with io.open(output_text, "w", encoding = "utf-8") as file_text:
            print("Extracting text to: " + output_text)
            doc.filter_to_file(file_text)

except kv.KeyViewError as e_kv:
    print("Unable to complete processing of file. KeyView error: " + str(e_kv))
    # could delete the likely empty file, since it was a KeyView error
except IOError as e_io:
    print("IO error writing metadata / text. " + str(e_io))
    sys.exit()