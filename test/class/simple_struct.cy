import libio;

class Foo {
	int a;
	int b;
	int c;
	byte[] str;
}

class Bar {
	Foo my_foo2;
	Foo my_foo;
}

void Foo_setStr(Foo this, byte[] s) {
	this.str = s;
}

void Bar_setFooStr(Bar this, byte[] s) {
	this.my_foo.str = s;
}

Bar my_bar = Bar();
my_bar.my_foo = Foo();

Foo_setStr(my_bar.my_foo, "Hello from an Object !\n");

my_bar.my_foo.a = 13;
my_bar.my_foo.a = 40;
my_bar.my_foo.b = 2;
my_bar.my_foo.c = my_bar.my_foo.a + my_bar.my_foo.b;

print(my_bar.my_foo.str);
print(my_bar.my_foo.c + 52);
putchar(10);
