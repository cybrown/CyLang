void putchar(int c);


int pow10(int n) {
    int i = 0;
    int r = 1;
    for (i = 0; i < n; i = i + 1)
    {
        r = r * 10;
    }
    return r;
}

int num_at(int n, int pos) {
    return (n / pow10(pos-1)) - (n / pow10(pos) * 10);
}

void print_int(int a) {
    int iter;
    bool print_zero = false;
    int n;
    for (iter = 10; iter > 0; iter = iter - 1)
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


int test() {
    print_int(503330450);
    putchar(10);
    return num_at(123456, 1);
}
