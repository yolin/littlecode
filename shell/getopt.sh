xargs -0 printf '%s\n' </proc/20133/cmdline |
    while read line
    do
        if [ "${line:0:1}" = "-" -a "$isarg" != "1" ]
        then
            isarg=1
        else
            isarg=0
        fi
    done

