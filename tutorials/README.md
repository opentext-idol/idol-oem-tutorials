# IDOL OEM Tutorials

A set of guides to introduce you to IDOL Eduction and KeyView and associated integration options.

---

- [Taster](#taster)
- [Introduction](#introduction)
- [Getting Started](#getting-started)
  - [Eduction](#eduction)
  - [KeyView Filter](#keyview-filter)
  - [KeyView Export](#keyview-export)
  - [IDOL ACI API](#idol-aci-api)
- [Capability showcase examples](#capability-showcase-examples)
  - [Eduction showcase](#eduction-showcase)
  - [KeyView Filter showcase](#keyview-filter-showcase)
  - [KeyView Export showcase](#keyview-export-showcase)
  - [IDOL ACI API showcase](#idol-aci-api-showcase)
- [Use the SDKs](#use-the-sdks)
  - [Eduction](#eduction-1)
  - [KeyView Filter](#keyview-filter-1)
  - [KeyView Export](#keyview-export-1)
  - [KeyView Filter + Eduction](#keyview-filter--eduction)
- [See also](#see-also)
  - [IDOL Media Server tutorials](#idol-media-server-tutorials)
  - [Links](#links)
    - [IDOL Eduction](#idol-eduction)
    - [KeyView Filter](#keyview-filter-2)
    - [KeyView Export](#keyview-export-2)

---

## Taster

Take a quick first look at IDOL Eduction and KeyView.  

1. Watch a video introducing KeyView's comprehensive handling of file formats, from identification to filtering and viewing:

      - [Watch 1](https://www.youtube.com/watch?v=66niyCTNtLM&list=PLlUdEXI83_Xoq5Fe2iUnY8fjV9PuX61FA).
      - [Watch 2](https://www.youtube.com/watch?v=QYEFlziEdTo&list=PLlUdEXI83_Xoq5Fe2iUnY8fjV9PuX61FA).

1. Watch a video exploring the use of Eduction to identify sensitive data, such as PII, within free text:

      - [Watch](https://www.youtube.com/watch?v=ftGL0p0PanU&list=PLlUdEXI83_Xoq5Fe2iUnY8fjV9PuX61FA).

## Introduction

These OEM tutorials consist of four branches:

- Eduction,
- KeyView Filter,
- KeyView Export, and
- IDOL ACI API (including IDOL Connectors)
   
Once you've mastered the basics of one or all components in the following section, look further down this page for many examples of more advanced usage.  

> NOTE: Be aware that [resources](../resources) distributed with these tutorials are available for download.

## Getting Started

Choose where to start below.

### Eduction

Make a solid start with Eduction.  Use the out-of-the-box binaries to develop your understanding of the key features and capabilities for matching entities in free text.

[Get started](./eduction/introduction.md).

### KeyView Filter

Build a firm foundation with KeyView Filter.  Use the out-of-the-box binaries to develop your understanding of the key features and capabilities for extracting (filtering) text, metadata and sub-files from files.

[Get started](./keyview_filter/introduction.md).

### KeyView Export

Build a firm foundation with KeyView Export.  Use the out-of-the-box binaries to develop your understanding of the key features and capabilities for producing HTML, XML and PDF renditions.

[Get started](./keyview_export/introduction.md).

### IDOL ACI API

Learn how to communicate with any ACI server using the ACI API.  Use sample code in C, Java, .NET and/or Python to build your understanding.

[Get started](./aci_api/introduction.md).

## Capability showcase examples

> NOTE: The following assume familiarity with IDOL Eduction and/or KeyView Filter concepts and are best started after completing the respective getting started lesson above.

Choose an IDOL OEM product below and dip into any of the linked showcase lessons to try more features and expand your knowledge.

### Eduction showcase

Explore more Eduction features.

[Get started](./eduction/README.md#capability-showcase).

### KeyView Filter showcase

Do more with KeyView Filter.

[Get started](./keyview_filter/README.md#capability-showcase).

### KeyView Export showcase

Do more with KeyView Export.

[Get started](./keyview_export/README.md#capability-showcase)

### IDOL ACI API showcase

More advanced example usage of the ACI API.

[Get started](./aci_api/README.md#capability-showcase).

## Use the SDKs

IDOL Eduction and KeyView Filter are designed to be embedded into other services.  For example, OpenText IDOL embeds the both SDKs into [NiFi processors](https://www.microfocus.com/documentation/idol/IDOL_24_3/NiFiIngest_24.3_Documentation/Help/Content/Walkthrough/BuildBasicPipeline.htm) to be used in data transformation workflows.

Many other OpenText products also embed Eduction and KeyView Filter to enhance their capabilities.  ISVs also license Eduction and KeyView Filter, embedding the SDKs into their applications and services for:

- data loss prevention (DLP) and other security and information governance needs,
- document / content management,
- archiving and eDiscovery, and
- many other use cases.

### Eduction

Use the SDK to perform extraction and more.

[Get started](./eduction/README.md#use-the-eduction-sdk).

### KeyView Filter

Use the SDK to work with your files.

[Get started](./keyview_filter/README.md#use-the-keyview-filter-sdk).

### KeyView Export

Use the SDK to work with your files.

[Get started](./keyview_export/README.md#use-the-keyview-export-sdk).

### KeyView Filter + Eduction

Use the KeyView Filter and Eduction SDKs into a combined solution.

[Get started](./keyview_filter+eduction/README.md#use-the-keyview-filter-sdk-and-eduction-sdk)

---

## See also

### IDOL Media Server tutorials

IDOL Media Server performs analytics on images, audio and video.  It's for OEMs too, via the ACI API.

[Get started](https://github.com/opentext-idol/idol-rich-media-tutorials).

### Links

- Full administration guides and release notes are available for all IDOL products [here](https://www.microfocus.com/documentation/idol/).
- Read more tips on working with IDOL products in [IDOL Expert](https://www.microfocus.com/documentation/idol/IDOL_24_3/IDOLServer_24.3_Documentation/Guides/html/expert/index.html).
- See the latest release notes for all IDOL products [here](https://www.microfocus.com/documentation/idol/IDOL_24_3/IDOLReleaseNotes_24.3_Documentation/idol/Content/_Introduction.htm).

#### IDOL Eduction

- Eduction SDK [User & Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionSDK_24.3_Documentation/Guides/html/)
- Eduction Server [Reference Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionServer_24.3_Documentation/Help/Content/_ACI_Welcome.htm)
- PCI [Technical Note](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionGrammars_24.3_Documentation/PCI/)
- PHI [Technical Note](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionGrammars_24.3_Documentation/PHI/)
- PII [Technical Note](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionGrammars_24.3_Documentation/PII/)
- Government Eduction Package [Technical Note](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionGrammars_24.3_Documentation/GOV/)

#### KeyView Filter

- KeyView Filter SDK [C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/c-programming/index.html)
- KeyView Filter SDK [C++ Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/cpp-programming/index.html)
- KeyView Filter SDK [Java Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/java-programming/index.html)
- KeyView Filter SDK [.NET Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/dotnet-programming/index.html)
- KeyView Filter SDK [Python Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/python-programming/index.html)

#### KeyView Export

- KeyView HTML Export SDK [C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewExportSDK_24.3_Documentation/Guides/html/html-export-c/index.html)
- KeyView HTML Export SDK [Java Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewExportSDK_24.3_Documentation/Guides/html/html-export-java/index.html)
- KeyView XML Export SDK [C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewExportSDK_24.3_Documentation/Guides/html/xml-export-c/index.html)
- KeyView XML Export SDK [Java Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewExportSDK_24.3_Documentation/Guides/html/xml-export-java/)
- KeyView PDF Export SDK [C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewExportSDK_24.3_Documentation/Guides/html/pdf-export-c/index.html)
