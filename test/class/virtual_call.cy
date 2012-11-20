import libio;

class A {
	int bar;
	virtual void p1(int i) {
		print("I am an A\n");
		return;
	}
	virtual void p2(int i) {
		print("I've said I am an A !\n");
		return;
	}
}

class B extends A {
	int foo;

	override void p1(int i) {
		print("I am a B\n");
		return;
	}
	override void p2(int i) {
		print("I've said I am a B !\n");
		return;
	}
}

void exec_p(A param) {
	param.p1(3);
	param.p2(3);
}

A a = A();
B b = B();

exec_p(a);
exec_p(b);
