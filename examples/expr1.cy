
int fact_recurse(int n) {
    return n == 1 ? 1 : n * fact_recurse(n-1);
}

int power_recurse(int a, int exp) {
    return exp != 0 ? a * power_recurse(a, exp-1) : 1;
}

bool int_to_bool(int n)
{
    return n != 0 ? true : false;
}


int la;
int lb;

float lazy_func_a()
{
    la = 1;
    return 3.14f;
}

float lazy_func_b()
{
    lb = 1;
    return 1.0f;
}

var a = 3b;


void do_no()
{
    return;
}

int test() {
    return fact_recurse(5)+power_recurse(3,3);
}



/*
int test() {
    var b = 0;
    switch(a) {
        case 1b:
            b = b + 11;
            break;
        case 2b:
            b = b + 22;
            break;
        case 3b:
            b = b + 33;
            break;
        default:
            b = b + 44;
    }
    return b;
}
*/

/*
int test() {
    var b = a+1;
    return b;
}
*/

/*
int test() {
    int b;
    b = 10;
    int i;
    for (i = 0; i < 10; i = i + 1)
    {
        b = b + 1;
        if (b == 15)
            continue;
        b = b + 1;
    }
    return b;
}
*/

/*
int test() {
    int i;
    i = 0;
    int j;
    j = 0;
    int b;
    b = 10;
    do
    {
        j = 0;
        if (i >= 9) break;
        while (true)
        {
            if (j >= 9)
                break;
            b = b + 1;
            j = j + 1;
        }
        i = i + 1;
    } while (true);
    return b;
}
*/



/*
int test() {
    a = 0;
    switch(6) {
        case 1:
            a = a + 11;
            break;
        case 2:
            a = a + 22;
            break;
        case 3:
            a = a + 33;
            break;
        default:
            a = a + 44;
    }
    return a;
}
*/

/*
int test()
{
    la = 0;
    lb = 0;
    return (lazy_func_a() || lazy_func_b()) == 3.14f ? 1 : 0;
}
*/


/*
int a;

int grrr() {
    int c;
    int d;
    return 1;
}

int test() {
    int b;
    a = 4;
    return a;
}
*/
/*
int test() {
    int i;
    for (i = 0; i < 33; i = i + 1)
    {
    }
    return i;
}
*/


/*
int test()
{
    int a;
    a = 4;
    int b;
    b = 0;
    int i;
    i = 0;
    if (a == 4)
    {
        b = 3;
        while (i < 10)
        {
            i = i + 1;
            b = b + 2;
        }
    }
    return b;
}
*/



/*
int test1()
{
    int iterator;
    iterator = 0;
    while (iterator < 5)
    {
        iterator = iterator + 1;
        iterator = iterator + 3;
    }
    return iterator;
}
*/


/*
int test1()
{
    int a;
    int i;
    while (i < 6)
        i = i + 1;
    a = i;
    return fact(a);
}
*/
