import libio;

int a;

for (a = 0; a < 10; a++)
{
	putint(a);
	putchar(10);
}

putchar(10);

for (a = 20; a > 0; a -= 1)
{
	putint(a);
	putchar(10);
}

putchar(10);

for (a = 100; a > -20; a -= 5)
{
	putint(a);
	putchar(10);
}

putchar(10);
