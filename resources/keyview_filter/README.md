# Demo files used by the various File Content Extraction lessons

---

- [Advanced Format Detection](#advanced-format-detection)
  - [AFD with `SmartCipher_Fmt.txt`](#afd-with-smartcipher_fmttxt)
  - [AFD with `SmartCipher_Fmt.txt.BOGUS_EXTENSION`](#afd-with-smartcipher_fmttxtbogus_extension)
  - [AFD with `KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf.7z`](#afd-with-keyviewfiltersdk_12120_releasenotes_enpdf7z)
  - [AFD with `KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf_PASSWORD.7z`](#afd-with-keyviewfiltersdk_12120_releasenotes_enpdf_password7z)
  - [AFD with `Coffee Chain.twbx`](#afd-with-coffee-chaintwbx)
- [Advanced Text Extraction](#advanced-text-extraction)
  - [ATF with `2022_calendar_HIDDEN_TEXT.docx`](#atf-with-2022_calendar_hidden_textdocx)
  - [ATF with `Simple meal planner1.xlsx`](#atf-with-simple-meal-planner1xlsx)
  - [ATF with `demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx`](#atf-with-demo_embedded_docshidden_textpptx)
  - [ATF with `Robin Zupanc Resume_RESTRICTED.docx`](#atf-with-robin-zupanc-resume_restricteddocx)
  - [ATF with `AmeliorationFertiliteDesSols.pptx`](#atf-with-ameliorationfertilitedessolspptx)
- [Advanced Metadata Extraction](#advanced-metadata-extraction)
  - [AME with `screenshot_XMP_METADATA.png`](#ame-with-screenshot_xmp_metadatapng)
  - [AME with `Robin Zupanc Resume_RESTRICTED.docx`](#ame-with-robin-zupanc-resume_restricteddocx)
- [Advanced Sub File Extraction](#advanced-sub-file-extraction)
  - [ASFE with `Simple meal planner1.xlsx`](#asfe-with-simple-meal-planner1xlsx)
  - [ASFE with `demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx`](#asfe-with-demo_embedded_docshidden_textpptx)
  - [ASFE with `demo_HAS_EMBEDDED_DOC.zip`](#asfe-with-demo_has_embedded_doczip)
  - [ASFE with `email with zip attachment.msg`](#asfe-with-email-with-zip-attachmentmsg)
  - [ASFE with `KeyViewFilterSDK_12.12.0_ReleaseNotes_en.rar`](#asfe-with-keyviewfiltersdk_12120_releasenotes_enrar)
  - [ASFE with `KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf_PASSWORD.7z`](#asfe-with-keyviewfiltersdk_12120_releasenotes_enpdf_password7z)
- [Optical Character Recognition (OCR)](#optical-character-recognition-ocr)
  - [OCR with `screenshot_TO_OCR.png`](#ocr-with-screenshot_to_ocrpng)
- [RMS](#rms)

---

## Advanced Format Detection

### AFD with `SmartCipher_Fmt.txt`

- OpenText SmartCipher encrypted text file

- `filter -d` detects as 1255 and identifies it's encrypted

### AFD with `SmartCipher_Fmt.txt.BOGUS_EXTENSION`

- OpenText SmartCipher encrypted text file, but with a bogus file extension

- `filter -d` detects as 1255 and identifies it's encrypted

### AFD with `KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf.7z`

### AFD with `KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf_PASSWORD.7z`

### AFD with `Coffee Chain.twbx`

- Download from [Tableau.com](https://community.tableau.com/s/question/0D54T00000C5bBjSAJ/where-can-i-download-the-sample-data-sets)
- Scroll down in forums post to the link to `Coffee Chain.twbx.zip`.

> NOTE: The downloaded file is a zip containing the `.twbx` file.  Extract it from the zip to use.

## Advanced Text Extraction

### ATF with `2022_calendar_HIDDEN_TEXT.docx`

- has mixed languages
- has comments
- has revision marks
- has header / footer
- has more metadata

- `filter` w/o args extracts body text + comments, no header/footer, no revision marks
- `filter -h` adds header/footer
- `filter -nc` excludes comments
- `filter -rm` add revision marks (*e.g.* Note in February)

### ATF with `Simple meal planner1.xlsx`

- has embedded images
- has multiple named worksheets
- has Excel data types - geo & stock
- has comments
- has notes

- `filter` extracts body text including "Excel data types" / comments / notes, exclude sheet names
- `filter` + `getsheetnames=1` adds sheet names
- `filter -nc` excludes comments / notes

### ATF with `demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx`

- embed 2022_calendar_HIDDEN_TEXT.docx and Simple meal planner1.xlsx
- has custom text in slide master

- `filter` w/o args extracts body text (includes header/footer)
- `filter -sh` adds slide master text (*e.g.* Secret text in the slide master)

### ATF with `Robin Zupanc Resume_RESTRICTED.docx`

- has hyperlinks

- `filter -sh` extracts link part of hyperlink

### ATF with `AmeliorationFertiliteDesSols.pptx`

- Download from [http://www.doc-developpement-durable.org/](https://www.doc-developpement-durable.org/file/Culture/Fertilisation-des-Terres-et-des-Sols/AmeliorationFertiliteDesSols.pptx)
- Slide 1 has text that showcases

## Advanced Metadata Extraction

### AME with `screenshot_XMP_METADATA.png`

- has standard metadata
- has XMP metadata

- `filter -i` extracts standard metadata
- `filter -xmp` extracts raw XMP packet and parses to name/value pairs

### AME with `Robin Zupanc Resume_RESTRICTED.docx`

- has document restrictions - restrict to read-only. password is: `paralegal`
  
  > NOTE: followed steps here, including setting password <https://support.microsoft.com/en-us/office/make-a-document-read-only-in-word-5c25909c-46d9-4eb0-9d1f-d072a560e340>

- `filtertest -restrictions` returns `Write restriction: true`

## Advanced Sub File Extraction

### ASFE with `Simple meal planner1.xlsx`

- has embedded images
- has multiple named worksheets
- has Excel data types - geo & stock
- has comments
- has notes

- `tstxtract` extracts 0 documents
- `tstxtract` + `ExtractImages=true` extracts 6 sub files

### ASFE with `demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx`

- embed 2022_calendar_HIDDEN_TEXT.docx and Simple meal planner1.xlsx
- has custom text in slide master

- `tstxtract` extracts 2 sub files
- `tstxtract -r` extracts 2 sub files
- `tstxtract -r` + `ExtractImages=true` extracts 2 sub files, but also 1 more in DOCX and 6 more in XLSX

### ASFE with `demo_HAS_EMBEDDED_DOC.zip`

- contains demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx

- `tstxtract` extracts 1 sub file
- `tstxtract -r` extracts add'l files as above for `demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx`
- `tstxtract -r` + `ExtractImages=true` extracts add'l files as above for `demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx`

### ASFE with `email with zip attachment.msg`

- has zip, which contains demo_EMBEDDED_DOC.pptx

- `tstxtract` extracts 2 sub files (mail & zip)
- `tstxtract -r` extracts add'l files as above for `demo_HAS_EMBEDDED_DOC.zip`
- `tstxtract -r` + `ExtractImages=true` extracts add'l files as above for `demo_HAS_EMBEDDED_DOC.zip`

### ASFE with `KeyViewFilterSDK_12.12.0_ReleaseNotes_en.rar`

- RAR5 containing PDF

- `tstxtract` extracts 1 sub file

### ASFE with `KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf_PASSWORD.7z`

- password protected 7-zip.  password is: `KeyView`

- `tstxtract` returns code 8 (password protected, per `include/kverrorcodes.h`)
- `tstxtract -p <PASSWORD>` extracts 1 sub file

## Optical Character Recognition (OCR)

### OCR with `screenshot_TO_OCR.png`

- something to OCR or not
- has typical metadata

- `filter` extracts text via OCR
- `filtertest -nocr` extracts no text

## RMS

> COMING SOON!
