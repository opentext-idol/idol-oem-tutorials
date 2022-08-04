# Extract Table Oriented Data

Eduction has a mode called `Table mode` that makes Eduction aware of columns and column headings.  Spreadsheet and CSV files are examples of data that represent data in rows and columns, typically with column headings.  With Eduction `Table mode`, matching will be able to differentiate between say a `date of birth` and `last updated date` because of the column heading.

For more details on this topic, reference the [Extract Entities from Tables](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionSDK_12.12_Documentation/Guides/html/Content/UseEduction/ImproveMatches/Extract_Table_Data.htm?Highlight=table) section of the Eduction reference guide.

In this lesson, you will:
- Perform `table mode` extraction with `edktool`
- Explore the input resources and output results for the table extraction sample.
- Optionally experiment with changes to `input.csv` and see if/how output changes.

> NOTE: This guide assumes you have already completed the introductory Eduction [tutorial](./introduction.md#eduction-sdk-introduction).

---

- [Setup](#setup)
  - [Resources](#resources)
- [Perform `table mode` extraction](#perform-table-mode-extraction)
  - [`input\input.csv`](#inputinputcsv)
  - [`config\test.cfg`](#configtestcfg)
  - [`grammar\test.xml`](#grammartestxml)
  - [`out.xml`](#outxml)
- [Next Steps (optional)](#next-steps-optional)
- [PII `table mode` example](#pii-table-mode-example)
  - [Perform PII `table mode` extraction](#perform-pii-table-mode-extraction)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup
Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Eduction SDK introduction](../eduction/introduction.md#eduction-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Eduction concepts.

### Resources

Be sure to download the following resources before you continue:
- [PII edk_samples](../../resources/eduction/pii/edk_samples) and install to `C:\MicroFocus\EductionGrammars_12.12.0_COMMON\pii\edk_samples\resources`

## Perform `table mode` extraction

The Eduction SDK contains a working example under `samples\table_extraction`. Since this lesson uses `edktool` to perform the extraction only the `samples\table_extraction\resources` sub-folders are of interest for now.

Go ahead and perform extract with `edktool` and we'll explore the inputs and output in more detail below.

```sh
> cd  C:\MicroFocus\EductionSDK_12.12.0_WINDOWS_X86_64\samples\table_extraction\resources
> edktool extract -l ..\..\..\licensekey.dat -c test\config\test.cfg -i test\input\input.csv -o out.xml
```

Let's connect the dots between the `test\config\test.cfg`, `test\grammar\test.xml` and `test\input\input.csv'.

### `input\input.csv`

The `test\input\input.csv` is pretty simple containing 3 columns and 4 rows with the first row containing the header and the rest representing the data.
```
Name,Number,Location
Adam,1,London
Ben,92,New York
Charles,pi,Peckham
```

### `config\test.cfg`

The `test\config\test.cfg` is also pretty simple, but contains some unique settings particular to `table mode`
```
[Eduction]
ResourceFiles=../resources/test/grammar/test.xml
HeaderEntity0=simple_pii/name_header
CellEntity0=simple_pii/name
HeaderEntity1=simple_pii/number_header
CellEntity1=simple_pii/number
HeaderEntity2=simple_pii/location_header
CellEntity2=simple_pii/location
MatchCase=FALSE
AllowMultipleResults=All
EnableComponents=TRUE
```

The `HeaderEntity#` and `CellEntity#` reference the header and value entities as defined in `test\grammar\test.xml`.

> NOTE: If you're curious, why `ResourceFiles` reference test.xml vs test.ecr, both the XML source and compiled ECR are supported. When XML source is used it gets compiled as the EDKEngine is initialized.  This is functional but less efficient than compiled ECR.

### `grammar\test.xml`

The `test\grammar\test.xml` is pretty simple defining 3 column headers and 3 value entities that correspond with the header entities.

### `out.xml`

The `out.xml` has matches for all 3 column headers, 3 matches for `name`, 2 matches for `number` and 2 matches for `location`.  This is because 'pi' isn't a number and 'Peckham' isn't defined in the `location` entity.

## Next Steps (optional)

If you'd like you can make changes to `test.xml` and/or `input.csv`.  Here's some ideas:
- Create a fourth column called age and put numbers in it. Hint: none of those number values will match since only the 'number' column allows for numbers.
- Add fictitious locations like 'Charles Town' or 'Mount Adam' to `input.csv` to the 'location' column.  Hint: these values will not match since only the 'name' column allows for numbers.

## PII `table mode` example

In the Eduction SDK documentation section [Extract Entities from Tables](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionSDK_12.12_Documentation/Guides/html/Content/UseEduction/ImproveMatches/Extract_Table_Data.htm?Highlight=cell) the PII date.ecr is used in the example.  This lesson builds upon the documentation including PII `national_id.ecr` in the configuration and providing sample `input.csv` file.

In the [setup](#setup), you downloaded the `pii_table_mode` resources. Two Eduction configuration files are provided: 
- `pii_table_mode.cfg` - enables entities from date.ecr and national_id.ecr
- `date.cfg` - enables date entities like `pii_table_mode.cfg` but without the `table mode` configuration

The `input.csv` file has two date columns: "Date of Birth" and "Admission Date" as one might see in medical or health insurance records. For the purpose of this lesson only the "Date of Birth" column and the "SSN" are of interest.  The "Name" column and thus `name.ecr` are excluded intentionally from this lesson to simplify things. In practice, for PII and PHI use cases, name, national id and date of birth would all be of interest.

### Perform PII `table mode` extraction

Run `edktool extract` using the same `input.csv` file with each of the `config` folder configurations.

```sh
> cd  C:\MicroFocus\EductionGrammars_12.12.0_COMMON\pii\edk_samples\resources
> edktool extract -l ..\..\..\..\licensekey.dat -c pii_table_mode\config\pii_table_mode.cfg -i pii_table_mode\input\input.csv -o table_mode.xml

> edktool extract -l ..\..\..\..\licensekey.dat -c pii_table_mode\config\date.cfg -i pii_table_mode\input\input.csv -o no_table_mode.xml
```

You will get the following matches:
- `no_table_mode.xml`: 4 total matches with 2 for the dates of birth and 2 for the admission date.
- `table_mode.xml`: 6 total matches with 2 for the landmarks, 2 for the dates of birth and 2 for the SSNs.

Eduction `table mode` was able to distinguish between the 2 types of dates by keying of the CSV column header. It performed similarly  for the U.S. national ID # (SSN).

## Conclusion

You now understand the basics of Eduction `table mode` and how it can reduce false positives for spreadsheet and CSV type data.  You have also explored a PII/PHI use case for `table mode` with a simple, but still useful configuration.

Next, why not try more tutorials to explore some of the other features available in IDOL Eduction, linked from the [main page](../README.md#capability-showcase-examples).

## See also

- [IDOL Eduction SDK User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionSDK_12.12_Documentation/Guides/html)
