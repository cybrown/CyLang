import libio;

int a;

a = 0;
while (a < 10)
{
	putint(a);
	putchar(10);
	a += 1;
}

putchar(10);

a = 20;
while (a > 0)
{
	putint(a);
	putchar(10);
	a -= 1;
}

putchar(10);

a = 100;
while (a > -20)
{
	putint(a);
	putchar(10);
	a -= 5;
}

putchar(10);
