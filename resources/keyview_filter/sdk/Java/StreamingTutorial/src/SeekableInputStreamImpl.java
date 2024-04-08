package tutorial;

import com.verity.api.SeekableInputStream;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.RandomAccessFile;
import java.lang.AutoCloseable;

/* Implement a SeekableInputStream to provide a source of file data to KeyView.
 * This example uses a RandomAccessFile to read from disk.
 */
public class SeekableInputStreamImpl implements SeekableInputStream, AutoCloseable
{
	private RandomAccessFile source;

	public SeekableInputStreamImpl(String inputFile) throws FileNotFoundException
	{
		this.source = new RandomAccessFile(inputFile, "r");
	}

	public int read(byte[] bytes, int offset, int length) throws IOException
	{
		return source.read(bytes, offset, length);
	}
	
	public void seek(long position) throws IOException
	{
		source.seek(position);
	}
	
	public long getPosition() throws IOException
	{
		return source.getFilePointer();
	}
	
	public long getSize() throws IOException
	{
		return source.length();
	}

	public void close() throws IOException
	{
		source.close();
	}
}
