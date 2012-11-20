import libio;

int[10] array;

int[] give_me_array() {
	return array;
}

void test() {
	int[] local_array;
	local_array = give_me_array();
	int i;
	for (i = 0; i < 10; i += 1)
	{
		local_array[i] = i*3;
	}
	int i;
	for (i = 0; i < 10; i += 1)
	{
		putint(local_array[i]);
		putchar(10);
	}
	return;
}

test();
