class String {

	byte[] data;
	long _length;

	byte[] getData() {
		byte[] res;
		res = {byte * this._length};
		long i;
		for (i = 0l; i < this._length; i++)
		{
			res[i] = this.data[i];
		}
		return res;
	}

	void setData(byte[] data, long size) {
		long i;
		this.data = {byte * size};
		for (i = 0l; i < size; i++)
		{
			this.data[i] = data[i];
		}
		this._length = size;
	}

	void setData(byte[] data) {
		long i;
		for (i = 0l; data[i] != 0b; i++) {}
		this.setData(data, i);
	}

	long length() {
		return this._length;
	}

	static String create(byte[] data) {
		String s = String();
		s.setData(data);
		return s;
	}

	String sub(long begin, long end) {
		long tmp;
		if (begin > end)
		{
			tmp = begin;
			begin = end;
			end = tmp;
		}
		if (begin > this._length)
			begin = this._length;
		if (end > this._length)
			end = this._length;
		long i;
		byte[] resb;
		resb = {byte * end-begin +1l};
		for (i = begin; i < end; i++)
		{
			resb[i-begin] = this.data[i];
		}
		resb[i] = 0b;
		return String.create(resb);
	}

	String concat(String other) {
		byte[] res;
		res = {byte * this.length() + other.length() -1l};
		long i;
		for (i = 0l; i < this.length(); i++)
		{
			res[i] = this.data[i];
		}
		long cur;
		cur = i;
		for (i = 0l; i < other.length(); i++)
		{
			res[i+cur] = other.at(i);
		}
		res[this.length()+other.length()-1l] = 0b;
		return String.create(res);
	}

	String sub(long begin) {
		return this.sub(begin, this._length);
	}

	byte at(long pos) {
		return this.data[pos];
	}
}
