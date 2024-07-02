# Python bindings for the C ACI API

This module provides a Python interface to communicate with OEM-licensed ACI servers via the C SDK.

It is split into two submodules:
  - `wrapper.py` contains classes that include Python bindings for targeted function in the C ACI API shared library, and
  - `client.py` contains a simple `call()` function that returns the server's response, usually as XML or JSON.

The various scripts in the `scripts` directory, provide examples, some of which we will step through below.

---

- [Setup](#setup)
  - [IDOL](#idol)
  - [Python](#python)
- [Writing a client](#writing-a-client)
- [Run your client program](#run-your-client-program)
- [Response formats](#response-formats)
- [Summarize text](#summarize-text)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

### IDOL

Follow the setup steps in the [ACI API introduction lesson](../../../tutorials/aci_api/introduction.md#install-idol-components) to:

- Extract the C SDK package (`IDOLCSDK_24.3.0_WINDOWS_X86_64.zip`), and
- Install an IDOL ACI Server (for us to communicate with) and run it in OEM mode. 

    > NOTE: Below, we assume you have IDOL Content Server running.

### Python

To run the Python ACI wrapper, install Python 3.X and the following required package:

```sh
pip install python-dotenv
```

In the `lib` sub-directory of this Python package, please find and open the `.env` file and ensure that the `ACI_LIB_PATH` environment variable points to your C SDK directory, *e.g.*:

```ini
ACI_LIB_PATH="C:\\OpenText\\ACI_API\\IDOLCSDK_24.3.0_WINDOWS_X86_64"
```

> NOTE: this directory contains the two required files: `client.h` and `aciclient.dll`.

## Writing a client

With your IDOL Content Server (or other ACI Server) running, our first request will be a simple one to get the version of the running server.  See the script to do this `resources/aci_api/Python/scripts/get_version_oem.py`.  The `call()` function is copied below:

```py
response = aci.client.call(
  encryption_key="<REPLACE_WITH_MY_LONG_KEY_STRING>",
  hostname="127.0.0.1",
  port="<REPLACE_WITH_ACI_PORT>",
  aci_action="GetVersion"
)
print(response)
```

Navigate to this directory and edit the file to make the following modifications for your setup:

1. set the value of the `encryption_key` parameter to the long string found in your `OEMstring.txt` file, and

    ```diff
    - encryption_key="<REPLACE_WITH_MY_LONG_KEY_STRING>",
    + encryption_key="NTI6MXyE...3dheAQC"
    ```

1. set the value of the ACI port, *e.g.* for IDOL Content Server:

    ```diff
    - port="<REPLACE_WITH_ACI_PORT>",
    + port=9100,
    ```

    > NOTE: Where the IDOL Content Server ACI port is configured in `content.cfg` in the `Server` section as:
    > ```ini
    > [Server]
    > Port=9100
    > ```

## Run your client program

First, ensure that IDOL Content Server is running: double-click the `content.exe` (or the equivalent executable for your preferred ACI server). 

Now, you're ready to run your client:

```sh
> cd resources\aci_api\Python\scripts
> python get_version_oem.py
IDOL Server v24.3.0
```

## Response formats

If you uncomment line 14 (as follows) and re-run the script you will see the response from Content Server is an XML string.

```diff
- # print(response)
+ print(response)
```

> TIP: As an extra exercise, why not modify the Python code to capture other properties from the response XML?

You can optionally configure a response in alternative formats including JSON.  See the [reference guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/Content_24.3_Documentation/Help/Content/Actions/SharedParameters/_ACI_ResponseFormat.htm) for more details.

Next, let's run the included `get_version_oem_json.py` script, which adds an additional option to specify the response format:

```py
aci_params = {
  "ResponseFormat": "simplejson"
}
```

Run this command to see the same output as before:

```sh
> python get_version_oem_json.py
IDOL Server v24.3.0
```

Notice that this second script is obtaining these values now from response JSON, as follows:

```py
name = data["autnresponse"]["responsedata"]["commonname"]
version = data["autnresponse"]["responsedata"]["version"]
```

## Summarize text

While we have IDOL Content Server running, let's try to do something more interesting.

Note the subfolder `content` inside `resources/aci_api/Python/scripts`.  The sample script `summarize_text_oem.py` instructs IDOL Content Server to intelligently summarize a larger section of text, *e.g.* an article on "Artificial Intelligence":

```
$ python summarize_text_oem.py 
Artificial intelligence (AI) is the intelligence of machines or software, as opposed to the intelligence of humans or animals. The various sub-fields of AI research are centered around particular goals and the use of particular tools.
```

> NOTE: Read more about IDOL Content Server's summarization API in the [reference guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/Content_24.3_Documentation/Help/Content/Actions/Miscellaneous/Summarize.htm).

## Conclusion

You now understand how to setup and run a Python ACI Client to interact with an IDOL ACI Server.

Next, why not explore some of the other methods for interacting with ACI Servers [here](../../../tutorials/aci_api/README.md#capability-showcase).

## See also

- ACI API Programming Guide: [C Language Interface](https://www.microfocus.com/documentation/idol/IDOL_24_3/IDOLJavaSDK_24.3_Documentation/Guides/html/Content/C/c_part.htm)
- IDOL Release Notes: [C Language Interface](https://www.microfocus.com/documentation/idol/IDOL_24_3/IDOLReleaseNotes_24.3_Documentation/idol/Content/SDKs/IDOL-C.htm)
