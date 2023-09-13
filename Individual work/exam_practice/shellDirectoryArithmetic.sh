#!/bin/bash

total_sum=0
total_file=0

for file in `find . -type d`; do
	if `grep -Eq '*.txt$'`; then
		total_sum=$((total_sum+1))
	fi
	total_file=$((total_file+1))
done

average_mean=$(($total_sum/$total_file))

echo "average mean is : $average_mean"
