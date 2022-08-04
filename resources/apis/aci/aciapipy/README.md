# Python bindings for the ACI API

The `aciapipy` module provides a Python interface to communicate with OEM-licensed ACI servers.

It is split into two submodules:
  - `wrapper.py` contains classes that include Python bindings for targeted function in the C ACI API shared library, and
  - `client.py` contains a simple `call()` function that returns an XML string response.

---

- [Dependencies](#dependencies)
- [Example usage](#example-usage)
- [OEM licensing](#oem-licensing)
- [License](#license)

---

## Dependencies

The C ACI API shared library and header files must be accessible.  The file `lib/.env` is used to specify their containing folder, and is set by default to:

  - On Windows:

    ```
    ACI_LIB_PATH="C:\\MicroFocus\\IDOLCSDK_12.4.0_WINDOWS_X86_64"
    ```

    This folder must contain the files:
    - `aciclient.dll`
    - `client.h`

  <!-- - On Linux TBC -->

## Example usage

Look in the `scripts` directory for samples making use of the ACI API.

```
$ cd scripts
$ python get_version.py
Media Server v12.12.0
```

> NOTE: The helper script `context.py` is used to explicitly specify the path of the package library to import.  This approach allows you to run scripts without the need to perform an installation.

## OEM licensing

The ACI API provides a means of encrypting requests to IDOL Servers.  This ACI encryption is required when communicating with IDOL Servers that are OEM licensed.

These Python wrapping functions support ACI encryption by passing in an encryption key.  This is the long string that would be provided with your OEM license key file and is applied as follows:

```py
response = aci.client.call(
  encryption_key="REPLACE_WITH_MY_LONG_KEY_STRING",
  hostname="127.0.0.1", 
  port=13000, 
  aci_action="GetStatus"
)
```

> NOTE: For more details of IDOL's OEM licensing model, please read the [reference guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/IDOLServer_12.12_Documentation/Guides/html/expert/Content/IDOLExpert/Licenses/Licenses.htm?Highlight=OEM).

## License

Copyright 2022 Micro Focus International plc.

Licensed under the MIT License (the "License"); you may not use this project except in compliance with the License.
