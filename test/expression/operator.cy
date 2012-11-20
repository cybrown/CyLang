import libio;

int a = 2;
int b = 3;
int c = 60;

double da = 2.0;
double db = 3.0;
double dc = 60.0;

//  Testing precedence
putint(a + b * c); putchar(10);
putint((a + b) * c); putchar(10);

// Testing int ops
putint(a + c); putchar(10);
putint(a - c); putchar(10);
putint(a * c); putchar(10);
putint(a / c); putchar(10);
putint(a % c); putchar(10);
putint(a & c); putchar(10);
putint(a | c); putchar(10);
putint(a << c); putchar(10);
putint(a >> c); putchar(10);

// Testing double ops
putdouble(da + dc); putchar(10);
putdouble(da - dc); putchar(10);
putdouble(da * dc); putchar(10);
putdouble(da / dc); putchar(10);
