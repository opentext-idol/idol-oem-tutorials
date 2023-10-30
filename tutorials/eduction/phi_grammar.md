# Use PHI Eduction grammars

The IDOL PHI Package contains tools that allow you to locate Protected Healthcare Information in your data, to help you comply with regulations in the U.S. Health Insurance Portability and Accountability Act (HIPAA).

In this lesson, you will:

- Explore and use the out-of-the-box PHI grammars.
- Gain deeper understanding of engine configuration file options.

> NOTE: This guide assumes you have already completed the introductory Eduction [tutorial](./introduction.md#eduction-sdk-introduction).

---

- [Setup](#setup)
  - [Resources](#resources)
- [What's in the Box?](#whats-in-the-box)
  - [Available Grammar Files](#available-grammar-files)
  - [Types of Entities](#types-of-entities)
- [Run PHI All Example Matching](#run-phi-all-example-matching)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Eduction SDK introduction](../eduction/introduction.md#eduction-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Eduction concepts.

> NOTE: In the `EductionGrammars_23.2_COMMON.zip`, the `phi\scripts\validation_scripts.lua` needs a correction as noted below:
```diff
-ndc_us={processs="validate_ndc"},
+ndc_us={process="validate_ndc"},
```

### Resources

Be sure to download the following resources before you continue:
- [PHI edk_samples](../../resources/eduction/phi/edk_samples) and install to `C:\OpenText\EductionGrammars_23.4.0_COMMON\phi\edk_samples\resources`

## What's in the Box?

The IDOL PHI Package includes IDOL Eduction Grammar files, postprocessing scripts (*e.g.* checksum & additional validation, output & score normalization and filtering) for certain entities.

### Available Grammar Files

To review which grammar files are included, list the directory `C:\OpenText\EductionGrammars_23.4.0_COMMON\phi`. The command `edktool list -a <grammar>.ecr ` can be used to explore the public entities, available components and license requirements. Or open the `phi_entities.html` file in your web browser. This `.html` file conveniently lists available entities by locale as well as grammar file name.

There is some apparent overlap with some of the grammars & entities in the PII Package.  The primary difference excluding the net new grammars (e.g. `age.ecr, dea.ecr, device.ecr` and others) and entities available in the PHI Package is that the PHI grammars are focused on the United States.

### Types of Entities

The PHI grammar files provide entities of the "context", "nocontext" and "landmark" forms like the PII, PCI and Gov packages do.

For the PHI date entities, like `phi/date/dob/*`, "context", "nocontext" and "landmark" options are available in order to match the recall and precision goals to the use case. Consider that the "nocontext" version might over-match significantly (*i.e.*, we are likely to return values that are similar to the entity patterns, such as a last updated date).

For full details of the entities included in the PHI Grammar Package, please reference the [PHI Package Technical Note](https://www.microfocus.com/documentation/idol/IDOL_23_4/EductionGrammars_23.4_Documentation/PHI/Content/PHI/PHI_GrammarReference.htm).

> NOTE: You can configure Eduction to use either versions of an entity, in which case matches located with context are given a higher score in the results.

## Run PHI All Example Matching

In the setup, you deployed edk_samples resources.  It contains resources to be used with the Eduction APIs and edktool: `phi\edk_samples\resources\phi_all\config\phi_all.cfg`. 

Run the following commands to see the output:

```sh
> cd C:\OpenText\EductionGrammars_23.4.0_COMMON\phi\edk_samples\resources
> edktool extract -l ..\..\..\..\EductionSDK_23.4.0_WINDOWS_X86_64\licensekey.dat -c phi_all\config\phi_all.cfg -i phi_all\input\input.txt -o out.xml
```

The `phi_all.cfg` configuration and `input.txt` represent all available entity categories in the `PHI Package`, but does intentional select "nocontext" vs "context" for particular entity categories.  In some cases both entity forms are enabled - *e.g.* `Entity21 = phi/inet/ip/*context` using a simple wildcard expression `*`.

The `phi_all.cfg` also enables [AllowOverlaps](https://www.microfocus.com/documentation/idol/IDOL_23_4/EductionSDK_23.4_Documentation/Guides/html/Content/Configuration/Eduction/_EDU_AllowOverlaps.htm). This allows for multiple entities to match part of (or the entirety of) the same input text.  An example of this in the `phi_all\input\input.txt` is:
```
email: jsmith@mailserver.com
```
which matches 3 distinct entities as the following with `AllowOverlaps = True`:

```xml
<MATCH EntityName="phi/inet/email/context" Offset="972" OffsetLength="972" Score="1" NormalizedTextSize="21" NormalizedTextLength="21" OriginalTextSize="28" OriginalTextLength="28">
  <ORIGINAL_TEXT>email: jsmith@mailserver.com</ORIGINAL_TEXT>
  <NORMALIZED_TEXT>jsmith@mailserver.com</NORMALIZED_TEXT>
  <COMPONENTS>
    <COMPONENT Name="LOCAL" Text="jsmith" Offset="0" OffsetLength="0" TextSize="6" TextLength="6"/>
    <COMPONENT Name="DOMAIN" Text="mailserver.com" Offset="7" OffsetLength="7" TextSize="14" TextLength="14"/>
  </COMPONENTS>
</MATCH>
<MATCH EntityName="phi/inet/email/nocontext" Offset="979" OffsetLength="979" Score="1" NormalizedTextSize="21" NormalizedTextLength="21" OriginalTextSize="21" OriginalTextLength="21">
  <ORIGINAL_TEXT>jsmith@mailserver.com</ORIGINAL_TEXT>
  <NORMALIZED_TEXT>jsmith@mailserver.com</NORMALIZED_TEXT>
  <COMPONENTS>
    <COMPONENT Name="LOCAL" Text="jsmith" Offset="0" OffsetLength="0" TextSize="6" TextLength="6"/>
    <COMPONENT Name="DOMAIN" Text="mailserver.com" Offset="7" OffsetLength="7" TextSize="14" TextLength="14"/>
  </COMPONENTS>
</MATCH>
<MATCH EntityName="phi/inet/url/nocontext" Offset="986" OffsetLength="986" Score="1" NormalizedTextSize="14" NormalizedTextLength="14" OriginalTextSize="14" OriginalTextLength="14">
  <ORIGINAL_TEXT>mailserver.com</ORIGINAL_TEXT>
  <NORMALIZED_TEXT>mailserver.com</NORMALIZED_TEXT>
  <COMPONENTS>
    <COMPONENT Name="HOST" Text="mailserver.com" Offset="0" OffsetLength="0" TextSize="14" TextLength="14"/>
  </COMPONENTS>
</MATCH>
```

For extra credit change the `phi_all\config\phi_all.cfg` to set `AllowOverlaps = False` and re-run `edktool` but output to `out2.xml` so you can easily compare the output.
> HINT: For `email: jsmith@mailserver.com` only `phi/inet/email/context` will match with `AllowOverlaps = False`.

Another noteworthy example with `AllowOverlaps=True` occurs with `phi/id/*context/us`: 

```xml
<MATCH EntityName="phi/id/context/us" Offset="1202" OffsetLength="1202" Score="1" NormalizedTextSize="11" NormalizedTextLength="11" OriginalTextSize="16" OriginalTextLength="16">
  <ORIGINAL_TEXT>SSN: 534-33-4394</ORIGINAL_TEXT>
  <NORMALIZED_TEXT>534-33-4394</NORMALIZED_TEXT>
  <COMPONENTS>
    <COMPONENT Name="ID_LANDMARK" Text="SSN" Offset="0" OffsetLength="0" TextSize="3" TextLength="3"/>
  </COMPONENTS>
</MATCH>
<MATCH EntityName="phi/id/nocontext/us" Offset="1207" OffsetLength="1207" Score="0.5" NormalizedTextSize="11" NormalizedTextLength="11" OriginalTextSize="11" OriginalTextLength="11">
  <ORIGINAL_TEXT>534-33-4394</ORIGINAL_TEXT>
  <NORMALIZED_TEXT>534-33-4394</NORMALIZED_TEXT>
</MATCH>
<MATCH EntityName="phi/id/context/us" Offset="1219" OffsetLength="1219" Score="0.9" NormalizedTextSize="11" NormalizedTextLength="11" OriginalTextSize="16" OriginalTextLength="16">
  <ORIGINAL_TEXT>SSN: 534 33 4393</ORIGINAL_TEXT>
  <NORMALIZED_TEXT>534 33 4393</NORMALIZED_TEXT>
  <COMPONENTS>
    <COMPONENT Name="ID_LANDMARK" Text="SSN" Offset="0" OffsetLength="0" TextSize="3" TextLength="3"/>
  </COMPONENTS>
</MATCH>
<MATCH EntityName="phi/id/context/us" Offset="1236" OffsetLength="1236" Score="0.8" NormalizedTextSize="9" NormalizedTextLength="9" OriginalTextSize="14" OriginalTextLength="14">
  <ORIGINAL_TEXT>SSN: 534334392</ORIGINAL_TEXT>
  <NORMALIZED_TEXT>534334392</NORMALIZED_TEXT>
  <COMPONENTS>
    <COMPONENT Name="ID_LANDMARK" Text="SSN" Offset="0" OffsetLength="0" TextSize="3" TextLength="3"/>
  </COMPONENTS>
</MATCH>
```

For `phi/id/nocontext/us`, only the match `534-33-4394` is produced due to the `PostProcessThreshold = 0.5`.

## Conclusion

You now understand how to explore and use the IDOL Eduction's PHI grammars, how wildcard expressions can be used in the Eduction engine configuration and also the impact of the `AllowOverlaps` setting.

Next, why not try more tutorials to explore some of the other features available in IDOL Eduction, linked from the [main page](../README.md#idol-eduction-showcase).

## See also

- [IDOL PHI Package Technical Note](https://www.microfocus.com/documentation/idol/IDOL_23_4/EductionGrammars_23.4_Documentation/PHI/)
- [IDOL Eduction User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_23_4/EductionSDK_23.4_Documentation/Guides/html/)
- [IDOL and KeyView OEM Release Notes](https://www.microfocus.com/documentation/idol/IDOL_23_4/IDOLReleaseNotes_23.4_Documentation/idol/Content/SDKs/Eduction.htm)