# IDOL OEM Tutorials

A set of guides to introduce you to IDOL Eduction and KeyView and associated integration options.

---

- [Taster](#taster)
- [Getting started](#getting-started)
  - [IDOL Eduction](#idol-eduction)
  - [KeyView Filter SDK](#keyview-filter-sdk)
  - [IDOL Media Server](#idol-media-server)
- [Use the APIs](#use-the-apis)
- [Capability showcase examples](#capability-showcase-examples)
  - [Eduction showcase](#eduction-showcase)
    - [Use the PII Eduction grammars](#use-the-pii-eduction-grammars)
    - [Use the PCI Eduction grammars](#use-the-pci-eduction-grammars)
    - [Extract Table Oriented Data](#extract-table-oriented-data)
    - [Assessing Performance of Eduction](#assessing-performance-of-eduction)
    - [Create a custom Eduction grammar](#create-a-custom-eduction-grammar)
    - [Use IDOL Eduction Server](#use-idol-eduction-server)
  - [KeyView Filter SDK showcase](#keyview-filter-sdk-showcase)
    - [Advanced Format Detection](#advanced-format-detection)
    - [Advanced Metadata Extraction](#advanced-metadata-extraction)
    - [Advanced Text Extraction](#advanced-text-extraction)
    - [Advanced Sub File Extraction](#advanced-sub-file-extraction)
    - [Microsoft RMS Files](#microsoft-rms-files)
    - [Optical Character Recognition](#optical-character-recognition)
  - [KeyView and Eduction](#keyview-and-eduction)
- [See also](#see-also)
  - [Links](#links)
    - [KeyView Filter](#keyview-filter)
    - [Eduction](#eduction)

---

## Taster

Take a quick first look at IDOL Eduction and KeyView.  

1. Watch a video introducing KeyView's comprehensive handling of file formats, from identification to filtering and viewing:

   [Watch 1](https://www.youtube.com/watch?v=66niyCTNtLM&list=PLlUdEXI83_Xoq5Fe2iUnY8fjV9PuX61FA).<br />
   [Watch 2](https://www.youtube.com/watch?v=QYEFlziEdTo&list=PLlUdEXI83_Xoq5Fe2iUnY8fjV9PuX61FA).

1. Watch a video exploring the use of Eduction to identify sensitive data, such as PII, within free text:

   [Watch](https://www.youtube.com/watch?v=ftGL0p0PanU&list=PLlUdEXI83_Xoq5Fe2iUnY8fjV9PuX61FA).

## Getting started

Choose where to start below with these IDOL OEM tutorials.  Once you've mastered the basics of one or both components, look further down this page for more advanced usage and to see how they can be used effectively in combination.  Be aware that [resources](../resources) distributed with these tutorials are available for download.

### IDOL Eduction

Make a solid start with Eduction.  Use the out-of-the-box binaries to develop your understanding of the key features and capabilities for matching entities in free text.

[Get started](./eduction/introduction.md).

### KeyView Filter SDK

Build a firm foundation with KeyView Filter.  Use the out-of-the-box binaries to develop your understanding of the key features and capabilities for extracting (filtering) text, metadata and sub-files from files.

[Get started](./keyview_filter/introduction.md).

### IDOL Media Server

IDOL Media Server performs analytics on images, audio and video.  It's for OEMs, too.

[Get started](https://github.com/microfocus-idol/idol-rich-media-tutorials).

## Use the APIs

Use the IDOL, KeyView Filter and Eduction SDK APIs.

[Get started](./apis/README.md#idol-keyview-and-eduction-apis).

## Capability showcase examples

> NOTE: The following assume familiarity with IDOL Eduction and/or KeyView Filter concepts and are best started after completing the respective getting started lesson.

Dip into any of the following showcase lessons to try more features.

### Eduction showcase

Explore more Eduction features.

#### Use the PII Eduction grammars

Explore and use out-of-the-box grammars to match PII entities.

[Get started](./eduction/pii_grammar.md).

#### Use the PCI Eduction grammars

Explore and use out-of-the-box grammars to match PCI entities.

[Get started](./eduction/pci_grammar.md).

#### Extract Table Oriented Data

Extract entities from files with row / column oriented data.

[Get started](./eduction/table_mode.md).

#### Assessing Performance of Eduction

Measure speed of extraction.

[Get started](./eduction/assess_performance.md).

#### Create a custom Eduction grammar

Develop your own rules to match entities.

[Get started](./eduction/custom_grammar.md).

#### Use IDOL Eduction Server

Perform Eduction as a service by calling the IDOL Eduction Server using the ACI API.

[Get started](./eduction/eduction_server.md).

### KeyView Filter SDK showcase

Do more with KeyView.

#### Advanced Format Detection

Other examples of automatic format detection.

[Get started](./keyview_filter/advanced_format_detection.md).

#### Advanced Metadata Extraction

Extract additional document metadata like XMP and document restrictions.

[Get started](./keyview_filter/advanced_metadata_extraction.md).

#### Advanced Text Extraction 

Extract other forms of visible text as well as hidden text.

[Get started](./keyview_filter/advanced_text_extraction.md).

#### Advanced Sub File Extraction

Extract sub-files from various formats.

[Get started](./keyview_filter/advanced_subfile_extraction.md).

#### Microsoft RMS Files

Explore metadata and XrML extraction from [Microsoft Azure RMS](https://docs.microsoft.com/en-us/azure/information-protection/what-is-azure-rms) protected content.

[Get started](./keyview_filter/rms.md).

#### Optical Character Recognition

Extract text from images.

[Get started](./keyview_filter/ocr.md).

### KeyView and Eduction

Combine the two SDKs in your own applications.

> COMING SOON!

## See also

### Links

- Full administration guides are available for all IDOL products [here](https://www.microfocus.com/documentation/idol/).
- Read more tips on working with IDOL products in [IDOL Expert](https://www.microfocus.com/documentation/idol/IDOL_12_12/IDOLServer_12.12_Documentation/Guides/html/expert/index.html).

#### KeyView Filter

- KeyView Filter SDK [C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html)
- KeyView Filter SDK [C++ Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/cpp-programming/index.html)
- KeyView Filter SDK [Java Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/java-programming/index.html)
- KeyView Filter SDK [.NET Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/dotnet-programming/index.html)

#### Eduction

- Eduction SDK [User & Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionSDK_12.12_Documentation/Guides/html/)
- PCI [Technical Note](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionGrammars_12.12_Documentation/PCI/)
- PHI [Technical Note](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionGrammars_12.12_Documentation/PHI/)
- PII [Technical Note](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionGrammars_12.12_Documentation/PII/)
- Government Eduction Package [Technical Note](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionGrammars_12.12_Documentation/GOV/)
