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

import com.verity.api.filter.DocFormatInfo;
import java.io.IOException;

/* Writes format detection information as plain text */
class DocFormatInfoWriter
{
	public static void write(DocFormatInfo format, OutputWriter output)
		throws IOException
	{
		output.writeLine(String.format("Class:   %s", format.getDocClass()));
		output.writeLine(String.format("Format:  %s", format.getDocFormat()));
		output.writeLine(String.format("Version: %s", format.getFormatVersion() / 1000.0));
		if(format.isEncrypted()) output.writeLine("File is encrypted");
		if(format.isWindowRMSEncrypted()) output.writeLine("File is Windows RMS Encrypted");
		if(format.isAppleSingleEncoded()) output.writeLine("File is Apple Single Encoded");
		if(format.isAppleDoubleEncoded()) output.writeLine("File is Apple Double Encoded");
		if(format.isMacBinaryEncoded()) output.writeLine("File is Mac Binary Encoded");
		if(format.isWangGDLencoded()) output.writeLine("File is WangGDLEncoded");
	}
}
