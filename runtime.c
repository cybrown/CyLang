#include <stdio.h>
#include <stdlib.h>

void putbyte(char i) {
	printf("%i", i);
}

void putshort(short i) {
	printf("%i", i);
}

void putint(int i) {
	printf("%i", i);
}

void putlong(long long i) {
	printf("%lld", i);
}

void putfloat(float f) {
	printf("%f", f);
}

void putdouble(double d) {
	printf("%f", d);
}

short btos(char arg) {
	return (short)arg;
}

int btoi(char arg) {
	return (int)arg;
}

long long btol(char arg) {
	return (long long)arg;
}

char stob(short arg) {
	return (char)arg;
}

int stoi(short arg) {
	return (int)arg;
}

long long stol(short arg) {
	return (long long)arg;
}

char itob(int arg) {
	return (char)arg;
}

short itos(int arg) {
	return (short)arg;
}

long long itol(int arg) {
	return (long long)arg;
}

char ltob(long long arg) {
	return (char)arg;
}

short ltos(long long arg) {
	return (short)arg;
}

int ltoi(long long arg) {
	return (int)arg;
}
