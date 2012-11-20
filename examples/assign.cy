void putchar(int c);

int fact(int a) {
    return a == 1 ? 1 : a * fact(a-1);
}

int pow10(int n) {
    int i = 0;
    int res = 1;
    for (i = 0; i < n; i = i + 1)
    {
        res = res * 10;
    }
    return res;
}

int pow(int a, int exp) {
    int i;
    int res;
    res = a;
    for (i = exp; i > 1; i = i - 1)
    {
        res = res * a;
    }
    return res;
}

int num_at(int n, int pos) {
    return (n / pow10(pos-1)) - (n / pow10(pos) * 10);
}

void print_int(int a) {
    int iter;
    bool print_zero = false;
    int n;
    for (iter = 10; iter > 0; iter -= 1)
    {
        n = num_at(a, iter);
        if (print_zero || n != 0)
        {
            print_zero = true;
            putchar(48+n);
        }
    }
    return;
}

int a = 2;
int b = 3;
print_int(a); putchar(10);
print_int(b); putchar(10);
print_int(b *= a); putchar(10);
print_int(b);
putchar(10);
