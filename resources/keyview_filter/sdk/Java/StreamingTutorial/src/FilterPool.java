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
import java.io.IOException;
import java.util.ArrayList;

class FilterPool implements AutoCloseable
{
	private ArrayList<Filter> free = new ArrayList<Filter>();

	// Gets a new Filter object, either by creating a new one, or re-using
	// a free one.
	public Filter getFilter() throws FilterException, IOException
	{
		if(free.isEmpty())
		{
			return createFilter();
		}
		else
		{
			return free.remove(0);
		}
	}

	// Use this to return a Filter object you are finished with to the pool.
	public void returnFilter(Filter filter)
	{
		free.add(filter);
	}

	// Shuts down all the filter objects.
	public void close() throws IOException
	{
		for(Filter filter : free)
		{
			try
			{
				filter.shutdownFilter();
			}
			catch(FilterException ex)
			{
				System.err.println("ERROR: Failed to shut down filter: " + ex.getMessage());
			}
		}
	}
	
	private static Filter createFilter() throws IOException, FilterException
	{
		Filter filter = new Filter(Config.getLicense(), Filter.CHARSET_UTF8, 0);
		// The Java API needs to know where the KeyView libraries
		// (like kvfilter.dll / kvfilter.so) are.
		filter.setFilterDirectory(Config.getFilterBinFolder());

		// Configure Filter to obtain hidden text and embedded images
		filter.setExtractImages(true);
		filter.setShowHiddenSheets(true);
		filter.setShowHiddenText(true);
		filter.setShowFormulas(Filter.ShowFormulas.VALUES_AND_FORMULAS);
		filter.setShowTaggedContent(true);

		// Some presentation formats, like PowerPoint, and PDF files can store
		// text in a strange order, not in the order you'd read it.  These
		// options tell Filter to re-order the text based on its position.
		filter.setFilterLogicalOrder(true);
		filter.setPDFLogicalOrder(Filter.PDF_LOGICAL_ORDER_AUTO);

		// These options cause Filter to output tabular data in a format that
		// Eduction can understand
		filter.setOutputTableDelimiters(true);
		filter.setTabDelimited(true);
		return filter;
	}
}
