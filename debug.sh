#! /bin/sh
gdb --batch -x gdb.txt --quiet --args cyexec "$1" -ev
