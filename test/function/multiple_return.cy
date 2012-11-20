import libio;

int multi_ret(int a) {
	if (a == 1)
	{
		return 1;
		return 3;	// This instruction shouldn't be in the bytecode
	}
	if (a == 2)
		return 2;
	return 3;
}

putint(multi_ret(-1));putchar(10);
putint(multi_ret(multi_ret(1)));putchar(10);
putint(multi_ret(2));putchar(10);
putint(multi_ret(3));putchar(10);
putint(multi_ret(-1));putchar(10);
putchar(10);
