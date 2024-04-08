# Create custom Eduction grammars

While there are number of pre-built grammar packages available to use with Eduction, two additional scenarios are supported related to custom grammars:
1. Net-new ones representing entities not available in pre-built packages
1. Extending pre-built entities to improve their match behavior

In this lesson, you will:
- compile and verify multiple grammar examples
- extend an existing grammar

> NOTE: This guide assumes you have already completed the introductory Eduction [tutorial](./introduction.md#eduction-sdk-introduction).

---

- [Setup](#setup)
- [Compile and Verify](#compile-and-verify)
  - [Simple example](#simple-example)
  - [Complex example](#complex-example)
  - [`grammar.xml` and `grammar_include.xml`](#grammarxml-and-grammar_includexml)
- [Extending an existing grammar](#extending-an-existing-grammar)
  - [Extend PII Name](#extend-pii-name)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the documentation links [below](#see-also).

> NOTE: This lesson assumes you have already completed the [Eduction SDK introduction](./introduction.md#eduction-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Eduction concepts.

## Compile and Verify

### Simple example

Let's start with the mechanics of compiling grammar XML source into an ECR.

```sh
> cd C:\OpenText\EductionSDK_24.2.0_WINDOWS_X86_64\samples\compile\resources\test
> edktool compile -l ..\..\..\..\licensekey.dat -i source\test.xml -o test.ecr

Eduction EDKTool Utility v24.2.0
Compiling:
  source\test.xml
into:
  test.ecr
using the license:
  ..\..\..\..\licensekey.dat

Compilation successful.

0.036 seconds elapsed
```

To verify the compilation and check which entities are declared as public, let's list the ECRs contents.

```sh
> edktool list -a test.ecr

Eduction EDKTool Utility v24.2.0
Loading resource file:
test.ecr


Grammar version:        4.0

Compiled using Edktool: 24.2.0

Listing entities:
test/two_words
    components: "FIRST" "SECOND"

Listing all necessary requirements for license:
    (none)

0.018 seconds elapsed
```

This looks like the source to test.ecr used in [Eduction introduction](./introduction.md#introduction-to-eduction) lesson.  As extra credit, run extract with the new `test.ecr`.

```sh
> edktool extract -l ..\..\..\..\licensekey.dat -g test.ecr -i ..\..\..\eduction_from_config\resources\test\input\input.txt
```

> NOTE: `EductionSDK_24.2.0_WINDOWS_X86_64\samples\compile` also has sample code illustrating how to use APIs to compile a grammar. 
 
### Complex example

The Eduction User and Programming Guide has excellent sections on this [topic](https://www.microfocus.com/documentation/idol/IDOL_24_2/EductionSDK_24.2_Documentation/Guides/html/Content/UseEduction/Grammars/GrammarFormat.htm), which will be relied upon heavily in this section of the lesson.

### `grammar.xml` and `grammar_include.xml`

The [grammar.xml](https://www.microfocus.com/documentation/idol/IDOL_24_2/EductionSDK_24.2_Documentation/Guides/html/Content/UseEduction/Grammars/grammar_xml.htm) and [grammar_include.xml](https://www.microfocus.com/documentation/idol/IDOL_24_2/EductionSDK_24.2_Documentation/Guides/html/Content/UseEduction/Grammars/grammar_include_xml.htm) example illustrates many interesting Eduction concepts:
- including another grammar file
- public and private entity scope
- headword / synonym and pattern for entity definition
- entity and pattern scoring
- patterns that reference another entity

As extra credit, copy and paste from the documentation into your own grammar.xml and grammar_include.xml files and compile, verify and test.

> HINT: Use UTF-8 capable editor and run `edktool compile -l <PATH_TO_LICENSEKEY.DAT> -i grammar.xml` produces 3 public entities.

## Extending an existing grammar

Grammars and entities contained within are kind of programming objects in that they can be inherited and extended. This allows for you to make net-new entities more quickly leveraging say `EductionGrammars_24.2.0_COMMON\general\grammars\date_spa.ecr` to make your own `datetime_advanced_spa.ecr` or improve the behavior of existing grammars by say adding to `PII pii/name/surname/nocontext/CC` to improve matching / scoring of PII name.

Before you continue with this part of the lesson, refer to these documentation links:

- [Extend Grammars](https://www.microfocus.com/documentation/idol/IDOL_24_2/EductionSDK_24.2_Documentation/Guides/html/Content/UseEduction/Grammars/Extend_Grammars.htm) section of the Eduction User and Programming Guide.
- [PII Grammar Customization](https://www.microfocus.com/documentation/idol/IDOL_24_2/EductionGrammars_24.2_Documentation/PII/Content/GrammarCustomization.htm)

### Extend PII Name

*Example 3: New Name and Custom Separator* of the [PII Grammar Customization](https://www.microfocus.com/documentation/idol/IDOL_24_2/EductionGrammars_24.2_Documentation/PII/Content/GrammarCustomization.htm) provides example on how to extend `given_name`, `surname` and use a custom separate in the `/nocontext/` form.

1. Copy & paste the XML in the documentation into `name_extended.xml` using UTF-8 capable editor.
   
2. You will likely need to change `path` attribute of `<include ...>` like the following:
    ```diff
    - <include path="name.ecr"/>
    + <include path="C:\OpenText\EductionGrammars_24.2.0_COMMON\PII\name.ecr"/>
    ```

3. Run `edktool compile` on `name_extend.xml`
    ```sh
    > edktool compile -l C:\OpenText\EductionSDK_24.2.0_WINDOWS_X86_64\licensekey.dat -i name_extended.xml 

    Eduction EDKTool Utility v24.2.0
    Compiling:
      name_extended.xml
    into:
      name_extended.ecr
    using the license:
      C:\OpenText\IDOLServer-24.2.0\EductionSDK_24.2.0_WINDOWS_X86_64\licensekey.dat

    Compilation successful.

    72.516 seconds elapsed
    ```

4. Using UTF-8 editor, create an `input.txt`
    ```
    Fobo Jones 

    Jane Fobo 

    and for fun Fobo Jobo, plus Jobo@@Fobo
    ```

5. Create `name_extended.cfg` from `EductionGrammars_24.2.0_COMMON\pii\config\edktool.cfg`
    ```diff
    -ResourceFiles = combined_address.ecr,combined_banking.ecr,combined_date.ecr,combined_driving.ecr,combined_health.ecr,combined_medical_terms.ecr,combined_name.ecr,combined_national_id.ecr,combined_nationality.ecr,combined_passport.ecr,combined_postcode.ecr,combined_tin.ecr,combined_travel.ecr
    +ResourceFiles=name_extended.ecr
    - Entity0 = pii/address/all,pii/banking/context/all,pii/banking/iban/context/all,pii/banking/swiftcode/context/all,pii/date/dob/context/all,pii/driving/context/all,pii/health/ehic/context/all,pii/health/id/context/all,pii/medical_terms/all,pii/name/all,pii/id/context/all,pii/nationality/any/context/all,pii/passport/context/all,pii/postcode/context/all,pii/tin/context/all,pii/tin/vatin/context/all,pii/travel/context/all
    +Entity0 = pii/name/gb
    -Script = scripts/pii_postprocessing.lua
    +Script = C:\OpenText\EductionGrammars_24.2.0_COMMON\pii\scripts\pii_postprocessing.lua
    ```

6.  Run `edktool extract`:
    ```sh
    > edktool extract -l C:\OpenText\EductionSDK_24.2.0_WINDOWS_X86_64\licensekey.dat -c name_extended.cfg -i input.txt -o out_extended.xml

    Eduction EDKTool Utility v24.2.0
    ...
    Entity search completed (T+2.623 seconds)

    2.637 seconds elapsed

    <?xml version="1.0" encoding="UTF-8"?>
    <MATCHLIST>
    <DOCUMENT Type="Plaintext" ID="Unknown">
    <MATCH EntityName="pii/name/gb" Offset="0" OffsetLength="0" Score="1" NormalizedTextSize="10" NormalizedTextLength="10" OriginalTextSize="10" OriginalTextLength="10">
      <ORIGINAL_TEXT>Fobo Jones</ORIGINAL_TEXT>
      <NORMALIZED_TEXT>FOBO JONES</NORMALIZED_TEXT>
      <COMPONENTS>
        <COMPONENT Name="FORENAME" Text="FOBO" Offset="0" OffsetLength="0" TextSize="4" TextLength="4"/>
        <COMPONENT Name="SURNAME" Text="JONES" Offset="5" OffsetLength="5" TextSize="5" TextLength="5"/>
      </COMPONENTS>
    </MATCH>
    <MATCH EntityName="pii/name/gb" Offset="13" OffsetLength="13" Score="0.6" NormalizedTextSize="9" NormalizedTextLength="9" OriginalTextSize="9" OriginalTextLength="9">
      <ORIGINAL_TEXT>Jane Fobo</ORIGINAL_TEXT>
      <NORMALIZED_TEXT>JANE FOBO</NORMALIZED_TEXT>
      <COMPONENTS>
        <COMPONENT Name="FORENAME" Text="JANE" Offset="0" OffsetLength="0" TextSize="4" TextLength="4"/>
        <COMPONENT Name="SURNAME" Text="FOBO" Offset="5" OffsetLength="5" TextSize="4" TextLength="4"/>
      </COMPONENTS>
    </MATCH>
    <MATCH EntityName="pii/name/gb" Offset="37" OffsetLength="37" Score="1" NormalizedTextSize="9" NormalizedTextLength="9" OriginalTextSize="9" OriginalTextLength="9">
      <ORIGINAL_TEXT>Fobo Jobo</ORIGINAL_TEXT>
      <NORMALIZED_TEXT>FOBO JOBO</NORMALIZED_TEXT>
      <COMPONENTS>
        <COMPONENT Name="FORENAME" Text="FOBO" Offset="0" OffsetLength="0" TextSize="4" TextLength="4"/>
        <COMPONENT Name="SURNAME" Text="JOBO" Offset="5" OffsetLength="5" TextSize="4" TextLength="4"/>
      </COMPONENTS>
    </MATCH>
    <MATCH EntityName="pii/name/gb" Offset="53" OffsetLength="53" Score="1" NormalizedTextSize="9" NormalizedTextLength="9" OriginalTextSize="10" OriginalTextLength="10">
      <ORIGINAL_TEXT>Jobo@@Fobo</ORIGINAL_TEXT>
      <NORMALIZED_TEXT>FOBO JOBO</NORMALIZED_TEXT>
      <COMPONENTS>
        <COMPONENT Name="SURNAME" Text="JOBO" Offset="0" OffsetLength="0" TextSize="4" TextLength="4"/>
        <COMPONENT Name="FORENAME" Text="FOBO" Offset="6" OffsetLength="6" TextSize="4" TextLength="4"/>
      </COMPONENTS>
    </MATCH>
    </DOCUMENT>
  </MATCHLIST>
    ```

    You should get 4 matches for the `pii/name/gb` entity.

7. Create a `name.cfg` using the OOTB `pii\name.ecr` and run `edktool extract` with `name.cfg` where you'll get 2 matches with `name.txt`
    ```sh
    > edktool extract -l C:\OpenText\EductionSDK_24.2.0_WINDOWS_X86_64\licensekey.dat -c name.cfg -i name.txt -o out.xml

    Eduction EDKTool Utility v24.2.0
    ...
    Entity search completed (T+2.623 seconds)

    2.637 seconds elapsed

    <?xml version="1.0" encoding="UTF-8"?>
    <MATCHLIST>
      <DOCUMENT Type="Plaintext" ID="Unknown">
        <MATCH EntityName="pii/name/gb" Offset="1" OffsetLength="1" Score="0.6" NormalizedTextSize="10" NormalizedTextLength="10" OriginalTextSize="10" OriginalTextLength="10">
          <ORIGINAL_TEXT>Fobo Jones</ORIGINAL_TEXT>
          <NORMALIZED_TEXT>FOBO JONES</NORMALIZED_TEXT>
          <COMPONENTS>
            <COMPONENT Name="FORENAME" Text="FOBO" Offset="0" OffsetLength="0" TextSize="4" TextLength="4"/>
            <COMPONENT Name="SURNAME" Text="JONES" Offset="5" OffsetLength="5" TextSize="5" TextLength="5"/>
          </COMPONENTS>
        </MATCH>
        <MATCH EntityName="pii/name/gb" Offset="14" OffsetLength="14" Score="0.6" NormalizedTextSize="9" NormalizedTextLength="9" OriginalTextSize="9" OriginalTextLength="9">
          <ORIGINAL_TEXT>Jane Fobo</ORIGINAL_TEXT>
          <NORMALIZED_TEXT>JANE FOBO</NORMALIZED_TEXT>
          <COMPONENTS>
            <COMPONENT Name="FORENAME" Text="JANE" Offset="0" OffsetLength="0" TextSize="4" TextLength="4"/>
            <COMPONENT Name="SURNAME" Text="FOBO" Offset="5" OffsetLength="5" TextSize="4" TextLength="4"/>
          </COMPONENTS>
        </MATCH>
      </DOCUMENT>
    </MATCHLIST>
    ```

You may wonder why `name.ecr` produced 2 matches instead of 0 matches for the seemingly fictitious names used in `name.txt`.  While both `name_extended.ecr` and `name.ecr` produce matches the score is higher with `name_extended.ecr` - 1.0 vs 0.6. This is because the pii/name/CC pattern is smart in that generic given names and surnames when combined with known name parts is still considered a name but with relatively less confidence.  It would be practically impossible to define every possible given name and surname - increasing memory and cpu use to match.  Plus these lists are forever changing.  So `pii/name/CC` has patterns that does "fuzzy" name matching thus finding the balance between precision / recall and system resource utilization.

The 3rd match is due to the additions to `pii/name/given_name/context/gb` and `pii/name/surname/context/gb`. The 4th match produced by `name_extended.ecr` is of course due to the `@@` delimiter that was added in `name_extended.xml`.

## Conclusion

You now understand the mechanics of compiling a grammar, verifying available entities and creating a new grammar either from scratch or extending existing one.

Next, why not try more tutorials to explore some of the other features available in IDOL Eduction, linked from the [main page](../README.md#idol-eduction-showcase).

## See also

- [Create and Modify Eduction Grammars](https://www.microfocus.com/documentation/idol/IDOL_24_2/EductionSDK_24.2_Documentation/Guides/html/Content/UseEduction/Grammars/GrammarFormat.htm)
- [Compile and Test Grammars](https://www.microfocus.com/documentation/idol/IDOL_24_2/EductionSDK_24.2_Documentation/Guides/html/Content/UseEduction/CompileTest/CompileTest.htm)
- [Grammar Format Reference](https://www.microfocus.com/documentation/idol/IDOL_24_2/EductionSDK_24.2_Documentation/Guides/html/Content/Reference/GrammarReference/grammarReference.htm)
- [edktool Options - Compile](https://www.microfocus.com/documentation/idol/IDOL_24_2/EductionSDK_24.2_Documentation/Guides/html/Content/Reference/edktool/Compile.htm)
