import libio;

int a;

a = 0;
do
{
	putint(a);
	putchar(10);
	a += 1;
} while (a < 10);

putchar(10);

a = 20;
do
{
	putint(a);
	putchar(10);
	a -= 1;
} while (a > 0);

putchar(10);

a = 100;
do
{
	putint(a);
	putchar(10);
	a -= 5;
} while (a > -20);

putchar(10);
