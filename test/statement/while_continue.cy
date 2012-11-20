import libio;

int a = 0;
int b = 0;

while (true)
{
	if (a >= 100)
		break;
	a++;
	if (a%2 == 0)
	{
		b++;
	}
}

putint(a); putchar(10);
putint(b); putchar(10);
