#! /bin/sh

sudo echo "4" > /sys/class/gpio/export
sudo echo "17" > /sys/class/gpio/export

sudo echo "in" > /sys/class/gpio/gpio4/direction
sudo echo "in" > /sys/class/gpio/gpio17/direction

l1="/sys/class/gpio/gpio17/value"
l2="/sys/class/gpio/gpio4/value"

status1=$(cat "$l1")
status2=$(cat "$l2")

echo "light1: "$status1
echo "light2: "$status2

id1=1;
id2=2;
light1=1;
light2=0;
while [ 1 ]
do
	status1=$(cat "$l1")
	status2=$(cat "$l2")
	echo "while"
	if [ $status1 != $light1 ]
	then	
		echo "light toggle"
		curl --data "id=$id1&status=$light1" http://192.168.100.123/update.php
		light1=$status1
	fi

	if [ $status2 != $light2 ]
	then
		echo "light toggle"
		curl --data "id=$id2&status=$light2" http://192.168.100.123/update.php
		light2=$status2
	fi
	sleep 1
done
