# /bin/sh
echo "Test text"
x=0
cat /home/gaurav/Documents/mark.html
while [ 1 ]
do
	cp /home/gaurav/Documents/mark.html /home/gaurav/Desktop/mark.html
 	x=$((x+1))
	echo "<!-- Comment number:" $x"-->" >> /home/gaurav/Desktop/mark.html
	cat /home/gaurav/Desktop/mark.html
	echo "----------------------------------------"
	sleep 2
done
