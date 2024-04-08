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

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.lang.AutoCloseable;

/* For this tutorial code, we write out everything we rerieve using the Filter
 * SDK into one big text file.  For the sake of readability, it's nice to be
 * able to include some headings so you can see what output relates to what.
 */
class OutputWriter implements AutoCloseable
{
	private OutputStream output;

	public OutputWriter(String outputFile)
		throws FileNotFoundException
	{
		output = new FileOutputStream(outputFile);
	}

	public OutputStream stream()
	{
		return output;
	}

	public void writeLine(String text) throws IOException
	{
		this.write(text + "\n");
	}

	public void write(String text) throws IOException
	{
		output.write(text.getBytes(StandardCharsets.UTF_8));
	}

	public void writeHeading(String title) throws IOException
	{
		writeUnderlined(title, "=");
	}

	public void writeSubheading(String title) throws IOException
	{
		writeUnderlined(title, "-");
	}

	private void writeUnderlined(String text, String underlineChar) throws IOException
	{
		this.write("\n" + text + "\n");
		this.write(underlineChar.repeat(text.length()) + "\n\n");
	}

	public void close() throws IOException
	{
		output.close();
	}
}
