# Using the Filter SDK and Eduction SDK together via their Python APIs

The Filter SDK and Eduction SDK allows you to embed their respective functionality into other services.  Since, the Filter SDK can extract text and Eduction and read / inspect text, it is natural to use them together resulting in a powerful solution.

To facilitate embedding, the Filter SDK has APIs for C, C++, Java, .NET and Python.  In addition, the Filter SDK runs natively on the following platforms: Windows (x86_32, x86_64, ARM_64), Linux (x86_32, x86_64 and ARM_64), MacOS (x86_64 and Apple M*).  Similar APIs and platforms are supported by the Eduction SDK.

In this lesson, you will:

- Work with a sample program that illustrates how to use the Python APIs of Filter SDK and Eduction SDK together

> NOTE: This guide assumes you have already completed the introductory Filter SDK [tutorial](../keyview_filter/introduction.md#introduction-to-filter-sdk).
> NOTE: This guide assumes you have already completed the Filter SDK Python API [tutorial](../keyview_filter/programming_python.md).
> NOTE: This guide assumes you have already completed the introductory Eduction SDK [tutorial](../eduction/introduction.md#introduction-to-eduction).
> NOTE: This guide assumes you have already completed the Eduction SDK Python API [tutorial](../eduction/eduction_sdk_api_python.md).

---

- [Setup](#setup)
  - [Resources](#resources)
- [Example programs](#example-programs)
  - [`kvfilter_eduction_stream`](#kvfilter_eduction_stream)
    - [Run](#run)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Filter SDK introduction](../keyview_filter/introduction.md#introduction-to-filter-sdk) and [Eduction SDK introduction](../eduction/introduction.md#introduction-to-eduction) lessons covering essential setup steps (for example, required downloads and installation steps) and basic Filter and Eduction concepts.  Installation of Python wheels, licensekey.dat / versionkey.dat and other required topics are covered.

### Resources

You must download the following resources before you continue:

- source code for this tutorial:
  - [kvfilter_eduction_stream.py](../../resources/keyview_filter+eduction/sdk/samples/kvfilter_eduction_stream/python/kvfilter_eduction_stream.py)
  - [run_kvfilter_eduction_stream.* scripts](../../resources/keyview_filter+eduction/sdk/samples/kvfilter_eduction_stream/python/)
  - [resources](../../resources/keyview_filter+eduction/sdk/samples/kvfilter_eduction_stream)

> NOTE: Deploy the `keyview_filter+eduction` resources to the `C:\OpenText\idol-oem-tutorials\resources` folder.  This is likely already the downloaded location.

## Example programs

An example program (with resources) for using the Filter SDK Python API and the Eduction SDK Python API are delivered as [resources](../../resources/eduction/sdk) that are part of this tutorial.  The sample programs cover topics:

- passing a binary or similar file that the Filter SDK supports, extracting the text and streaming this text to Eduction

### `kvfilter_eduction_stream`

The `kvfilter_eduction_stream` sample program accepts a configuration file as you've been using in the other Eduction lessons, any input file that the Filter SDK supports and a path to the output JSON file.

#### Run

Go ahead and run `kvfilter_eduction_stream`.  A Windows batch file `run_kvfilter_eduction_stream.bat` is provided.  The Eduction related configuration is the same as the `eduction_from_config\resources\test` with a PDF representation of input.txt used as the default input to `run_kvfilter_eduction_stream.bat`.

> NOTE: Before proceeding make sure that `VERSION`, `PLATFORM`, `PYTHON_HOME` and other paths in `run_kvfilter_eduction_stream.bat` are correct for your environment.

```sh
> cd C:\OpenText\idol-oem-tutorials\resources\keyview_filter+eduction\sdk\samples\kvfilter_eduction_stream\python
Creating Filter SDK session.
Using the license key: C:\OpenText\KeyViewFilterSDK_25.1.0_WINDOWS_X86_64\licensekey.dat
Creating EDK Factory.
Using Eduction license key: C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\licensekey.dat
Using Eduction version key: C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\versionkey.dat
Creating EDK Engine from config: test\config\test.cfg
Successfully configured 1 post-processing tasks.
Creating EDK Session and processing input stream.
```

Review `educed.EDK.JSON` to see the match information. The program should run and produce an output file containing two matches, as follows:

```json
{
"matches": [
{
  "name": "test/two_words",
  "original": "foo bar",
  "offset": 15,
  "components": [
    {
      "name": "FIRST",
      "text": "foo",
      "offset": 0
    },
    {
      "name": "SECOND",
      "text": "bar",
      "offset": 4
    }
  ]
},
{
  "name": "test/two_words",
  "original": "baz bah",
  "offset": 23,
  "components": [
    {
      "name": "FIRST",
      "text": "baz",
      "offset": 0
    },
    {
      "name": "SECOND",
      "text": "bah",
      "offset": 4
    }
  ]
}
]}
```

For extra credit, try `kvfilter_eduction_stream` on other Eduction configurations and/or other input files.

Review the `kvfilter_eduction_stream.py` Python source code to gain more insights into how to use the Filter SDK and Eduction SDK together in your application.

## Conclusion

You have now used the Filter SDK API for Python to automatically detect the file format, extract text and pass that extracted text to the Eduction SDK API for Python resulting in powerful solution that combines these SDKs.

Next, why not try more tutorials to explore some of the other lessons in the Filter SDK + Eduction SDK lesson, linked from [here](../keyview_filter+eduction/README.md#use-the-filter-sdk-and-eduction-sdk).

## See also

- [Filter SDK Python Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/KeyviewFilterSDK_25.1_Documentation/Guides/html/python-programming/)
- [Release Notes](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/IDOLReleaseNotes_25.1_Documentation/oem/Content/_KeyView.htm)
- [Eduction SDK User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionSDK_25.1_Documentation/Guides/html/)
- [Release Notes](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/IDOLReleaseNotes_25.1_Documentation/oem/Content/_KeyView.htm)
- [Eduction Release Notes](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/IDOLReleaseNotes_25.1_Documentation/idol/Content/SDKs/Eduction.htm)
