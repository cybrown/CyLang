import libio;
import string;

byte[] data1 = "Hello, ";
byte[] data2 = "World !";

void print(String s) {
	print(s.getData());
}

String s1 = String.create(data1);
String s2 = String.create(data2);

String s = s1.concat(s2);

print(data1); print("\n");
print(s);; print("\n");
data1[4] = '@';
print(data1);; print("\n");
print(s);; print("\n");
data1 = s.getData();
print(data1);; print("\n");
print(s);; print("\n");
print(s.sub(3l, 5l));; print("\n");
print(s.sub(4l));; print("\n");

print(String.create("Hello, ").concat(String.create("World !")));
print("\n");
