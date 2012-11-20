import libio;

int a = 0;
putint(a++); putchar(10);
putint(a--); putchar(10);
putint(a--); putchar(10);

putint(++a); putchar(10);
putint(--a); putchar(10);
putint(++a); putchar(10);

float f = 5.0f;
double d = 5.0d;
putfloat(f++); putchar(10);
putfloat(f--); putchar(10);
putfloat(f++); putchar(10);

putdouble(--d); putchar(10);
putdouble(++d); putchar(10);
putdouble(--d); putchar(10);