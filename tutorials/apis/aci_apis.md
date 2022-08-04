# IDOL ACI APIs

IDOL services support a REST style API allowing client applications to perform the following, but not limited to, types of functions:
- monitor the service status
- perform administrative actions
- load data into the service
- train the models of the service
- ask service to perform analytics on data

The ACI API exists to provide a common approach to interacting with any IDOL ACI service.

In this lesson, you will:
- Learn about the key features of an ACI server.
- Configure and start the IDOL ACI service of your choice with your OEM license key.
- Explore the ACI API SDK for C to allow communication with an ACI service of your choice

> NOTE: This lesson is a companion lesson to Connector, Eduction Server, Media Server and other ACI service lessons.

---

- [Setup](#setup)
  - [Download IDOL components](#download-idol-components)
  - [Obtain an OEM license key](#obtain-an-oem-license-key)
  - [Install IDOL components](#install-idol-components)
- [API Documentation](#api-documentation)
- [IDOL ACI Servers](#idol-aci-servers)
- [Example programs](#example-programs)
  - [C](#c)
  - [Java](#java)
  - [.Net](#net)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the documentation links [below](#see-also).

> NOTE: This lesson is a companion less to Connector, Eduction Server, Media Server and other ACI service lessons where essential setup steps (*e.g.* required downloads and installation steps) and basic concepts are covered separately.

### Download IDOL components

Download software from the [Software Licensing and Downloads](https://sld.microfocus.com/mysoftware/index) portal.

1. Under the *Downloads* tab, select your product, product name and version from the dropdowns:

    ![get-software](./figs/get-software.png)

1. From the list of available files, select and download the following (depending on your platform):
   - C - IDOLCSDK_12.4.0_<PLATFORM>.zip , `IDOLCSDK_12.4.0_WINDOWS_X86_64.zip`
   - Java - idol-aci-client-12.10.0-bin.zip or idol-aci-client-12.10.0-bin.tar.gz
   - .Net - IDOLDotNetSDK_12.4.0_WINDOWS_X86_64.zip

    > NOTE: the most recent versions of each ACI SDK are correct as above.

### Obtain an OEM license key

Contact Micro Focus to obtain a trial OEM license key.  For this tutorial you will require the following two files:
1. `licensekeyInternal.dat`: the OEM license key file itself, and
2. `OEMstring.txt`: containing associated encryption keys required by clients making requests to Eduction Server.

### Install IDOL components

1. Copy your downloaded files into a new working folder.  The follow guide assumes this is `C:\MicroFocus` on Windows.
2. Extract the `.zip` files to give you:
   - `C:\MicroFocus\ACI_API\IDOLCSDK_12.4.0_WINDOWS_X86_64`,
   - `C:\MicroFocus\ACI_API\IDOLJavaSDK_12.10.0\idol-aci-client-12.10.0-bin`,
   - `C:\MicroFocus\ACI_API\IDOLDotNetSDK_12.4.0_WINDOWS_X86_64`
3. Copy your OEM license key `.dat` file into `C:\MicroFocus\<ACI_Service_of_your_choice>` and rename it to `licensekey.dat`.
   
    > NOTE: this key will typically have been named `licensekeyInternal.dat` when you received it.

## API Documentation

The [ACI API Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_6/IDOLJavaSDK_12.4_Documentation/Guides/html/English/index.html) is an excellent resource which will be heavily relied upon in this lesson.

The API specific reference documentation is located as below:
- C - [C-Language Reference](https://www.microfocus.com/documentation/idol/IDOL_12_6/IDOLJavaSDK_12.4_Documentation/Guides/html/English/index.html#C/C_functions.htm)
- Java - 'IDOLJavaSDK_12.10.0\idol-aci-client-12.10.0-bin\aci-api-release-12.10.0-javadoc\index.html"
- .Net - 'IDOLDotNetSDK_12.4.0_WINDOWS_X86_64\Documentation.chm'

> NOTE: If you're using the IDOL Java SDK, go ahead an unpack the `javadoc.jar` to the path as noted above.

## IDOL ACI Servers

All IDOL ACI servers include, *e.g.* under the directory: `C:\MicroFocus\<IDOL_ACI_Service_of_your_choice>`:
- an executable, *e.g.* `<aci_service_name>.exe`, and
- a primary configuration file, *e.g.* `aci_service_name.cfg`.

An ACI server can be launched by running the executable or by configuring a service on [Windows](https://www.microfocus.com/documentation/idol/IDOL_12_12/IDOLServer_12.12_Documentation/Guides/html/gettingstarted/Content/Shared_Admin/Installation/_ADM_Install_WindowsServices.htm) or on [Linux](https://www.microfocus.com/documentation/idol/IDOL_12_12/IDOLServer_12.12_Documentation/Guides/html/gettingstarted/Content/Shared_Admin/Installation/_ADM_Install_LinuxStartup.htm).

Where you have an OEM license key, the ACI server looks on startup for a `licensekey.dat` file in the same directory as the executable.

> NOTE: With a non-OEM license, the primary configuration file must be modified to reference an instance of IDOL License Server, which is contacted to received permission to run.  Use of IDOL License Server is beyond the scope of this lesson.

## Example programs

### C

> Coming soon!

### Java

> Coming soon!

### .Net

> Coming soon!

## Conclusion


## See also

- [ACI API Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_6/IDOLJavaSDK_12.4_Documentation/Guides/html/English/index.html)
- [IDOL OEM Licensing Technical Note](https://www.microfocus.com/documentation/idol/IDOL_12_6/IDOLOEMLicensing_12.6_TechnicalNote_en.pdf)
- [IDOL Getting Started Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/IDOLServer_12.12_Documentation/Guides/html/gettingstarted/index.html)
- [IDOL Expert](https://www.microfocus.com/documentation/idol/IDOL_12_12/IDOLServer_12.12_Documentation/Guides/html/expert/index.html)
