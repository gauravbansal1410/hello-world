#! /bin/sh
echo "Test text"
rm /home/gaurav/Desktop/templog.txt
x=0
while [ 1 ]
do
	x=$((x+1))
	echo -n $x": " >> templog.txt
	./a.out >> templog.txt
	cat templog.txt
	echo "--------------------------------------"
	sleep 2
done
