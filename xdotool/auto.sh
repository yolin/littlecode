#!/bin/bash

while true; do
    windowid=`xdotool search --name "Mozilla Firefox" | head -1`
    lefttop_x=537
    lefttop_y=157

    function mouse_moveto {
        xdotool mousemove --sync $lefttop_x $lefttop_y
        xdotool mousemove_relative -- $(($1-$lefttop_x)) $(($2-$lefttop_y)) click 1
    }

    xdotool windowfocus $windowid
    xdotool sleep 2
    xdotool key ctrl+l
    xdotool sleep 3
    xdotool type 192.168.1.1
    xdotool key KP_Enter
    xdotool sleep 10 
    xdotool type admin
    xdotool key Tab
    xdotool type admin
    xdotool sleep 3
    xdotool key KP_Enter
    xdotool sleep 10
    mouse_moveto 1653 249
    xdotool sleep 3
    mouse_moveto 631 886
    xdotool sleep 3
    mouse_moveto 832 432
    xdotool sleep 3
    xdotool type EWS1025
    xdotool sleep 1
    xdotool key KP_Enter
    xdotool sleep 4
    mouse_moveto 1132 434
    xdotool sleep 15
    mouse_moveto 896 372
    xdotool sleep 100
    while true;do
        wget -O /tmp/testfile.tmp -T 3 -q http://192.168.1.1 2>/dev/null
        if [ $? -eq 0 ];then
            break
        fi
    done
done
