# Named Entity Recognition Server

The Named Entity Recognition ACI Server is a stand-alone server that uses the Knowledge Discovery (formerly known as IDOL) ACI infrastructure. Named Entity Recognition Server is one of the available options that you have to run Named Entity Recognition with Named Entity Recognition SDK being another.

In this lesson, you will:

- Learn about the key features of an ACI server.
- Configure and start Named Entity Recognition Server with your OEM license key.
- Explore the ACI API SDK for C to allow communication with Named Entity Recognition Server.
- Use the include Python wrapper for the ACI API to perform Named Entity Recognition.

This guide assumes you have already completed both:

- the introductory Named Entity Recognition [tutorial](./introduction.md), and
- the ACI API introductory tutorial [Python example](../../resources/aci_api/Python/README.md).

---

- [Setup](#setup)
  - [Download ACI SDK for C, Named Entity Recognition Server \& Grammars](#download-aci-sdk-for-c-named-entity-recognition-server--grammars)
  - [Install Knowledge Discovery components](#install-knowledge-discovery-components)
- [ACI Servers](#aci-servers)
- [Configuring Named Entity Recognition Grammars](#configuring-named-entity-recognition-grammars)
- [Run Named Entity Recognition Server](#run-named-entity-recognition-server)
- [Perform Named Entity Recognition via the ACI API](#perform-named-entity-recognition-via-the-aci-api)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

### Download ACI SDK for C, Named Entity Recognition Server & Grammars

Download software from the [Software Licensing and Downloads](https://sld.microfocus.com/mysoftware/index) portal.

1. Under the *Downloads* tab, select your product, product name and version from the dropdowns:

    ![get-software](../../figs/get-software.png)

1. From the list of available files, select and download the following (depending on your platform):
   - `IDOLCSDK_25.4.0_{PLATFORM}`, *e.g.* `IDOLCSDK_25.4.0_WINDOWS_X86_64.zip`,
   - `EductionServer_25.4.0_{PLATFORM}`, *e.g.* `EductionServer_25.4.0_WINDOWS_X86_64.zip`,
   - `EductionGrammars_25.4.0_COMMON.zip` (if you don't already have a copy from the introductory tutorial), and
   - `Versionkey_25.4.0_COMMON.zip`.

    > NOTE: you should have already downloaded the C API package while following the ACI API introductory [tutorial](../aci_api/introduction.md#download-knowledge-discovery-components).

### Install Knowledge Discovery components

1. Copy your downloaded files into a new working folder.  The following guide assumes this is `C:\OpenText` on Windows.
1. Extract the `.zip` files to give you:
   - `C:\OpenText\IDOLCSDK_25.4.0_WINDOWS_X86_64`,
   - `C:\OpenText\EductionServer_25.4.0_WINDOWS_X86_64`, and
   - `C:\OpenText\EductionGrammars_25.4.0_COMMON`
  
1. Copy your OEM license key `.dat` file into `C:\OpenText\EductionServer_25.4.0_WINDOWS_X86_64` and rename it to `licensekey.dat`.

    > NOTE: obtain this key as described in ACI API introductory [tutorial](../aci_api/introduction.md#obtain-an-oem-license-key).

1. Extract the file `versionkey.dat` from `Versionkey_25.4.0_COMMON.zip`, then copy that file into `C:\OpenText\EductionServer_25.4.0_WINDOWS_X86_64` as described in the [Knowledge Discovery Release Notes - Licensing](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/idol/Content/Upgrade/Licenses.htm).

> NOTE: On Windows, you may need to install the included Visual C++ Redistributable package.  In the same Named Entity Recognition Server folder, right-click on `vcredist.exe` then select 'Run as administrator'. If you see a version conflict error here, you may need to first uninstall any existing version.

## ACI Servers

All ACI servers include, *e.g.* under the directory: `C:\OpenText\EductionServer_25.4.0_WINDOWS_X86_64`:

- an executable, *e.g.* `eductionserver.exe`, and
- a primary configuration file, *e.g.* `eductionserver.cfg`.

An ACI server can be launched by running the executable or by configuring a service on [Windows](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLServer_25.4_Documentation/Guides/html/gettingstarted/Content/Shared_Admin/Installation/_ADM_Install_WindowsServices.htm) or on [Linux](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLServer_25.4_Documentation/Guides/html/gettingstarted/Content/Shared_Admin/Installation/_ADM_Install_LinuxStartup.htm).

Where you have an OEM license key, the ACI server looks on startup for a `licensekey.dat` file in the same directory as the executable.  Edit the `eductionserver.cfg` as follows to use OEM license key:

```diff
-[License]
-LicenseServerHost=localhost
-LicenseServerACIPort=20000
```

> NOTE: With a non-OEM license, the primary configuration file must be modified to reference an instance of License Server, which is contacted to received permission to run.  Use of License Server is beyond the scope of this lesson.

## Configuring Named Entity Recognition Grammars

As will now be familiar, Named Entity Recognition grammars are supplied separately in the `EductionGrammars_25.4.0_COMMON.zip` container.

Edit the `eductionserver.cfg` as follows:

```diff
-ResourceFiles=grammars/internet.ecr
+ResourceFiles=../EductionGrammars_25.4.0_COMMON/general/grammars/internet.ecr
```

The `[Eduction]` section of this configuration file should look familiar to you from the introduction, as the configuration of Resource Files and Entities is the same.

Note some important additional sections:

- The Service and Server ports that Named Entity Recognition Server will listen on to receive requests from an ACI client:

    ```ini
    [Service]
    ServicePort=13001

    [Server]
    Port=13000
    ```

- IP address/range restrictions for clients to have requests accepted by the ACI server:

    ```ini
    [AuthorizationRoles]
    0=AdminRole
    1=QueryRole

    [AdminRole]
    StandardRoles=admin,servicecontrol,query,servicestatus
    Clients=localhost
    ...
    ```

- The log files that Named Entity Recognition Server will write out to:

    ```ini
    [Logging]
    LogDirectory=./logs
    0=ApplicationLogStream
    1=EductionLogStream
    2=QueryLogStream
    ```

## Run Named Entity Recognition Server

For the simplest start, now double-click the `eductionserver.exe`.

Open the `logs/application.log` file to see amount other messages and the following line:

```txt
This ACI Server will not accept unencrypted communications from ACI clients.
```

This line means that your Named Entity Recognition Server has successfully picked up up the OEM license key and is ready to accept encrypted requests from an ACI client.

## Perform Named Entity Recognition via the ACI API

The ACI (Autonomy Content Infrastructure) Client API enables easy communication between custom-built applications and ACI servers.

If you are not already familiar with the Python ACI API wrapper, refer to [resources/aci_api/Python](../../resources/aci_api/Python/README.md) in this tutorials package.

Now that you're set up with Named Entity Recognition Server and the Python ACI API, it's time to run something useful.  The included scripts directory contains a file to do just that: `educe_from_text_oem.py` under the `eduction` directory.

This script uses the `call()` function to run Named Entity Recognition Server's `EduceFromText` action, submitting a text string to be analyzed, as well as the entity type to be educed, as follows:

```py
aci_params = {
  "Text": "Simon received emails from christopher.blanks@opentext.com and chris.blanks@opentext.com today.",
  "Entities": "internet/addr_email"
}
```  

> NOTE: Remember that above we configured Named Entity Recognition Server to reference the `internet.ecr` grammar file, from which we're using the email entity as a test.

As previously, you must set the value of the `encryption_key` parameter to the long string found in your `OEMstring.txt` file:

  ```diff
  - encryption_key="REPLACE_WITH_MY_LONG_KEY_STRING",
  + encryption_key="NTI6MXyE...3dheAQC"
  ```

Run the script to see the output from Named Entity Recognition Server:

```sh
> python educe_from_text_oem.py 
offset,match,score
26,christopher.blanks@opentext.com,1.0
64,chris.blanks@opentext.com,1.0
```

Two matches are produced reflecting the two email addresses in the input text.

For more details on running the "EduceFromText" action and its optional parameters, please read the [reference guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionServer_25.4_Documentation/Help/Content/Actions/Eduction/EduceFromText.htm).

## Conclusion

You now understand how to license and run Named Entity Recognition Server in an OEM deployment to receive ACI-encrypted requests from an ACI client to perform Named Entity Recognition from sample text.

Next, why not try more tutorials to explore some of the other features available in Named Entity Recognition, linked from [here](../eduction/README.md#capability-showcase).

## See also

- [Named Entity Recognition Server Reference Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionServer_25.4_Documentation/Help/Content/_ACI_Welcome.htm)
- [Named Entity Recognition SDK User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/)
- [Named Entity Recognition Grammars User Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionGrammars_25.4_Documentation/Help/)
- [Knowledge Discovery Release Notes - Named Entity Recognition](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/idol/Content/SDKs/Eduction.htm)
