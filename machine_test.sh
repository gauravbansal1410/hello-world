#! /bin/sh

sudo echo "17" > /sys/class/gpio/export

sudo echo "in" > /sys/class/gpio/gpio17/direction

l1="/sys/class/gpio/gpio17/value"

status1=$(cat "$l1")

echo "machine1: "$status1

id1=1;
id2=2;
machine1=1;
while [ 1 ]
do
	status1=$(cat "$l1")
	echo "while"
	if [ $status1 != $machine1 ]
	then	
		echo "Machine status change"
		curl --data "id=$id1&status=$machine1" http://192.168.100.118/machine_update.php
		machine1=$status1
	fi
	sleep 1
done
