import libio;

class String {

	byte[] data;
	int _len;

	void fromBytes(byte[] s) {
		int l = 0;
		for (l= 0; s[l] != 0b; l = l + 1)
		{
		}
		this._len = l;
		this.data = {byte * (l+1)};
		for (l= 0; s[l] != 0b; l = l + 1)
		{
			this.data[l] = s[l];
		}
		this.data[l] = 0b;
	}

	byte[] getBytes() {
		return this.data;
	}

	int length() {
		return this._len;
	}

	String concat(String other) {
		String res = String();
		int i;
		int cur;
		res._len = this.length() + other.length();

		res.data = {byte * res._len+1};
		res.data[res._len] = 0b;

		cur = 0;
		for (i = 0; this.data[i] != 0b; i = i + 1)
		{
			res.data[i] = this.data[i];
			cur = cur + 1;
		}
		for (i = 0; other.data[i] != 0b; i = i + 1)
		{
			res.data[cur] = other.data[i];
			cur = cur + 1;
		}
		return res;
	}

	static String create(byte[] b) {
		String res = String();
		res.fromBytes(b);
		return res;
	}
}

void print(String str) {
	print(str.getBytes());
}

print(String.create("Hello ").concat(String.create("World !")).concat(String.create(" From Concatenation.")).concat(String.create("\n")));
