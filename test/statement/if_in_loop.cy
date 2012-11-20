import libio;

int a;

for (a = 0; a < 10; a += 1)
{
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
}
