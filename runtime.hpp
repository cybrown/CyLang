extern "C" {
	void putbyte(char i);
	void putshort(short i);
	void putint(int i);
	void putlong(long long i);
	void putfloat(float f);
	void putdouble(double d);

	short     btos(char arg);
	int       btoi(char arg);
	long long btol(char arg);
	char      stob(short arg);
	int       stoi(short arg);
	long long stol(short arg);
	char      itob(int arg);
	short     itos(int arg);
	long long itol(int arg);
	char      ltob(long long arg);
	short     ltos(long long arg);
	int       ltoi(long long arg);
}
