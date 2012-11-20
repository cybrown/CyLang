import libio;

int a = 0;

void ret() {
	a = 5;
}

ret();

putint(a);
putchar(10);
