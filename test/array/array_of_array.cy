import libio;

int[2] arr0;
int[2] arr1;

int[2][2] arr;
int[2][2] arre;
int[2][2] arree;

arr[0] = arr0;
arr[1] = arr1;

// Testing successive affectation of arrays
arree = arre = arr;

arr[0][1] = 42;
arr[1][0] = 64;
arr[1][1] = 1515;

putint(arree[0][1]); putchar(10);
putint(arree[1][0]); putchar(10);
putint(arree[1][1]); putchar(10);
putchar(10);

putint(arr0[1]); putchar(10);
putint(arr1[0]); putchar(10);
putint(arr1[1]); putchar(10);
putchar(10);
