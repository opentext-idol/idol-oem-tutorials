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

import com.verity.api.filter.FilterException;
import java.io.IOException;
import java.io.File;

public class StreamingTutorial
{
	public static void main(String[] args)
	{
		if(args.length != 2)
		{
			System.err.println("Usage: StreamingTutorial <inputFile> <outputFile>");
			System.err.println("   Demonstrates usage of the Filter SDK by:");
			System.err.println("      * Filtering all the text from inputFile to outputFile");
			System.err.println("      * Outputting all the metadata from inputFile into outputFile");
			System.err.println("      * Extracting all subfiles of inputFile and performing and repeating");
			System.err.println("        these steps for each of them.");
		}
		else
		{
			try
			{
				outputAllFileData(args[0], args[1]);
			}
			catch(IOException ex)
			{
				System.err.println("IO Exception: " + ex.toString());
			}
			catch(FilterException ex)
			{
				System.err.println("Filtering failed: " + ex.getMessage());
			}
		}
	}
	
	public static void outputAllFileData(String inputFile, String outputFile) throws IOException, FilterException
	{
		System.err.printf("Processing input file %s to %s\n", inputFile, outputFile);

		// This demo extracts and filters subfiles recursively.  For each level
		// of recursion we need a new Filter object.  The FilterPool makes it
		// easy to do this efficiently by allowing you to get a new Filter
		// object whenever you need one, automatically re-using Filter objects
		// you have finished with.
		try(FilterPool filterPool = new FilterPool())
		{
			// We could just pass the input filename to the Filter SDK, instead of creating
			// this SeekableInputStreamImpl.  SeekableInputStreamImpl is here to
			// demonstrate that you could read from any source of file-data that
			// lets you read and seek.
			//
			// You can also pass a non-seekable InputStream to the FIlter SDK, and the Filter SDK
			// will cache whatever data it requires.
			try(SeekableInputStreamImpl input = new SeekableInputStreamImpl(inputFile))
			{
				// The Filter SDK can write to any OutputStream.  In this case we just
				// send the text output to a file.
				try(OutputWriter output = new OutputWriter(outputFile))
				{
					// StreamDemo does the recursive extraction and filtering.
					StreamDemo demo = new StreamDemo(filterPool, output);

					// The demo puts all the output from the demo into a single
					// text file.  Heading make it easy to see which text
					// relates to which file, and which functionality it shows.
					String rootDisplayName = new File(inputFile).getName();
					output.writeHeading(rootDisplayName);
					demo.outputAllFileData(input, rootDisplayName);
				}
			}
		}
	}
}
