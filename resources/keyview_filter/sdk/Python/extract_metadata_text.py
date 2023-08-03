import sys
import os
import io
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
    
#input_filepath = exportSDK_home + "/testdocs/Annual_Report.docx"
input_filepath = exportSDK_home + "/testdocs/freezer2.ppt"
#input_filepath = exportSDK_home + "/testdocs/FreshDinner.doc"
#input_filepath = exportSDK_home + "/testdocs/frshfrozen.xls"
#input_filepath = exportSDK_home + "/testdocs/Investment_Portfolio.xlsx"
#input_filepath = exportSDK_home + "/testdocs/Report_Template.pdf"
#input_filepath = exportSDK_home + "/testdocs/SquaresLetterHead.tif"


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
session.config.ocr(True)

try:
    print('Processing input document: ' + input_filepath)
    doc = session.open(input_filepath)
    print("\n" + str(doc.info) + "\n")
except kv.KeyViewError as e:
    print("Unable to open session. KeyView error: " + str(e))
    sys.exit()

try:
    # open metadata output file
    output_metadata = input_filepath + "_KV_METADATA.TXT"
    with io.open(output_metadata, "w", encoding = "utf-8") as file_metadata:
      print("Extracting metadata to: " + output_metadata)
      for m in doc.metadata:
          file_metadata.write(m.key + ": " + str(m.value) + "\n")
  
    # open text output file
    output_text = input_filepath + "_KV_TEXT.TXT"
    with io.open(output_text, "w", encoding = "utf-8") as file_text:
      print("Extracting text to: " + output_text)
      for line in doc.text.readlines():
          file_text.write(line)            

except kv.KeyViewError as e_kv:
    print("Unable to process file. KeyView error: " + str(e_kv))
    sys.exit()

except IOError as e_io:
    print("IO error writing metadata / text. " + str(e_io))
    sys.exit()
