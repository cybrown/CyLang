/*

Tests:
    Recursion.
    For loop.
    If condition.
    Local variables.
    Global variables.
*/

int sum;

int power_recurse(int a, int exp) {
    return exp != 0 ? a * power_recurse(a, exp-1) : 1;
}

int power_loop(int a, int exp) {
    int i;
    int sum;
    sum = a;
    for (i = exp; i > 1; i = i - 1)
    {
        sum = sum * a;
    }
    return sum;
}

int i;
for (i = 1; i < 6; i=i+1)
{
    sum = sum + power_recurse(i, i+1);
}

for (i = 1; i < 6; i=i+1)
{
    sum = sum + power_loop(i, i+1);
}
sum;
33478 == sum;
