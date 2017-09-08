#! /bin/sh
echo "Test text"
rm /home/pi/Desktop/templog.txt
x=0
while [ 1 ]
do
	x=$((x+1))
	echo -n $x": " >> templog.txt
	./temphum.py 22 22 >> templog.txt
	cat templog.txt
	echo "--------------------------------------"
	sleep 2
done
