/* BEGIN COPYRIGHT NOTICE */
/* Copyright 2024 Open Text.
*
* The only warranties for products and services of Open Text and its affiliates
* and licensors ("Open Text") are as may be set forth in the express warranty
* statements accompanying such products and services. Nothing herein should be
* construed as constituting an additional warranty. Open Text shall not be
* liable for technical or editorial errors or omissions contained herein. The
* information contained herein is subject to change without notice.
*/
/* END COPYRIGHT NOTICE */

package tutorial;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

// Configuration for the demo code.
class Config
{
	public static String getLicense()
	{
		// Replace this with your license string:
		try {
			String licensekey_filepath = "KEYVIEW_LICENSEKEY_PATH";
			
			String longString = new String(Files.readAllBytes(Paths.get(licensekey_filepath)));
		} catch (IOException e) {
            System.err.println("An I/O error occurred while reading the license key: " + e.getMessage());
            e.printStackTrace();
        }					
	}

	public static String getFilterBinFolder()
	{
		// Replace this with the location of your Filter SDK bin folder.
		return "KEYVIEW_BIN_FOLDER";
	}
}
