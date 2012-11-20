import libio;

void test(int a) {
	if (a == 1)
		putchar(49);
	else if (a == 2)
		putchar(50);
	else if (a == 3)
		putchar(51);
	else if (a == 4)
		putchar(52);
	else
		putchar(64);
	putchar(10);
	return;
}

test(1);
test(2);
test(3);
test(4);
test(5);
test(6);
test(3);
