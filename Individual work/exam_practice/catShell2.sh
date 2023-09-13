#!/bin/bash

for arg in *.txt; do
	if grep -q -E "cat" "$arg";then
		echo $arg
	fi
done
