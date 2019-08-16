(
    echo ------1--------------
    flock -x -w 30 200
    echo ------2--------------
    sleep 10
) 200>/tmp/1.lock
