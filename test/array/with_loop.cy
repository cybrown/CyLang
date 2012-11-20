import libio;

int[10] array;
int i;
for (i = 0; i < 10; i += 1)
{
	array[i] = i*3;
}
int i;
for (i = 0; i < 10; i += 1)
{
	putint(array[i]);
	putchar(10);
}
