#!/bin/bash

A=$1
B=$2

find $A -type f | while read F; do
	N=`ls -l $F | awk '{print $5}'`
	if test $N -gt $B; then
		echo $F
	fi
done

