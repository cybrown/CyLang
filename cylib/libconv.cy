short extern btos(byte a);
int   extern btoi(byte a);
long  extern btol(byte a);
byte  extern stob(short a);
int   extern stoi(short a);
long  extern stol(short a);
byte  extern itob(int a);
short extern itos(int a);
long  extern itol(int a);
byte  extern ltob(long a);
short extern ltos(long a);
int   extern ltoi(long a);

byte toByte(short s) {
	return stob(s);
}
byte toByte(int i) {
	return itob(i);
}
byte toByte(long l) {
	return ltob(l);
}

short toShort(byte b) {
	return btos(b);
}
short toShort(int i) {
	return itos(i);
}
short toShort(long l) {
	return ltos(l);
}

int toInt(byte b) {
	return btoi(b);
}
int toInt(short s) {
	return stoi(s);
}
int toInt(long l) {
	return ltoi(l);
}

long toLong(byte b) {
	return btol(b);
}
long toLong(short s) {
	return stol(s);
}
long toLong(int i) {
	return itol(i);
}
