#! /bin/sh

RESULT_DIR=test
ls $RESULT_DIR | while read dir
do
	if [ -d $RESULT_DIR/"$dir" ]
	then
		ls $RESULT_DIR/"$dir"/*.cy | while read file
		do
			cat "${file%.cy}".cy | ./cyexec -ev 2> /dev/null | diff --brief "${file%.cy}".out - 2> /dev/null > /dev/null && echo -n "Success:" || echo -n "Failure:"
			echo -n " $dir."
			echo $(basename "${file%.cy}")
		done
	fi
done
