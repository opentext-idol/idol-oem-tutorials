# Use Government Eduction grammars

The Eduction Government Package contains tools that allow you to locate various forms of classified / unclassified Government markings,  U.S. export controls related entities, U.S. regulation references and global legal entity identifier.

In this lesson, you will:

- Explore and use the out-of-the-box Government Markings grammars.

> NOTE: This guide assumes you have already completed the introductory Eduction [tutorial](./introduction.md#introduction-to-eduction).

---

- [Setup](#setup)
  - [Resources](#resources)
- [What's in the Box?](#whats-in-the-box)
  - [Available Grammar Files](#available-grammar-files)
  - [Types of Entities](#types-of-entities)
- [Run Government All Example Matching](#run-government-all-example-matching)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Eduction SDK introduction](../eduction/introduction.md#introduction-to-eduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Eduction concepts.

### Resources

Be sure to download the following resources before you continue:
- [Government edk_samples](../../resources/eduction/gov/edk_samples) and install to `C:\OpenText\EductionGrammars_25.1.0_COMMON\gov\edk_samples\resources`

## What's in the Box?

The Eduction Government Package includes Eduction Grammar files, post-processing scripts (*e.g.* checksum & additional validation, output & score normalization and filtering) for certain entities.

### Available Grammar Files

To review which grammar files are included, list the directory `C:\OpenText\EductionGrammars_25.1.0_COMMON\gov`. The command `edktool list -a <grammar>.ecr ` can be used to explore the public entities, available components and license requirements. Or open the `gov_entities.html` file in your web browser. This `.html` file conveniently lists available entities by locale as well as grammar file name.

The Government Grammar Package covers classified/unclassified markings for the U.S. and Australia, U.S. export controls and a global, legal entity identifier.

### Types of Entities

The Government grammar files provide entities of the "context", "nocontext" and "landmark" forms like the PII, PHI and PCI packages do.

For full details of the entities included in the Government Grammar Package, please reference the [Eduction Grammars User Guide - Government Grammars](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionGrammars_25.1_Documentation/Help/Content/PackGov/PackGov_Intro.htm)

> NOTE: You can configure Eduction to use either versions of an entity, in which case matches located with context are given a higher score in the results.

## Run Government All Example Matching

In the setup, you deployed edk_samples resources.  It contains resources to be used with the Eduction APIs and `edktool`: `gov\edk_samples\resources\gov_all\config\gov_all.cfg`.

Run the following commands to see the output:

```sh
> cd C:\OpenText\EductionGrammars_25.1.0_COMMON\gov\edk_samples\resources
> edktool.exe extract -l ..\..\..\..\EductionSDK_25.1.0_WINDOWS_X86_64\licensekey.dat -c gov_all\config\gov_all.cfg -i gov_all\input\input.txt -o out.xml
```

The `gov_all.cfg` configuration and `input.txt` represent all available entity categories in the Government package, but does intentionally select "nocontext" vs "context" for particular entity categories.

## Conclusion

You now understand how to explore and use the Eduction's Government grammars and an example of how the post processing stage of Eduction matching is very valuable.

Next, why not try more tutorials to explore some of the other features available in Eduction, linked from [here](../eduction/README.md#capability-showcase).

## See also

- [Eduction Grammars Users Guide - Government Grammars](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionGrammars_25.1_Documentation/Help/Content/PackGov/PackGov_Intro.htm)
- [Eduction User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionSDK_25.1_Documentation/Guides/html/)
- [Knowledge Discovery Release Notes - Eduction](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/IDOLReleaseNotes_25.1_Documentation/idol/Content/SDKs/Eduction.htm)