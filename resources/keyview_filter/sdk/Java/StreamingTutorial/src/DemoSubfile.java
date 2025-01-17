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

import com.verity.api.Charset;
import com.verity.api.ErrorCode;
import com.verity.api.filter.Filter;
import com.verity.api.filter.FilterException;
import com.verity.api.filter.ExtSubFileExtractConfig;
import com.verity.api.filter.ExtSubFileExtractInfo;
import com.verity.api.filter.ExtSubFileInfo;
import java.io.File;
import java.io.IOException;
import java.util.UUID;
import tutorial.OutputWriter;
import tutorial.MetadataWriter;


/* Demonstrates the things you can do with a subfile */
class DemoSubfile
{
	Filter filter;
	long docId;
	int subfileIndex;
	OutputWriter output;

	public DemoSubfile(Filter filter, long docId, int subfileIndex, OutputWriter output)
	{
		this.filter = filter;
		this.docId = docId;
		this.subfileIndex = subfileIndex;
		this.output = output;
	}

	// Files can contain their own metadata, and container files can contain
	// metadata about their subfiles.  This prints out the metadata the parent
	// file stores for this subfile
	public void printMetadata() throws IOException
	{
		try
		{
			output.writeSubheading("Subfile Metadata");
			MetadataWriter.writeMetadata(filter.extGetSubFileMetadataList(docId, subfileIndex), output);
		}
		catch(FilterException ex)
		{
			if(ex.getErrorCode() == ErrorCode.KVERR_FormatNotSupported)
			{
				output.writeLine("No metadata for this type of subfile");
			}
			else
			{
				output.writeLine("ERROR: Could not get subfile metadata: " + ex.getMessage());
			}
		}
	}

	// Extract this subfile to a uniquely named temporary file
	public File extract() throws IOException
	{
		try
		{
			output.writeSubheading("Information about this subfile");
			ExtSubFileInfo subfile = filter.extGetSubFileInfo(docId, subfileIndex);

			if(subfile.isFolder())
			{
				output.writeLine(String.format("Subfile %d is a folder called %s", subfileIndex, subfile.getSubFileName()));
				return null;
			}
			else if(subfile.isExternal())
			{
				output.writeLine(String.format("Subfile %d is an external link to %s", subfileIndex, subfile.getSubFileName()));
				return null;
			}
			else
			{
				output.writeLine(String.format("Subfile %d is called %s", subfileIndex, subfile.getSubFileName()));

				String temporaryFileName = UUID.randomUUID().toString();
				ExtSubFileExtractInfo extractInfo = filter.extExtractSubFile(docId, subfileIndex, createExtractConfig(temporaryFileName));

				output.writeSubheading("Detection information from the extraction result");
				DocFormatInfoWriter.write(extractInfo.getDocFormatInfo(), output);

				if(extractInfo.isExternal())
				{
					output.writeLine("Subfile is an external link");
					return null;
				}
				
				// If you pass in a filename containing invalid characters the Filter SDK
				// can extract to a different file path to the one you passed in.
				// This is highly unlikely to happen the way we are using the API
				// here.
				return new File(extractInfo.getFilePath());
			}
		}
		catch(FilterException ex)
		{
			output.writeLine(String.format("ERROR: Failed to extract subfile: %s", ex.getMessage()));
		}
		return null;
	}

	public String getName() throws IOException
	{
		try
		{
			ExtSubFileInfo subfile = filter.extGetSubFileInfo(docId, subfileIndex);
			return subfile.getSubFileName();
		}
		catch(FilterException ex)
		{
			return "<ERROR: Name unavailable: " + ex.getMessage() + ">";
		}
	}

	private static ExtSubFileExtractConfig createExtractConfig(String destinationName)
	{
		ExtSubFileExtractConfig config = new ExtSubFileExtractConfig();

		// If we extract email body text, get the HTML/RTF version rather than
		// the plain text version, and convert it to UTF8.
		config.setGetFormattedBody(true);
		config.setTargetCharset(Charset.KVCS_UTF8);

		// Where to extract the file to.  In an actual application you would
		// probably choose to extract to a temporary folder.
		config.setExtractDirectory(".");
		config.setFilePath(destinationName);

		return config;
	}

}
