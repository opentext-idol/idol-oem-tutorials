# IDOL OEM Tutorials

A set of guides to introduce you to IDOL Eduction and KeyView and associated integration options.

---

- [Taster](#taster)
- [Introduction](#introduction)
- [Getting Started](#getting-started)
  - [IDOL Eduction](#idol-eduction)
  - [KeyView Filter](#keyview-filter)
  - [IDOL ACI API](#idol-aci-api)
- [Capability showcase examples](#capability-showcase-examples)
  - [IDOL Eduction showcase](#idol-eduction-showcase)
  - [KeyView Filter showcase](#keyview-filter-showcase)
  - [KeyView and Eduction](#keyview-and-eduction)
  - [IDOL ACI API showcase](#idol-aci-api-showcase)
- [Use the SDKs](#use-the-sdks)
  - [IDOL Eduction](#idol-eduction-1)
  - [KeyView Filter](#keyview-filter-1)
- [See also](#see-also)
  - [IDOL Media Server tutorials](#idol-media-server-tutorials)
  - [Links](#links)
    - [IDOL Eduction](#idol-eduction-2)
    - [KeyView Filter](#keyview-filter-2)

---

## Taster

Take a quick first look at IDOL Eduction and KeyView.  

1. Watch a video introducing KeyView's comprehensive handling of file formats, from identification to filtering and viewing:

      - [Watch 1](https://www.youtube.com/watch?v=66niyCTNtLM&list=PLlUdEXI83_Xoq5Fe2iUnY8fjV9PuX61FA).
      - [Watch 2](https://www.youtube.com/watch?v=QYEFlziEdTo&list=PLlUdEXI83_Xoq5Fe2iUnY8fjV9PuX61FA).

1. Watch a video exploring the use of Eduction to identify sensitive data, such as PII, within free text:

      - [Watch](https://www.youtube.com/watch?v=ftGL0p0PanU&list=PLlUdEXI83_Xoq5Fe2iUnY8fjV9PuX61FA).

## Introduction

These OEM tutorials consist of three branches:

- IDOL Eduction,
- KeyView Filter, and
- IDOL ACI API
   
Once you've mastered the basics of one or all components in the following section, look further down this page for many examples of more advanced usage.  

> NOTE: Be aware that [resources](../resources) distributed with these tutorials are available for download.

## Getting Started

Choose where to start below.

### IDOL Eduction

Make a solid start with Eduction.  Use the out-of-the-box binaries to develop your understanding of the key features and capabilities for matching entities in free text.

[Get started](./eduction/introduction.md).

### KeyView Filter

Build a firm foundation with KeyView Filter.  Use the out-of-the-box binaries to develop your understanding of the key features and capabilities for extracting (filtering) text, metadata and sub-files from files.

[Get started](./keyview_filter/introduction.md).

### IDOL ACI API

Learn how to communicate with any ACI server using the ACI API.  Use sample code in C, Java, .NET and/or Python to build your understanding.

[Get started](./aci_api/introduction.md).

## Capability showcase examples

> NOTE: The following assume familiarity with IDOL Eduction and/or KeyView Filter concepts and are best started after completing the respective getting started lesson above.

Choose an IDOL OEM product below and dip into any of the linked showcase lessons to try more features and expand your knowledge.

### IDOL Eduction showcase

Explore more Eduction features.

[Get started](./eduction/README.md#capability-showcase).

### KeyView Filter showcase

Do more with KeyView.

[Get started](./keyview_filter/README.md#capability-showcase).

### KeyView and Eduction

Combine the two SDKs in your own applications.

> COMING SOON!

### IDOL ACI API showcase

More advanced example usage of the ACI API.

[Get started](./aci_api/README.md#capability-showcase).

## Use the SDKs

IDOL Eduction and KeyView Filter are designed to be embedded into other services.  For example, Micro Focus IDOL embeds the both SDKs into [NiFi processors](https://www.microfocus.com/documentation/idol/IDOL_12_13/NiFiIngest_12.13_Documentation/Help/Content/Walkthrough/BuildBasicPipeline.htm) to be used in data transformation workflows.

Many other Micro Focus products also embed Eduction and KeyView Filter to enhance their capabilities.  ISVs also license Eduction and KeyView Filter, embedding the SDKs into their applications and services for:

- data loss prevention (DLP) and other security and information governance needs,
- document / content management,
- archiving and eDiscovery, and
- many other use cases.

### IDOL Eduction

Use the SDK to perform extraction and more.

[Get started](./eduction/README.md#use-the-eduction-sdk).

### KeyView Filter

Use the SDK to work with your files.

[Get started](./keyview_filter/README.md#use-the-keyview-filter-sdk).

---

## See also

### IDOL Media Server tutorials

IDOL Media Server performs analytics on images, audio and video.  It's for OEMs too, via the ACI API.

[Get started](https://github.com/microfocus-idol/idol-rich-media-tutorials).

### Links

- Full administration guides are available for all IDOL products [here](https://www.microfocus.com/documentation/idol/).
- Read more tips on working with IDOL products in [IDOL Expert](https://www.microfocus.com/documentation/idol/IDOL_12_13/IDOLServer_12.13_Documentation/Guides/html/expert/index.html).

#### IDOL Eduction

- Eduction SDK [User & Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_13/EductionSDK_12.13_Documentation/Guides/html/)
- PCI [Technical Note](https://www.microfocus.com/documentation/idol/IDOL_12_13/EductionGrammars_12.13_Documentation/PCI/)
- PHI [Technical Note](https://www.microfocus.com/documentation/idol/IDOL_12_13/EductionGrammars_12.13_Documentation/PHI/)
- PII [Technical Note](https://www.microfocus.com/documentation/idol/IDOL_12_13/EductionGrammars_12.13_Documentation/PII/)
- Government Eduction Package [Technical Note](https://www.microfocus.com/documentation/idol/IDOL_12_13/EductionGrammars_12.13_Documentation/GOV/)

#### KeyView Filter

- KeyView Filter SDK [C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/c-programming/index.html)
- KeyView Filter SDK [C++ Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/cpp-programming/index.html)
- KeyView Filter SDK [Java Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/java-programming/index.html)
- KeyView Filter SDK [.NET Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/dotnet-programming/index.html)
