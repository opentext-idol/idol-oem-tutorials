# C ACI API Sample Code

The C ACI API sample code resources build upon the information in the [ACI API Programming Guide - C Language Interface](https://www.microfocus.com/documentation/idol/IDOL_24_3/IDOLJavaSDK_24.3_Documentation/Guides/html/Content/C/c_part.htm) providing working examples to interact with IDOL ACI services. 

The various examples contain source code and build scripts for Windows and Linux.

The `/bin/<PLATFORM>` folders contains executables for Windows and Linux built with `USE_IDOL_OEM_ENCRYPTION = true`. However, since the provided exes are built with `USE_IDOL_OEM_ENCRYPTION = true`, the `do_run_*.*` scripts need to be updated with your issued OEM style license key.

The `/src/<example>` folders contains the source code and build tools.

---

- [Setup](#setup)
  - [Setup - Build](#setup---build)
  - [Setup - Run](#setup---run)
  - [Required third-party tools](#required-third-party-tools)
- [getStatus](#getstatus)
- [fetch\_synchronize](#fetch_synchronize)
- [fetch\_identifiers](#fetch_identifiers)
- [fetch\_collect](#fetch_collect)
- [fetch\_delete](#fetch_delete)
- [fetch\_insert](#fetch_insert)
- [fetch\_update](#fetch_update)
- [queueInfo\_getStatus](#queueinfo_getstatus)
- [ms\_process](#ms_process)
- [See also](#see-also)
  
---

## Setup

Relative paths are used in the provided `do_*` scripts and the Visual Studio project files. They assume the following installation paths:
- `C:\OpenText\idol_oem_tutorials\resources\apis\aci\c`
- `C:\OpenText\IDOLCSDK_24.3.0_WINDOWS_X86_64`

### Setup - Build

To build and then run each example the constants `USE_IDOL_OEM_ENCYPTION` and `IDOL_OEM_ENCRYPTION_KEY` will need to be updated with same encryption key information provided in the `OEMstring.txt` file.
 
### Setup - Run

> NOTE: In the `do_run_*.*` scripts, the `ACI_HOSTNAME`, `ACI_PORT` and other service specific settings noted below may need to be updated for your ACI service instance.

To use the pre-built `/target` classes, the `do_run.*` scripts (`ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY` variable) need to be updated with the encryption key information provided in the `OEMstring.txt` file.  See [here](../../../tutorials/aci_api/introduction.md#obtain-an-oem-license-key) for details on obtaining OEM style license key.
 
### Required third-party tools

- C compiler - gcc / Visual Studio

  > TIP: If using Visual Studio Code, you may find these instructions helpful for setting up your C/C++ development environment: https://code.visualstudio.com/docs/cpp/config-mingw

- A (UTF-8 capable) text editor, *e.g.*:
  - [VS Code](https://code.visualstudio.com/download), or
  - [Notepad++](https://notepad-plus-plus.org/download)

- A Markdown viewer
  - Plugins to VS Code, Notepad++ and some web browsers are good options

## getStatus

This sample code is for use with all IDOL services, since `action=getStatus` is an administrative action supported by all IDOL service types.  It can also serve as the foundation for implementing other actions.

## fetch_synchronize

This sample code is for use with IDOL Connectors issuing the basic settings for `action=fetch` and implementing `fetchAction=synchronize`. It can also serve as the foundation for implementing other fetch actions.

> NOTE: The `do_run_fetch_synchronize.*` script may need to be updated with your configured fetch task name in `TASK_NAME`.

## fetch_identifiers

This sample code is for use with IDOL Connectors issuing the basic settings for `action=fetch` and implementing `fetchAction=identifiers`. It can also serve as the foundation for implementing other fetch actions.

> NOTE: The `do_run_fetch_identifiers.*` script may need to be updated with your configured fetch task name in `TASK_NAME`.

## fetch_collect

This sample code is for use with IDOL Connectors issuing the basic settings for `action=fetch` and implementing `fetchAction=collect`. It can also serve as the foundation for implementing other fetch actions.

> NOTE: The `do_run_fetch_collect.*` script will need to be updated with the `IDENTIFIERS_CSV` for the data to collect.

> NOTE: The `do_run_fetch_collect.*` script may need to updated with the `DESTINATION_FOLDER`.

## fetch_delete

This sample code is for use with IDOL Connectors issuing the basic settings for `action=fetch` and implementing `fetchAction=delete`. It can also serve as the foundation for implementing other fetch actions.

> NOTE: The `do_run_fetch_delete.*` script will need to be updated with the `IDENTIFIERS_CSV` for the data to collect.

## fetch_insert

This sample code is for use with IDOL Connectors issuing the basic settings for `action=fetch` and implementing `fetchAction=insert`. It can also serve as the foundation for implementing other fetch actions.

> NOTE: The `do_run_fetch_synchronize.*` script may need to be updated with your configured fetch task name in `TASK_NAME`.

> NOTE: A `insertXML.xml` will need to be updated containing properly formatted `<insertXML>` syntax for the connector being used.  For more details, refer to the documentation for the connector being used.

> NOTE: The `do_run_fetch_insert.*` script may need to be updated with the `INSERT_XML_FILE` path containing the data to insert.

## fetch_update

This sample code is for use with IDOL Connectors issuing the basic settings for `action=fetch` and implementing `fetchAction=update`. It can also serve as the foundation for implementing other fetch actions.

> NOTE: A `identifiersXML.xml` will need to be updated containing properly formatted `<identifiersXML>` syntax for the connector being used.  For more details, refer to the documentation for the connector being used.

> NOTE: The `do_run_fetch_update.*` script may need to be updated with the `IDENTIFIERS_XML_FILE` path containing the data to update.

## queueInfo_getStatus

This sample code is applicable to all IDOL services (*e.g.* Connectors, CFS, MediaServer and Content) that support asynchronous actions.  `action=queueInfo&queueAction=getStatus` is to get the status.

> NOTE: The `do_run_queueInfo_getstatus.*bat*` script may need to be updated with the `QUEUE_NAME` appropriate for the IDOL service type in use.  Asynchronous actions are supported by connectors, CFS, MediaServer and other IDOL service types.

> NOTE: The `do_run_queueInfo_getstatus.` script will need to be updated with the token returned by asynchronous actions like `action=fetch` to check the status of a particular token.  If the TOKEN variable is set to empty string then recent tokens status will be returned.

## ms_process
This sample code is for use with IDOL Media Server issuing the basic settings for `action=process`.

> NOTE: The `do_run_ms_process.*` script will need to be updated with the `CONFIG_NAME` appropriate for the intended Media Server processing.  

> NOTE: The `do_run_ms_process.*` script will need to be updated with the `SOURCE_FILE_PATH` of the rich media file to process.

## See also

- ACI API Programming Guide: [C Language Interface](https://www.microfocus.com/documentation/idol/IDOL_24_3/IDOLJavaSDK_24.3_Documentation/Guides/html/Content/C/c_part.htm)
- IDOL Release Notes: [C Language Interface](https://www.microfocus.com/documentation/idol/IDOL_24_3/IDOLReleaseNotes_24.3_Documentation/idol/Content/SDKs/IDOL-C.htm)
