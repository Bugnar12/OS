#!/bin/bash

S=0
for F in $1/*.c
do
        N=`grep "[^	]" $F |wc -l`
	S=`expr $S + $N`
done
echo The number is $S
