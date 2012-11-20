import libio;

int[2][3] a;
a = {{42, 21, 3},{83, 46, 51}};
int i;
int j;
for (i = 0; i < 2; i++)
{
	for (j = 0; j < 3; j++)
	{
		putint(a[i][j]);
		putchar(10);
	}
}
//byte[] str = {'L','i','t','e','r','a','l',' ','o','f',' ','c','h','a','r','s',' ','!', 0b};
byte[] str = "Literal of chars !";
byte[][] strings = {
	{'H','e','l','l','o',' ', 0b},
	{'A','r','r','a','y', 0b}
};
puts(str);
puts({'L','i','t','e','r','a','l',' ','o','f',' ','c','h','a','r','s',' ','!', 0b});
puts(strings[0]);
puts(strings[1]);
