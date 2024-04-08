# Obtain an IDOL license

You can obtain software and licenses from the [Software Licensing and Downloads](https://sld.microfocus.com/mysoftware/index) portal.

1. Under the *Entitlements* tab, search for *IDOL*
1. Select from your available environment types:
1. Scroll to the bottom and click `Activate` next to your *IDOL SW license*

    ![get-license](./figs/get-license.png)
 
1. On the "License Activation" screen, at the bottom, select the check box, choose your preferred version (the latest is 24.2), then fill in the quantity to activate:

   ![eSoftware-selectLicense](./figs/eSoftware-selectLicense.png)

1. Above this section, fill in the requested details, including the MAC address and host name of the machine where you will set up your IDOL system:

   ![eSoftware-configureLicense](./figs/eSoftware-configureLicense.png)

    > NOTE: In these tutorials you will primarily use SDKs, where you will embed this license key, know that this license key can also be used to enable IDOL License Server, which can only run on the machine whose details are specified and which listens for HTTP requests from other IDOL components to provide them license seats.  That servers' default port is `20000` but you are free to change this.

    > HINT: To obtain your MAC address and host name on Windows, open a command prompt and enter `ipconfig /all`.  Now look for the "Host Name" and "Physical Address" fields:
    >
    > ![ipconfig](./figs/ipconfig.png)
    >
    > On Linux the equivalent command is [`ifconfig`](https://man.openbsd.org/ifconfig.8).

1. Click "Next", then confirm your details and click "Submit".  You will soon received your key, which is a `.dat` file, by email.
