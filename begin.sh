# /bin/sh
echo "Test text"
x=0
cat /home/pi/Documents/mark.html
while [ 1 ]
do
	cp /home/pi/Documents/mark.html /home/pi/Desktop/mark.html
 	x=$((x+1))
	echo "<!-- Comment number:" $x"-->" >> /home/pi/Desktop/mark.html
	cat /home/pi/Desktop/mark.html
	echo "----------------------------------------"
	sleep 2
done
