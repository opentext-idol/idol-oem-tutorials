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

import com.verity.api.ErrorCode;
import com.verity.api.SeekableInputStream;
import com.verity.api.filter.ExtMainFileInfo;
import com.verity.api.filter.ExtOpenDocConfig;
import com.verity.api.filter.Filter;
import com.verity.api.filter.FilterException;
import java.io.IOException;
import tutorial.MetadataWriter;
import tutorial.OutputWriter;

/* Class for demonstrating Filter functionality. */
class DemoFilter
{
	Filter filter;
	OutputWriter output;
	SeekableInputStream input;

	public DemoFilter(Filter filter, SeekableInputStream input, OutputWriter output)
	{
		this.filter = filter;
		this.input = input;
		this.output = output;
	}

	// Gets the Filter SDK to identify the format of your file
	public void printFormatInformation() throws IOException
	{
		try
		{
			output.writeSubheading("Detected Format");
			input.seek(0);
			filter.setInputSource(input);
			DocFormatInfoWriter.write(filter.getDocFormatInfo(), output);
		}
		catch(FilterException ex)
		{
			output.writeLine("Detection failed: " + ex.getMessage());
		}
	}

	// Prints out metadata that the file stores about itself
	public void printMetadata() throws IOException
	{
		output.writeSubheading("Metadata");
		try
		{
			input.seek(0);
			MetadataWriter.writeMetadata(filter.getMetadata(), output);
		}
		catch(FilterException ex)
		{
			if(ex.getErrorCode() == ErrorCode.KVERR_FormatNotSupported)
			{
				output.writeLine("Metadata cannot be retrieved for this format");
			}
			else
			{
				output.writeLine("ERROR: Could not retrieve metadata: " + ex.getMessage());
			}
		}
	}

	// Prints out the plain text content of the file
	public void printFilteredText() throws IOException
	{
		try
		{
			output.writeSubheading("Filtered Text");
			input.seek(0);
			filter.doFilter(input, output.stream());
			output.write("\n");
		}
		catch(FilterException ex)
		{
			if(ex.getErrorCode() == ErrorCode.KVERR_FormatNotSupported)
			{
				output.writeLine("This format cannot be filtered");
			}
			else
			{
				output.writeLine("ERROR: Could not filter text: " + ex.getMessage());
			}
		}
	}

	// Allows you to perform an action for every subfile.
	public void foreachSubfile(SubfileHandler action) throws IOException
	{
		try
		{
			// First we open the file for extraction
			input.seek(0);
			long docId = filter.extOpenDocument(input, new ExtOpenDocConfig());
			if(docId != 0)
			{
				// Find out how many subfiles there are
				ExtMainFileInfo mainFile = filter.extGetMainFileInfo(docId);

				// Loop over the subfiles
				for(int ii=0; ii<mainFile.getNumSubFiles(); ++ii)
				{
					action.accept(new DemoSubfile(filter, docId, ii, output));
				}
				filter.extCloseDocument(docId);
			}
			else
			{
				output.writeLine("ERROR: Could not open file for extraction");
			}
		}
		catch(FilterException ex)
		{
			if(ex.getErrorCode() == ErrorCode.KVERR_FormatNotSupported)
			{
				// This is not a format we can extract subfiles from
			}
			else
			{
				output.writeLine("ERROR: Could not extract subfiles: " + ex.getMessage());
			}
		}
	}
}
