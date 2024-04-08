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

import com.verity.api.metadata.MetadataElement;
import com.verity.api.metadata.MetadataList;
import java.io.IOException;
import tutorial.OutputWriter;

/* Writes metadata as plain text */
class MetadataWriter
{
	public static void writeMetadata(MetadataList metadata, OutputWriter output)
		throws IOException
	{
		MetadataElement[] elements = metadata.getElements();
		if(elements.length == 0)
		{
			output.writeLine("No metadata");
		}
		else
		{
			output.write(String.format("%16s  %40s  %10s  %s\n",
				"Standardized Key", "Raw Key", "Type", "Value converted to String"));

			for(MetadataElement element : elements)
			{
				output.write(String.format("%16s  %40s  %10s  %s\n",
					element.getStandardKey(),
					element.getKey(),
					element.getValueType(),
					element.getValueAsString()));
			}
			output.write("\n");
		}
	}
}

