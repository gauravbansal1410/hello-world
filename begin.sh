#! /bin/sh
echo "Test text"
x=0
cat /home/gaurav/Documents/mark.html
while [ 1 ]
do
	cp /home/gaurav/Documents/mark.html /home/gaurav/Desktop/mark.html
 	x=$((x+1))
	cat /home/gaurav/Desktop/mark.html
	sleep 1
done
