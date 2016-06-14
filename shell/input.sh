#!/bin/bash
# trap ctrl-c and call ctrl_c()
trap ctrl_c INT

#tail -f /root/snpowertest_0614101205/console.log &
#tailpid=$!

function ctrl_c() {
        echo "test"
}

while [ "$input" != "EOF" ]
do
    read input
    echo $input > /dev/ttyUSB1
done

#kill $tailpid 2>/dev/null
