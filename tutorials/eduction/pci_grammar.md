# Use PCI Eduction grammars

The IDOL PCI Package contains tools that allow you to locate Payment Card Industry (PCI) in your data, to help you comply with financial regulations.

In this lesson, you will:

- Explore and use the out-of-the-box PCI grammars.
- Gain deeper understanding of checksum validation.

> NOTE: This guide assumes you have already completed the introductory Eduction [tutorial](./introduction.md#eduction-sdk-introduction).

---

- [Setup](#setup)
  - [Resources](#resources)
- [What's in the Box?](#whats-in-the-box)
  - [Available Grammar Files](#available-grammar-files)
  - [Types of Entities](#types-of-entities)
- [PAN (Personal Account Number) Matching](#pan-personal-account-number-matching)
- [Run PCI All Example Matching](#run-pci-all-example-matching)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Eduction SDK introduction](../eduction/introduction.md#eduction-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Eduction concepts.

### Resources

Be sure to download the following resources before you continue:
- [PCI edk_samples](../../resources/eduction/pci/edk_samples) and install to `C:\MicroFocus\EductionGrammars_12.12.0_COMMON\pci\edk_samples\resources`

## What's in the Box?

The IDOL PCI Package includes IDOL Eduction Grammar files, postprocessing scripts (*e.g.* checksum & additional validation, output & score normalization and filtering) for certain entities.

### Available Grammar Files

To review which grammar files are included, list the directory `C:\MicroFocus\EductionGrammars_12.12.0_COMMON\pci`. The command `edktool list -a <grammar>.ecr ` can be used to explore the public entities, available components and license requirements.  The PCI Grammar Package covers name (for many countries), date and account number variations specific to the PCI use case.

### Types of Entities

The PCI grammar files provide entities of the "context", "nocontext" and "landmark" forms like the PII, PHI and Gov packages do.

For full details of the entities included with the address grammar, please read the [reference guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionGrammars_12.12_Documentation/PCI/#PCI/PCI_GrammarReference.htm).

For the PCI date entities, like `pci/date/paymentcard/*` available with both "context" and "nocontext" options, consider that the "nocontext" version might over-match significantly (*i.e.*, we are likely to return values that are similar to the entity patterns, such as a date of birth). However, not relying on context also reduces the number of false negatives (*i.e.*, we miss fewer matches).

The PCI number entities, like `pci/pan/*/pan`, there's also "context", "nocontext" and "landmark" entity forms. However, the "nocontext" form has less risk of false positives due to checksum validation which we will explore below.

> NOTE: You can configure Eduction to use either versions of an entity, in which case matches located with context are given a higher score in the results.

## PAN (Personal Account Number) Matching

Let's try this out now to see what information is returned from a PAN match.

In the setup, you deployed PCI edk_samples resources which can be used with the Eduction APIs and `edktool`: `pci\edk_samples\resources\account_nbr\config\account_nbr.cfg`.

Run the following commands to see the output:

```sh
cd C:\MicroFocus\EductionGrammars_12.12.0_COMMON\pci\edk_samples\resources
edktool extract -l ..\..\..\..\EductionSDK_12.12.0_WINDOWS_X86_64\licensekey.dat -c account_nbr\config\account_nbr.cfg -i account_nbr\input\input.txt -o out.xml
```

15 matches are found representing a landmark plus 14 personal account numbers out of 16 potential credit card numbers.
```xml
<?xml version="1.0" encoding="UTF-8"?>
<MATCHLIST>
  <DOCUMENT Type="Plaintext" ID="Unknown">
    <MATCH EntityName="pci/pan/landmark/pan" Offset="61" OffsetLength="61" Score="1" NormalizedTextSize="11" NormalizedTextLength="11" OriginalTextSize="11" OriginalTextLength="11">
      <ORIGINAL_TEXT>Card Number</ORIGINAL_TEXT>
      <NORMALIZED_TEXT>card number</NORMALIZED_TEXT>
    </MATCH>
    <MATCH EntityName="pci/pan/nocontext/pan" Offset="144" OffsetLength="144" Score="1" NormalizedTextSize="15" NormalizedTextLength="15" OriginalTextSize="15" OriginalTextLength="15">
      <ORIGINAL_TEXT>378282246310005</ORIGINAL_TEXT>
      <NORMALIZED_TEXT>378282246310005</NORMALIZED_TEXT>
    </MATCH>
    <MATCH EntityName="pci/pan/nocontext/pan" Offset="181" OffsetLength="181" Score="1" NormalizedTextSize="15" NormalizedTextLength="15" OriginalTextSize="15" OriginalTextLength="15">
      <ORIGINAL_TEXT>371449635398431</ORIGINAL_TEXT>
      <NORMALIZED_TEXT>371449635398431</NORMALIZED_TEXT>
    </MATCH>
    ...
  </DOCUMENT>
</MATCHLIST>
```

You might ask why only 14 out of 16?  For the samples data in `account_nbr\input\input.txt`, there are two reasons:
1. the 13 digit Visa number is of an old form that is currently excluded in order to achieve the right balance of precision, recall and speed.
2. the last example in `input.txt` matches the American Express regex (leading digits and length).  However, it is blocked at the post-processing validation stage, which performs a checksum validation using the Luhn algorithm.  While the PAN does have limiting regex patterns (by length and digit combinations), it is possible to encounter numbers that look like a PAN, but are not. By doing a checksum validation on the matching string of digits, false positive matches are reduced.

As an extra credit exercise, you can edit `account_nbr\config\account_nbr.cfg` commenting out the pci_postprocessing task:
```diff
[Eduction]
- PostProcessingTask0 = pci_postprocessing
+ //PostProcessingTask0 = pci_postprocessing
```

Then re-run `edktool extract` as above but output to `-o out2.xml` so you can compare the results. There will be 16 matches this time: 1 landmark and 15 PANs.

## Run PCI All Example Matching

In the setup, you deployed edk_samples resources.  It contains resources to be used with the Eduction APIs and `edktool`: `pii\edk_samples\resources\pci_all\config\pci_all.cfg`. 

Run the following commands to see the output:

```sh
cd C:\MicroFocus\EductionGrammars_12.12.0_COMMON\pci\edk_samples\resources
edktool extract -l ..\..\..\..\EductionSDK_12.12.0_WINDOWS_X86_64\licensekey.dat -c pci_all\config\pci_all.cfg -i pci_all\input\input.txt -o out.xml
```

The `pci_all` configuration and `input.txt` represent all available entity categories in the PCI package, but does intentional select "nocontext" vs "context" for particular entity categories.

## Conclusion

You now understand how to explore and use the IDOL Eduction's PCI grammars and an example of how the post processing stage of Eduction matching is very valuable. Other entity categories like PII national_id & tin, PHI device UDI & DEA # and GOV Legal Entity Identifier (LEI) do checksum based validation to improve match precision.

Next, why not try more tutorials to explore some of the other features available in IDOL Eduction, linked from the [main page](../README.md#capability-showcase-examples).

## See also

- [IDOL PCI Package Technical Note](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionGrammars_12.12_Documentation/PCI/)
- [IDOL Eduction User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionSDK_12.12_Documentation/Guides/html)