# Use Government Named Entity Recognition grammars

The Named Entity Recognition Government Package contains tools that allow you to locate various forms of classified / unclassified Government markings,  U.S. export controls related entities, U.S. regulation references and global legal entity identifier.

In this lesson, you will:

- Explore and use the out-of-the-box Government Markings grammars.

> NOTE: This guide assumes you have already completed the introductory Named Entity Recognition [tutorial](./introduction.md).

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

> NOTE: This lesson assumes you have already completed the [Named Entity Recognition SDK introduction](../eduction/introduction.md) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Named Entity Recognition concepts.

### Resources

Be sure to download the following resources before you continue:
- [Government edk_samples](../../resources/eduction/gov/edk_samples) and install to `C:\OpenText\EductionGrammars_25.4.0_COMMON\gov\edk_samples\resources`

## What's in the Box?

The Named Entity Recognition Government Package includes Named Entity Recognition Grammar files, post-processing scripts (*e.g.* checksum & additional validation, output & score normalization and filtering) for certain entities.

### Available Grammar Files

To review which grammar files are included, list the directory `C:\OpenText\EductionGrammars_25.4.0_COMMON\gov`. The command `edktool list -a <grammar>.ecr ` can be used to explore the public entities, available components and license requirements. Or open the `gov_entities.html` file in your web browser. This `.html` file conveniently lists available entities by locale as well as grammar file name.

The Government Grammar Package covers classified/unclassified markings for the U.S. and Australia, U.S. export controls and a global, legal entity identifier.

### Types of Entities

The Government grammar files provide entities of the "context", "nocontext" and "landmark" forms like the PII, PHI and PCI packages do.

For full details of the entities included in the Government Grammar Package, please reference the [Named Entity Recognition Grammars User Guide - Government Grammars](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionGrammars_25.4_Documentation/Help/Content/PackGov/PackGov_Intro.htm)

> NOTE: You can configure Named Entity Recognition to use either versions of an entity, in which case matches located with context are given a higher score in the results.

## Run Government All Example Matching

In the setup, you deployed edk_samples resources.  It contains resources to be used with the Named Entity Recognition SDK APIs and `edktool`: `gov\edk_samples\resources\gov_all\config\gov_all.cfg`.

Run the following commands to see the output:

```sh
> cd C:\OpenText\EductionGrammars_25.4.0_COMMON\gov\edk_samples\resources
> edktool.exe extract -l ..\..\..\..\EductionSDK_25.4.0_WINDOWS_X86_64\licensekey.dat -c gov_all\config\gov_all.cfg -i gov_all\input\input.txt -o out.xml
```

The `gov_all.cfg` configuration and `input.txt` represent all available entity categories in the Government package, but does intentionally select "nocontext" vs "context" for particular entity categories.

## Conclusion

You now understand how to explore and use the Named Entity Recognition's Government grammars and an example of how the post processing stage of Named Entity Recognition matching is very valuable.

Next, why not try more tutorials to explore some of the other features available in Named Entity Recognition, linked from [here](../eduction/README.md#capability-showcase).

## See also

- [Named Entity Recognition Grammars Users Guide - Government Grammars](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionGrammars_25.4_Documentation/Help/Content/PackGov/PackGov_Intro.htm)
- [Named Entity Recognition User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/)
- [Knowledge Discovery Release Notes - Named Entity Recognition](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/idol/Content/SDKs/Eduction.htm)