import libio;

void test(int a) {
	switch(a)
	{
		case 1:
			putchar(49); putchar(10);
		case 2:
			putchar(50); putchar(10); break;
		case 3:
			putchar(51); putchar(10);
		case 4:
			putchar(52); putchar(10);
		default:
			putchar(64); putchar(10);
	}
	putchar(10);
	return;
}

void test2(int a) {
	switch(a)
	{
		default:
			putchar(64); putchar(10);
		case 1:
			putchar(49); putchar(10);
		case 2:
			putchar(50); putchar(10); break;
		case 3:
			putchar(51); putchar(10);
		case 4:
			putchar(52); putchar(10);
	}
	putchar(10);
	return;
}

void test3(int a) {
	switch(a)
	{
		case 1:
			putchar(49); putchar(10);
		case 2:
			putchar(50); putchar(10); break;
		case 3:
			putchar(51); putchar(10);
		default:
			putchar(64); putchar(10);
		case 4:
			putchar(52); putchar(10);
	}
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

putchar(10);
putchar(64);
putchar(64);
putchar(10);

test2(1);
test2(2);
test2(3);
test2(4);
test2(5);
test2(6);
test2(3);

putchar(10);
putchar(64);
putchar(64);
putchar(10);

test3(1);
test3(2);
test3(3);
test3(4);
test3(5);
test3(6);
test3(3);
