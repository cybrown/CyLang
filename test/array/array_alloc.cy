import libio;

int[] a;
int[] b;
a = {int * 100l};
a[1] = 42;
b = a;
a = {int * 100l};
a[1] = 51;
print(b[1]);
putchar(10);
print(a[1]);
putchar(10);
