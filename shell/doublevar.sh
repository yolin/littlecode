#set to double variable

host=master
IP_master=100
#don't use `eval ...`,  only support $(eval ...)
aaa=$(eval echo \$IP_${host})

echo $aaa


#get  double

for i in 1 2 3
do
eval AAA_$i=$i
eval echo \${AAA_$i}
eval "VAL=\"$VAL $(echo \${AAA_$i})\""
done
echo VAL=$VAL
echo ${AAA_1}
echo ${AAA_2}

echo ${AAA_3}
