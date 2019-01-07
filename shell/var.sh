#!/bin/sh

for i in 1 2 3
do
eval AAA_$i=$i
done
echo ${AAA_1}
echo ${AAA_2}
echo ${AAA_3}
