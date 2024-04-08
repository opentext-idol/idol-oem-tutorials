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

import com.verity.api.filter.Filter;
import com.verity.api.filter.FilterException;
import com.verity.api.SeekableInputStream;
import java.io.IOException;
import java.io.File;

/* Demonstrates using the Java streaming APIs in the Filter SDK */
public class StreamDemo
{
	private FilterPool filterPool;
	private OutputWriter output;

	public StreamDemo(FilterPool filterPool, OutputWriter output)
	{
		this.filterPool = filterPool;
		this.output = output;
	}

	// Output information about the file passed in, recursing into each subfile
	public void outputAllFileData(SeekableInputStream inputFile, String displayName) throws FilterException, IOException
	{
		Filter filter = filterPool.getFilter();
		try
		{
			DemoFilter demoFilter = new DemoFilter(filter, inputFile, output);
			// Print out the file format, metadata, and plain text content
			demoFilter.printFormatInformation();
			demoFilter.printFilteredText();
			demoFilter.printMetadata();

			// Loop over the subfiles so we can do the same of each of them
			demoFilter.foreachSubfile(new SubfileHandler() {;
				public void accept(DemoSubfile subfile) throws FilterException, IOException
				{
					handleSubfile(filter, subfile, displayName);
				}
			});
		}
		finally
		{
			filterPool.returnFilter(filter);
		}
	}

	// Output the information about a subfile and then extract it and pass it
	// back to outputAllFileData.
	public void handleSubfile(Filter filter, DemoSubfile subfile, String parentDisplayName) throws FilterException, IOException
	{
		// To help you see which file the text in the output file relates to.
		String displayName = parentDisplayName + "/" + subfile.getName();
		System.err.printf("Processing subfile %s\n", displayName);
		output.writeHeading("Subfile: " + displayName);

		// Print metadata the parent file stores about this subfile.
		subfile.printMetadata();

		// If the file can be extracted, do so.
		File extractedSubfile = subfile.extract();
		if(extractedSubfile != null)
		{
			// Create an input stream for the file extracted, and pass it back
			// to outputAllFileData to get detection info, metadata, plain text
			// and to recursively extract its subfiles.
			try(SeekableInputStreamImpl subfileStream = new SeekableInputStreamImpl(extractedSubfile.getPath()))
			{
				outputAllFileData(subfileStream, displayName);
			}
			finally
			{
				extractedSubfile.delete();
			}
		}
	}}
