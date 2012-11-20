void extern putchar(int c);
void extern putbyte(byte c);
void extern putshort(short c);
void extern putint(int c);
void extern putlong(long c);
void extern putfloat(float f);
void extern putdouble(double d);
void extern puts(byte[] str);
void extern printf(byte[] str);

void print(byte c) {
	putbyte(c);
}

void print(short c) {
	putshort(c);
}

void print(int c) {
	putint(c);
}

void print(long c) {
	putlong(c);
}

void print(float f) {
	putfloat(f);
}

void print(double d) {
	putdouble(d);
}

void print(byte[] str) {
	printf(str);
}

void print(bool c) {
	print(c ? "true" : "false");
}
