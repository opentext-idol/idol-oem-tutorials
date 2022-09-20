# Eduction Server

The Eduction ACI Server is a stand-alone server that uses the IDOL ACI infrastructure. It is one of the available options that you have to run Eduction.

In this lesson, you will:

- Learn about the key features of an ACI server.
- Configure and start Eduction Server with your OEM license key.
- Explore the ACI API SDK for C to allow communication with Eduction Server.
- Use the include Python wrapper for the ACI API to perform Eduction.

This guide assumes you have already completed the introductory Eduction [tutorial](./introduction.md).

---

- [Setup](#setup)
  - [Download ACI SDK for C, Eduction Server & Grammars](#download-aci-sdk-for-c-eduction-server--grammars)
  - [Obtain an OEM license key](#obtain-an-oem-license-key)
  - [Install IDOL components](#install-idol-components)
- [IDOL ACI Servers](#idol-aci-servers)
- [Configuring Eduction Grammars](#configuring-eduction-grammars)
- [Run Eduction Server](#run-eduction-server)
- [The ACI API](#the-aci-api)
  - [Python wrapper](#python-wrapper)
  - [Encrypted requests](#encrypted-requests)
  - [Response format options](#response-format-options)
  - [Run Eduction](#run-eduction)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

### Download ACI SDK for C, Eduction Server & Grammars

Download software from the [Software Licensing and Downloads](https://sld.microfocus.com/mysoftware/index) portal.

1. Under the *Downloads* tab, select your product, product name and version from the dropdowns:

    ![get-software](./figs/get-software.png)

1. From the list of available files, select and download the following (depending on your platform):
   -  `IDOLCSDK_12.4.0_{PLATFORM}`, *e.g.* `IDOLCSDK_12.4.0_WINDOWS_X86_64.zip`,
   -  `EductionServer_12.12.0_{PLATFORM}`, *e.g.* `EductionServer_12.12.0_WINDOWS_X86_64.zip`, and
   -  `EductionGrammars_12.12.0_COMMON.zip` (if you don't already have a copy from the introductory tutorial).

    > NOTE: the most recent version of the IDOL C SDK is currently 12.4.0.

### Obtain an OEM license key

Contact Micro Focus to obtain a trial OEM license key.  For this tutorial you will require the following two files:
1. `licensekeyInternal.dat`: the OEM license key file itself, and
2. `OEMstring.txt`: containing associated encryption keys required by clients making requests to Eduction Server.

### Install IDOL components

1. Copy your downloaded files into a new working folder.  The follow guide assumes this is `C:\MicroFocus` on Windows.
2. Extract the `.zip` files to give you:
   - `C:\MicroFocus\IDOLCSDK_12.4.0_WINDOWS_X86_64`,
   - `C:\MicroFocus\EductionServer_12.12.0_WINDOWS_X86_64`, and
   - `C:\MicroFocus\EductionGrammars_12.12.0_COMMON`
  
3. Copy your OEM license key `.dat` file into `C:\MicroFocus\EductionServer_12.12.0_WINDOWS_X86_64` and rename it to `licensekey.dat`.
   
    > NOTE: this key will typically have been named `licensekeyInternal.dat` when you received it.

4. On Windows, you may need to install the included Visual C++ Redistributable package.  In the the same Eduction Server folder, right-click on `vcredist_2017.exe` then select 'Run as administrator'.
   
    > HINT: If you see a version conflict error here, you may need to first uninstall any existing version.

## IDOL ACI Servers

All IDOL ACI servers include, *e.g.* under the directory: `C:\MicroFocus\EductionServer_12.12.0_WINDOWS_X86_64`:
- an executable, *e.g.* `eductionserver.exe`, and
- a primary configuration file, *e.g.* `eductionserver.cfg`.

An ACI server can be launched by running the executable or by configuring a service on [Windows](https://www.microfocus.com/documentation/idol/IDOL_12_12/IDOLServer_12.12_Documentation/Guides/html/gettingstarted/Content/Shared_Admin/Installation/_ADM_Install_WindowsServices.htm) or on [Linux](https://www.microfocus.com/documentation/idol/IDOL_12_12/IDOLServer_12.12_Documentation/Guides/html/gettingstarted/Content/Shared_Admin/Installation/_ADM_Install_LinuxStartup.htm).

Where you have an OEM license key, the ACI server looks on startup for a `licensekey.dat` file in the same directory as the executable.

> NOTE: With a non-OEM license, the primary configuration file must be modified to reference an instance of IDOL License Server, which is contacted to received permission to run.  Use of IDOL License Server is beyond the scope of this lesson.

## Configuring Eduction Grammars

As will now be familiar, Eduction grammars are supplied separately in the `EductionGrammars_12.12.0_COMMON.zip` container.  The default Eduction Server configuration file assumes the existence of the general `internet.ecr` file as follows:

```ini
[Eduction]
ResourceFiles=grammars/internet.ecr
```

Copy you folder across to meet this assumption:

```sh
robocopy C:\MicroFocus\EductionGrammars_12.12.0_COMMON\general\grammars C:\MicroFocus\EductionServer_12.12.0_WINDOWS_X86_64\grammars
```

The `[Eduction]` section of this configuration file should look familiar to you from the introduction, as the configuration of Resource Files and Entities is the same.

Note some important additional sections:

- The Service and Server ports that Eduction Server will listen on to receive requests from an ACI client:

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

- The log files that Eduction Server will write out to:

    ```ini
    [Logging]
    LogDirectory=./logs
    0=ApplicationLogStream
    1=EductionLogStream
    2=QueryLogStream
    ```

## Run Eduction Server

For the simplest start, now double-click the `eductionserver.exe`.

Open the `logs/application.log` file to see amount other messages, the following line:

```
This ACI Server will not accept unencrypted communications from ACI clients.
```

This line means that your Eduction Server has successfully picked up up the OEM license key and is ready to accept encrypted requests from an ACI client.

## The ACI API

The ACI (Autonomy Content Infrastructure) Client API enables easy communication between custom-built applications and Micro Focus ACI servers, as well as simple manipulation of the returned result sets.

The ACI API SDK is currently available for C, Java and .NET.  In this tutorial we will use the C variant with a custom Python wrapper for ease of testing.

### Python wrapper

The Python wrapper code is included in this tutorial package under `resources/apis/aci/aciapipy`.

In the `lib` directory, you find and open the `.env` file to ensure that the `ACI_LIB_PATH` environment variable points to your C SDK directory:

```ini
ACI_LIB_PATH="C:\\MicroFocus\\IDOLCSDK_12.4.0_WINDOWS_X86_64"
```

> NOTE: this directory must contain the files `client.h` and `aciclient.dll`.

To run the Python ACI wrapper, install Python 3.X and the required package:

```sh
pip install python-dotenv
```

### Encrypted requests

With your Eduction Server running, our first request will be a simple one to get the version of the running server.  See the script to do this `aciapipy/scripts/get_version_oem.py`, copied below:

```py
"""
Capture the ACI server name and version from an ACI-encrypted 'GetVersion' request 
to an OEM-licensed IDOL Eduction Server.
"""
import context as aci
import xml.etree.ElementTree as ET

response = aci.client.call(
  encryption_key="REPLACE_WITH_MY_LONG_KEY_STRING",
  hostname="127.0.0.1",
  port=13000,
  aci_action="GetVersion"
)
# print(response)
root = ET.fromstring(response)

namespaces = {'autn': 'http://schemas.autonomy.com/aci/'}
name = root.find(".//autn:productname", namespaces).text
version = root.find(".//autn:version", namespaces).text
print(f'{name} v{version}')
```

Navigate to this directory and edit the file to set the value of the `encryption_key` parameter to the long string found in your `OEMstring.txt` file.

Now you're ready to run:

```sh
> cd resources\apis\aci\aciapipy\scripts
> python get_version_oem.py
Eduction Server v12.12.0
```

### Response format options

If you uncomment line 13 (as follows) and re-run the script you will see the response from Eduction Server is an unencrypted XML string.

```diff
- # print(response)
+ print(response)
```

You can optionally configure a response in alternative formats including JSON.  See the [reference guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionServer_12.12_Documentation/Help/Content/Actions/SharedParameters/_ACI_ResponseFormat.htm) for more details.

Next, let's run the included `get_version_oem_json.py` script, which adds an additional option to specify the response format:

```py
aci_params = {
  "ResponseFormat": "simplejson"
}
```

Run this command to see the same output as before:

```sh
> python get_version_oem_json.py
Eduction Server v12.12.0
```

Notice that this second script is obtaining these values now from response JSON, as follows:

```py
name = data["autnresponse"]["responsedata"]["productname"]
version = data["autnresponse"]["responsedata"]["version"]
```

### Run Eduction

Now that you're set up with Eduction Server and an ACI client to make encrypted calls, it's time to run something useful.

The included scripts directory contains another file to do just that: `educe_from_text_oem.py`.

This script uses the `call()` function to run Eduction Server's `EduceFromText` action, submitting a text string to be analyzed as well as the entity type to be educed, as follows:

```py
aci_params = {
  "Text": "Simon received emails from christopher.blanks@microfocus.com and chris.blanks@microfocus.com today.",
  "Entities": "internet/addr_email"
}
```  

> NOTE: Remember that Eduction Server's default configuration file included the `internet.ecr` grammar file, from which we're using the email entity as a test.

Run the script to see the output from Eduction Server:

```
> python educe_from_text_oem.py 
offset,match,score
26,christopher.blanks@microfocus.com,1.0
64,chris.blanks@microfocus.com,1.0
```

For more details on running the "EduceFromText" action and its optional parameters, please read the [reference guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionServer_12.12_Documentation/Help/Content/Actions/Eduction/EduceFromText.htm).

## Conclusion

You now understand how to license and run Eduction Server in an OEM deployment to receive ACI-encrypted requests from an ACI client.

> NOTE: these instructions are valid for any ACI server, so you are already more powerful than you thought.

Next, why not try more tutorials to explore some of the other features available in IDOL Eduction, linked from the [showcase](./README.md) page.

## See also

- [IDOL Eduction (Server) User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionServer_12.12_Documentation/Guides/html/)
- [IDOL Eduction SDK User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionSDK_12.12_Documentation/Guides/html)
