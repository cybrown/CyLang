import libio;

long bytearray_length(byte[] s)
{
	long l = 0l;
	while (s[l] != 0b)
	{
		l = l + 1l;
	}
	return l;
}

byte[] bytearray_copy(byte[] s)
{
	long l = 0l;
	while (s[l] != 0b)
	{
		l = l + 1l;
	}
	byte[] res;
	l = bytearray_length(s);
	res = {byte * (l+1l)};
	for (l= 0l; s[l] != 0b; l = l + 1l)
	{
		res[l] = s[l];
	}
	res[l] = 0b;
	return res;
}

class CA {
	byte[] message;
	int num;
	byte b;

	void print_msg() {
		print(this.message);
	}

	void setMessage(byte[] m)
	{
		this.message = bytearray_copy(m);
	}
}

class CB {
	CA a1;
	CA a2;
}

CB cb = CB();
cb.a1 = CA();
cb.a2 = CA();

byte[] world = "World !\n";
cb.a1.setMessage("Hello, ");
cb.a2.setMessage(world);

world[1] = 'a';

cb.a1.print_msg();
cb.a2.print_msg();
print (world);
