# Demo files used by the various KeyView lessons

---

- [Advanced Format Detection](#advanced-format-detection)
  - [SmartCipher\_Fmt.txt](#smartcipher_fmttxt)
  - [SmartCipher\_Fmt.txt.BOGUS\_EXTENSION](#smartcipher_fmttxtbogus_extension)
  - [KeyViewFilterSDK\_12.12.0\_ReleaseNotes\_en.pdf.7z](#keyviewfiltersdk_12120_releasenotes_enpdf7z)
  - [KeyViewFilterSDK\_12.12.0\_ReleaseNotes\_en.pdf\_PASSWORD.7z](#keyviewfiltersdk_12120_releasenotes_enpdf_password7z)
  - [Coffee Chain.twbx](#coffee-chaintwbx)
- [Advanced Text Extraction](#advanced-text-extraction)
  - [2022\_calendar\_HIDDEN\_TEXT.docx](#2022_calendar_hidden_textdocx)
  - [Simple meal planner1.xlsx](#simple-meal-planner1xlsx)
  - [demo\_EMBEDDED\_DOCS+HIDDEN\_TEXT.pptx](#demo_embedded_docshidden_textpptx)
  - [Robin Zupanc Resume\_RESTRICTED.docx](#robin-zupanc-resume_restricteddocx)
  - [AmeliorationFertiliteDesSols.pptx](#ameliorationfertilitedessolspptx)
- [Advanced Metadata Extraction](#advanced-metadata-extraction)
  - [screenshot\_XMP\_METADATA.png](#screenshot_xmp_metadatapng)
  - [Robin Zupanc Resume\_RESTRICTED.docx](#robin-zupanc-resume_restricteddocx-1)
- [Advanced Sub File Extraction](#advanced-sub-file-extraction)
  - [Simple meal planner1.xlsx](#simple-meal-planner1xlsx-1)
  - [demo\_EMBEDDED\_DOCS+HIDDEN\_TEXT.pptx](#demo_embedded_docshidden_textpptx-1)
  - [demo\_HAS\_EMBEDDED\_DOC.zip](#demo_has_embedded_doczip)
  - [email with zip attachment.msg](#email-with-zip-attachmentmsg)
  - [KeyViewFilterSDK\_12.12.0\_ReleaseNotes\_en.rar](#keyviewfiltersdk_12120_releasenotes_enrar)
  - [KeyViewFilterSDK\_12.12.0\_ReleaseNotes\_en.pdf\_PASSWORD.7z](#keyviewfiltersdk_12120_releasenotes_enpdf_password7z-1)
- [Optical Character Recognition (OCR)](#optical-character-recognition-ocr)
  - [screenshot\_TO\_OCR.png](#screenshot_to_ocrpng)
- [RMS](#rms)

---

## Advanced Format Detection

### SmartCipher_Fmt.txt

- OpenText SmartCipher encrypted text file

- `filter -d` detects as 1255 and identifies it's encrypted

### SmartCipher_Fmt.txt.BOGUS_EXTENSION

- OpenText SmartCipher encrypted text file, but with a bogus file extension

- `filter -d` detects as 1255 and identifies it's encrypted

### KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf.7z

### KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf_PASSWORD.7z

### Coffee Chain.twbx
- Download from [Tableau.com](https://community.tableau.com/s/question/0D54T00000C5bBjSAJ/where-can-i-download-the-sample-data-sets)
- Scroll down in forums post to the link to `Coffee Chain.twbx.zip`. 

> NOTE: The downloaded file is a zip containing the .twbx file.  Extract it from the zip to use.

## Advanced Text Extraction

### 2022_calendar_HIDDEN_TEXT.docx

- has mixed languages
- has comments
- has revision marks
- has header / footer
- has more metadata

- filter w/o args extracts body text + comments, no header/footer, no revision marks
- filter -h adds header/footer
- filter -nc excludes comments
- filter -rm add revision marks (*e.g.* Note in February)

### Simple meal planner1.xlsx

- has embedded images
- has multiple named worksheets
- has Excel data types - geo & stock
- has comments
- has notes

- filter extracts body text including "Excel data types" / comments / notes, exclude sheet names
- filter + getsheetnames=1 adds sheet names
- filter -nc excludes comments / notes

### demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx

- embed 2022_calendar_HIDDEN_TEXT.docx and Simple meal planner1.xlsx
- has custom text in slide master

- filter w/o args extracts body text (includes header/footer)
- filter -sh adds slide master text (*e.g.* Secret text in the slide master)

### Robin Zupanc Resume_RESTRICTED.docx

- has hyperlinks

- filter -sh extracts link part of hyperlink

### AmeliorationFertiliteDesSols.pptx

- Download from [http://www.doc-developpement-durable.org/](https://www.doc-developpement-durable.org/file/Culture/Fertilisation-des-Terres-et-des-Sols/AmeliorationFertiliteDesSols.pptx)
- Slide 1 has text that showcases 

## Advanced Metadata Extraction

### screenshot_XMP_METADATA.png

- has standard metadata
- has XMP metadata

- filter -i extracts standard metadata
- filter -xmp extracts raw XMP packet and parses to name/value pairs

### Robin Zupanc Resume_RESTRICTED.docx

- has document restrictions - restrict to read-only. password is: paralegal
- NOTE: followed steps here, including setting password https://support.microsoft.com/en-us/office/make-a-document-read-only-5c25909c-46d9-4eb0-9d1f-d072a560e340

- filtertest -restrictions returns `Write restriction: true`


## Advanced Sub File Extraction

### Simple meal planner1.xlsx

- has embedded images
- has multiple named worksheets
- has Excel data types - geo & stock
- has comments
- has notes

- tstxtract extracts 0 documents
- tstxtract + ExtractImages=true extracts 6 sub files

### demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx

- embed 2022_calendar_HIDDEN_TEXT.docx and Simple meal planner1.xlsx
- has custom text in slide master

- tstxtract extracts 2 sub files
- tstxtract -r extracts 2 sub files
- tstxtract -r + ExtractImages=true extracts 2 sub files, but also 1 more in DOCX and 6 more in XLSX

### demo_HAS_EMBEDDED_DOC.zip 

- contains demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx

- tstxtract extracts 1 sub file
- tstxtract -r extracts add'l files as above for demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx
- tstxtract -r + ExtractImages=true extracts add'l files as above for demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx

### email with zip attachment.msg

- has zip, which contains demo_EMBEDDED_DOC.pptx

- tstxtract extracts 2 sub files (mail & zip)
- tstxtract -r extracts add'l files as above for demo_HAS_EMBEDDED_DOC.zip
- tstxtract -r + ExtractImages=true extracts add'l files as above for demo_HAS_EMBEDDED_DOC.zip

### KeyViewFilterSDK_12.12.0_ReleaseNotes_en.rar

- RAR5 containing PDF

- tstxtract extracts 1 sub file

### KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf_PASSWORD.7z

- password protected 7-zip.  password is: KeyView

- tstxtract returns code 8 (password protected, per include/kverrorcodes.h)
- tstxtract -p <PASSWORD> extracts 1 sub file

## Optical Character Recognition (OCR)

### screenshot_TO_OCR.png

- something to OCR or not
- has typical metadata

- filter extracts text via OCR
- filtertest -nocr extracts no text

## RMS

> COMING SOON!
