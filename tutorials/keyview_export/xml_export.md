# XML Export

As we saw in the introduction lesson for Export SDK, .....

In this lesson, you will:

- Explore more about Export SDK's XML output, using `xmlini` with the sample `ini` files.


---

- [Setup](#setup)
  - [Resources](#resources)
- [Use XML Export](#use-xml-export)
  - [Use `xmlini`](#use-xmlini)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Export SDK introduction](./introduction.md) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Export SDK concepts.

### Resources

Be sure to download the following resources before you continue:

- scripts from [here](../../resources/keyview_export/) and install to `C:\OpenText\idol-oem-tutorials\resources`

Sample files are provided in the `testdocs` folder of ExportSDK.

## Use XML Export

### Use `xmlini`

In the introduction lesson [`cnv2xml`](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/xml-export-c/Content/C/samples_export/cnv2xml.htm) was used to render XML from supported file formats.  The configuration used by `cnv2xml` takes a one-size fits all approach.  [`xmlini`](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/xml-export-c/Content/C/samples_export/xmlini.htm) lets you provide an `ini` file to tailor the XML output.

[Explore Conversion Options with the Sample Programs](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/xml-export-c/Content/export/GettingStarted/Set_Conversion_Options.htm#Template) provides of the provided `ini` files. Review this section now.

Let's run `xmlini` using the provided resource `run_xmlini.bat`.

> NOTE: In `run_xmlini.bat`, be sure to edit the paths for your environment, to select input file and ini file.

```sh
> cd C:\OpenText\idol-oem-tutorials\resources\keyview_export
> run_xmlini.bat
Input file:  C:\OpenText\KeyviewExportSDK_25.4.0_WINDOWS_X86_64\testdocs\Annual_Report.docx
Output file:  C:\OpenText\KeyviewExportSDK_25.4.0_WINDOWS_X86_64\testdocs\Annual_Report.docx.xml1file.XML
Ini file: C:\OpenText\KeyviewExportSDK_25.4.0_WINDOWS_X86_64\xmlexport\programs\ini\xml1file.ini

WARNING: xmlini is a sample program only and is not for production use
Conversion to XML completed.

Allocated memory not freed      = 0 bytes.
Maximum memory used             = 0 bytes.

```

Note the paths above and view the XML output in your favorite text editor or XML viewer.

For more information on `ini` file contents, refer to [Set Conversion Options](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/xml-export-c/Content/export/GettingStarted/Set_Conversion_Options.htm?Highlight=xml_index) and [KVXMLOptions](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/xml-export-c/Content/C/ExportAPIStructures/KVXMLOptions.htm?Highlight=xml_index.ini)

Try other source files and provide XMLExport ini files.

> NOTE: If you use `xml_index.ini`, it is recommended to add the following lines to insure the output character set has a more useful value:
```diff
+[KVXMLOptions]
+eOutputCharSet=KVCS_UTF8
+bForceOutputCharSet=TRUE
```

## Conclusion

By using `xmlini`, you've seen how the XML output can vary based on the provided `ini` configuration that controls `KVXMLOptions`.  Optimizing the `KVXMLOptions` for your use case is a next step.

## See also

- [XML Export SDK C Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/xml-export-c/index.html)
- [XML Export SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/xml-export-java/)
- [File Content Extraction Release Notes](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/oem/Content/_KeyView.htm)
