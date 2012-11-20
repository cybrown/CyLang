import libio;

int fact(int a, int dummy) {
	print("INT");
    return a == 1 ? 1 : a * fact(a-1, 0);
}


long fact(long a, int dummy) {
	print("LONG");
    return a == 1l ? 1l : a * fact(a-1l, 0);
}


long res;
long i;
for (i = 5l; i <= 7l; i = i + 1l)
{
    res = res + fact(i, 0);
}


print(res);
putchar(10);
print(true);
