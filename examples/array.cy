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
    for (iter = 20; iter > 0; iter = iter - 1)
    {
        n = num_at(a, iter);
        if (print_zero || n != 0 || iter == 1)
        {
            print_zero = true;
            putchar(48+n);
        }
    }
    return;
}

int[10] arr;

arr[0] = 0;
arr[1] = 8;
arr[2] = 6;
arr[3] = 9;
arr[4] = 42;
arr[5] = 1;
arr[6] = 3;
arr[7] = 7;
arr[8] = 3;
arr[9] = 4;



void sort(int[10] arr) {
    int i;
    boolean f = true;
    int tmp;
    while (f)
    {
        f = false;
        for (i = 0; i < 9; i = i + 1)
        {
            if (arr[i] > arr[i+1])
            {
                tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                f = true;
            }
        }
    }
    return;
}

sort(arr);

int i;
for (i = 0; i < 10; i = i + 1)
{
    print_int(arr[i]);
    putchar(10);
}


int main() {
    __main__();
    return 0;
}
