ifs="$@"
rps_flowentries=`cat /proc/sys/net/core/rps_sock_flow_entries`
cpunum=`cat /proc/cpuinfo |grep ^processor |wc -l`
echo cpunum:$cpunum
echo /proc/sys/net/core/rps_sock_flow_entries:$rps_flowentries
echo --



for ifn in $ifs
do
rps_queue=`find /sys/class/net/$ifn/queues/ -name "rx-*"`
rps_queuenum=`echo "$rpsqueue"|wc -l`
rps_flowcnt=`echo $(($rps_flowentries/$rps_queuenum))`

echo --
for rxqueue in `find /sys/class/net/$ifn/queues/ -name "rx-*"`
do
    printf $rxqueue/rps_cpus:
    cat $rxqueue/rps_cpus
    printf $rxqueue/rps_flow_cnt:
    cat $rxqueue/rps_flow_cnt
done
echo
done
