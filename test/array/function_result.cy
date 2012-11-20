import libio;

int[3] arr;

int[] ret_arr() {
	return arr;
}

ret_arr()[0] = 40;
ret_arr()[1] = 2;
ret_arr()[2] = ret_arr()[0] + ret_arr()[1];

putint(ret_arr()[2]);
putchar(10);
