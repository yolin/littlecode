windowid=`xdotool search --name "Mozilla Firefox" | head -1`
xdotool windowfocus $windowid
xdotool key ctrl+l
xdotool type 192.168.1.1
xdotool key KP_Enter
xdotool sleep 5
xdotool type admin
xdotool key Tab
xdotool type admin
xdotool sleep 1
