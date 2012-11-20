#! /bin/sh

RESULT_DIR=test
ls $RESULT_DIR | while read dir
do
	if [ -d $RESULT_DIR/"$dir" ]
	then
		echo $dir
		ls $RESULT_DIR/"$dir"/*.cy | while read file
		do
			echo "$file"
			cat "${file%.cy}".cy | ./cyexec -ev > "${file%.cy}".out
		done
	fi
done
