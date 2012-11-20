import stream;

long extern fopen(byte[] name, byte[] mode);
long extern fread(byte[] data, long len, long num, long descr);
long extern fwrite(byte[] data, long len, long num, long descr);
int  extern fclose(long descr);
int  extern fseek(long descr, long offset, int whence);
long extern ftell(long descr);
void extern rewind(long descr);

class File extends Stream {
	long descriptor;

	bool open(byte[] name, byte[] mode) {
		this.descriptor = fopen(name, mode);
		return (this.descriptor != 0l);
	}

	virtual byte[] read(long len) {
		byte[] data;
		if (this.descriptor != 0l)
		{
			data = {byte * len};
			fread(data, len, 1l, this.descriptor);
		}
		return data;
	}

	virtual long write(byte[] data, long len) {
		long res = 0l;
		if (this.descriptor != 0l)
		{
			res = fwrite(data, len, 1l, this.descriptor);
		}
		return res;
	}

	bool close() {
		if (this.descriptor != 0l)
		{
			fclose(this.descriptor);
			return true;
		}
		return false;
	}

	bool isOpen() {
		return (this.descriptor != 0l);
	}

	void seek(long offset, int whence) {
		if (this.isOpen())
		{
			fseek(this.descriptor, offset, whence);
		}
	}

	long tell() {
		if (this.isOpen())
		{
			return ftell(this.descriptor);
		}
		return 0l;
	}

	void rewind() {
		if (this.isOpen())
			rewind(this.descriptor);
	}

	void append() {
		this.seek(0l, 2);
	}
}
