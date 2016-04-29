#!/bin/bash

clean_up() {
	echo CLEAN UP!!
	exit
}

trap clean_up term int hup

while true
do
	echo sleeping
	sleep 10
done

clean_up
