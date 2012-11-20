import libio;

void sort(int[] arr, int size) {
	int tmp;
	int i;
	bool flag = true;
	while (flag)
	{
		flag = false;
		for (i = 0; i < size-1; i += 1)
		{
			if (arr[i] > arr[i+1])
			{
				tmp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = tmp;
				flag = true;
			}
		}
		i = 0;
	}
	return;
}

int[10] array;
array[0] = 51;
array[1] = 32;
array[2] = 83;
array[3] = 10;
array[4] = 42;
array[5] = 96;
array[6] = 35;
array[7] = 75;
array[8] = 25;
array[9] = 97;

int i;

for (i = 0; i < 10; i += 1)
{
	putint(array[i]);
	putchar(10);
}

putchar(10);
sort(array, 10);

for (i = 0; i < 10; i += 1)
{
	putint(array[i]);
	putchar(10);
}
