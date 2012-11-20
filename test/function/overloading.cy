import libio;

void take_int(int a) {
	putint(a);
	putchar(10);
}

void take_double(double f) {
	putdouble(f);
	putchar(10);
}

void take(int a) {
	puts("INT");
	take_int(a);
}

void take(double f) {
	puts("DOUBLE");
	take_double(f);
}

void take(byte[] str) {
	puts(str);
}

take(5);
take(3);
take(3.14);
take(42);
take(-45.32);
take(-34);
take(0);
take(0.0);
take("That's all folks!");
