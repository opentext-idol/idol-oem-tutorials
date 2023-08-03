# Custom Post Processing

In other Eduction lessons the OOTB `*_postprocessing.lua` scripts are used as is required with these grammars. Various functions are performed within these scripts like checksum and other value validation, score normalization and output normalization.  But there are other valuable use cases for Eduction post-processing.

Refer to the [Eduction User and Programming Guide - Post-Processing](https://www.microfocus.com/documentation/idol/IDOL_23_3/EductionSDK_23.3_Documentation/Guides/html/Content/UseEduction/PostProcessing/LuaPostProcessing.htm) section for more information on this topic.

In this lesson, other uses for post processing will be explored:
- custom redaction of credit card numbers
- entity specific post-process score threshold

> NOTE: This guide assumes you have already completed the introductory Eduction [tutorial](./introduction.md#eduction-sdk-introduction).

> NOTE: This lesson assumes you have already completed the [Eduction PCI Grammar](../eduction/pci_grammar.md#use-pci-eduction-grammars) lesson covering the basics of the PCI Grammar package.

> NOTE: This lesson assumes you have already completed the [Eduction PII Grammar](../eduction/pii_grammar.md#use-pii-eduction-grammars) lesson covering the basics of the PII Grammar package.

---

- [Setup](#setup)
  - [Resources](#resources)
- [Custom redaction of credit card numbers](#custom-redaction-of-credit-card-numbers)
- [Entity specific post-process score threshold](#entity-specific-post-process-score-threshold)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Eduction SDK introduction](./introduction.md#eduction-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Eduction concepts.

### Resources

Be sure to download the following resources before you continue:
- [PCI redact_account_nbr sample](../../resources/eduction/pci/edk_samples/resources/redact_account_nbr) and install to `C:\OpenText\EductionGrammars_23.3.0_COMMON\pci\edk_samples\resources\redact_account_nbr`
- [PII custom post-process threshold](../../resources/eduction/pii/edk_samples/resources/custom_pp_threshold) and install to `C:\OpenText\EductionGrammars_23.3.0_COMMON\pii\edk_samples\resources\custom_pp_threshold`

## Custom redaction of credit card numbers

While the EductionSDK supports redaction of match values in the output text, there are some use cases where special redaction can be valuable. For credit card #'s, the first few digits are generic and related to the issuer with the last few digits also generally preserved.  By removing the middle digits, the credit card # effectively becomes unusable. An example of the redaction looks like the following: 
```
4012 8888 8888 1881

4012 xxxx xxxx 1881
````

> NOTE: This lesson uses the PCI entity `pci/pan/context/pan` (pci_numbers.ecr) but the same approach works with General entity `number/cc` (number_cc.ecr) with no changes to the Lua script.

The `pci_pan_redact.lua` works with the `pci/pan/*context/pan` entity in the pci_numbers.ecr. It should be configured to run after pci_postprocessing.lua as is done in `config/redact_account_nbr.cfg`.  With some simple regular expressions, the middle digits of the credit card number will be replaced with the value in `redaction_character`.  This Lua script works regardless of the # of digits and delimiters that occur in the matching credit card number.

```lua
local redaction_character = "x"

function processmatch (edkmatch)
    if edkmatch then
		local text = edkmatch:getMatchedText()
		local first, middle, last = regex_match(text, "(\\d{4})(.*)(\\d{4})")
		middle = regex_replace_all(middle, "\\d", redaction_character)
		
		edkmatch:setOutputText(first .. middle .. last) 
	end
	
	return true
end
```

> NOTE: The standard IDOL Lua functions - [regex_match()](https://www.microfocus.com/documentation/idol/IDOL_23_3/NiFiIngest_23.3_Documentation/Help/Content/Lua/General/_LUA_regex_match.htm) and  [regex_replace_all()](https://www.microfocus.com/documentation/idol/IDOL_23_3/NiFiIngest_23.3_Documentation/Help/Content/Lua/General/_LUA_regex_replace_all.htm) are the keys to implementing the custom redaction. 


Run the provided example
```sh
> cd C:\OpenText\EductionGrammars_23.3.0\pci\edk_samples\resources
> edktool extract -l ..\..\..\..\EductionSDK_23.3.0_WINDOWS_X86_64\licensekey.dat -c redact_account_nbr\config\redact_account_nbr.cfg -i redact_account_nbr\input\input.txt
```

Two matches are produced:
```xml
...
<?xml version="1.0" encoding="UTF-8"?>
<MATCHLIST>
  <DOCUMENT Type="Plaintext" ID="Unknown">
    <MATCH EntityName="pci/pan/nocontext/pan" Offset="1" OffsetLength="1" Score="1" NormalizedTextSize="19" NormalizedTextLength="19" OriginalTextSize="19" OriginalTextLength="19">
      <ORIGINAL_TEXT>4012 8888 8888 1881</ORIGINAL_TEXT>
      <NORMALIZED_TEXT>4012 xxxx xxxx 1881</NORMALIZED_TEXT>
    </MATCH>
    <MATCH EntityName="pci/pan/nocontext/pan" Offset="22" OffsetLength="22" Score="1" NormalizedTextSize="16" NormalizedTextLength="16" OriginalTextSize="16" OriginalTextLength="16">
      <ORIGINAL_TEXT>4012888888881881</ORIGINAL_TEXT>
      <NORMALIZED_TEXT>4012xxxxxxxx1881</NORMALIZED_TEXT>
    </MATCH>
  </DOCUMENT>
</MATCHLIST>
Entity search completed (T+0.157 seconds)

0.157 seconds elapsed
```

Notice that the `<NORMALIZED_TEXT> has the redacted representation of the matching credit card number with only the middle digits affected.  If `edktool redact` was used then the entire credit number would be redacted.

## Entity specific post-process score threshold

While EductionSDK supports entity specific scoring via `EntityMinScore#`, this score is applied after the ECR/EJR processing and before the post-processing stage. The `PostProcessThreshold` applies to all entities. Refer to [Eduction User and Programming Guide - PostProcessThreshold](https://www.microfocus.com/documentation/idol/IDOL_23_3/EductionSDK_23.3_Documentation/Guides/html/Content/Configuration/Eduction/_EDU_PostProcessThreshold.htm) section of the Eduction User and Programming Guide for more information on this topic.  

This part of the lesson will illustrate how to use a post-processing Lua script to implement an entity specific PostProcessThreshold.

Different `PostProcessThreshold` values per entity allows for use cases like different precision for a particular country within an entity category or similar across entity categories. In this example, we will filter out lower confidence matches of the US SSN (when there's no delimiter) and preserve higher confidence matches (with space or - delimiter), similar for the Argentinian national id number and allow for standard matching of other country national id numbers.

Run the following commands to see the output:

```sh
> cd C:\OpenText\EductionGrammars_23.3.0\pii\edk_samples\resources
> edktool extract -l ..\..\..\..\EductionSDK_23.3.0_WINDOWS_X86_64\licensekey.dat -c custom_pp_threshold\config\custom_pp_threshold.cfg -i custom_pp_threshold\input\input.txt -o out_custom_pp_threshold.xml
```

The following matches are produced
```xml
...
<?xml version="1.0" encoding="UTF-8"?>
<MATCHLIST>
  <DOCUMENT Type="Plaintext" ID="Unknown">
    <MATCH EntityName="pii/id/nocontext/us" Offset="8" OffsetLength="8" Score="0.5" NormalizedTextSize="11" NormalizedTextLength="11" OriginalTextSize="11" OriginalTextLength="11">
      <ORIGINAL_TEXT>343-55-8575</ORIGINAL_TEXT>
      <NORMALIZED_TEXT>343-55-8575</NORMALIZED_TEXT>
    </MATCH>
    <MATCH EntityName="pii/id/nocontext/us" Offset="20" OffsetLength="20" Score="0.45" NormalizedTextSize="11" NormalizedTextLength="11" OriginalTextSize="11" OriginalTextLength="11">
      <ORIGINAL_TEXT>241 53 8573</ORIGINAL_TEXT>
      <NORMALIZED_TEXT>241 53 8573</NORMALIZED_TEXT>
    </MATCH>
    <MATCH EntityName="pii/id/nocontext/al" Offset="94" OffsetLength="94" Score="0.5" NormalizedTextSize="10" NormalizedTextLength="10" OriginalTextSize="10" OriginalTextLength="10">
      <ORIGINAL_TEXT>I05101999Q</ORIGINAL_TEXT>
      <NORMALIZED_TEXT>I05101999Q</NORMALIZED_TEXT>
      <COMPONENTS>
        <COMPONENT Name="NID" Text="I05101999Q" Offset="0" OffsetLength="0" TextSize="10" TextLength="10"/>
      </COMPONENTS>
    </MATCH>
    <MATCH EntityName="pii/id/nocontext/ar" Offset="183" OffsetLength="183" Score="0.475" NormalizedTextSize="8" NormalizedTextLength="8" OriginalTextSize="8" OriginalTextLength="8">
      <ORIGINAL_TEXT>22691903</ORIGINAL_TEXT>
      <NORMALIZED_TEXT>22691903</NORMALIZED_TEXT>
    </MATCH>
    <MATCH EntityName="pii/id/nocontext/au" Offset="223" OffsetLength="223" Score="0.75" NormalizedTextSize="9" NormalizedTextLength="9" OriginalTextSize="9" OriginalTextLength="9">
      <ORIGINAL_TEXT>AMS123456</ORIGINAL_TEXT>
      <NORMALIZED_TEXT>AMS123456</NORMALIZED_TEXT>
      <COMPONENTS>
        <COMPONENT Name="IMMICARD" Text="AMS123456" Offset="0" OffsetLength="0" TextSize="9" TextLength="9"/>
      </COMPONENTS>
    </MATCH>
  </DOCUMENT>
</MATCHLIST>
Entity search completed (T+1.004 seconds)

1.008 seconds elapsed
```

Edit the `custom_pp_threshold/config/custom_pp_threshold.cfg` to remove the second post process task 
```diff
-PostProcessingTask1 = custom_pp_threshold
```
and re-run the same edktool command as above, but with `-o out_no_custom_pp_threshold.xml`. You will get different (more) matches - with `PostProcessThreshold=0.4` when the custom_pp_threshold task is disabled.

The `custom_pp_threshold/scripts/custom_pp_threshold.lua` provides the framework for this solution and allows for it to be easily extended for use with other grammars and entities.

## Conclusion

You are now familiar with more use cases for Eduction post processing: custom match redaction and custom score threshold.

Next, why not try more tutorials to explore some of the other features available in IDOL Eduction, linked from the [main page](../README.md#idol-eduction-showcase).

## See also

- [IDOL PCI Package Technical Note](https://www.microfocus.com/documentation/idol/IDOL_23_3/EductionGrammars_23.3_Documentation/PCI/)
- [IDOL PII Package Technical Note](https://www.microfocus.com/documentation/idol/IDOL_23_3/EductionGrammars_23.3_Documentation/PII/)
- [IDOL Eduction User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_23_3/EductionSDK_23.3_Documentation/Guides/html/)
- [IDOL and KeyView OEM Release Notes](https://www.microfocus.com/documentation/idol/IDOL_23_3/IDOLReleaseNotes_23.3_Documentation/oem/Content/SDKs/Eduction.htm)