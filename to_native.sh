#! /bin/bash

function clean
{
	rm tmp_native.c
	rm out.ss.cbe.c
	rm out.ss
}

./cyexec $1 -o
llc -march=c out.ss
echo "#define cy_malloc(U) malloc(U)" > tmp_native.c
cat out.ss.cbe.c >> tmp_native.c
echo "int main() {__main__(); return 0;}" >> tmp_native.c
gcc runtime.c tmp_native.c
clean
