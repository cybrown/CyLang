import libio;

int func_add_int(int a, int b) {
	return a + b;
}

void void_func() {
	putint(func_add_int(42, 60));
	return;
}

void_func();
