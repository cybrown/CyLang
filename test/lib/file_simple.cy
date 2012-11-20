import libio;
import file;

File f = File();
f.open("test.txt", "a+");

if (!f.isOpen())
{
	print("File not open...\n");
}
else
{
	print("File open ! \n");
	f.write("foo\n", 4l);
	f.close();

	f.open("test.txt", "r");
	f.rewind();


	print(f.read(3l));
	print("\n");
	f.close();
}
