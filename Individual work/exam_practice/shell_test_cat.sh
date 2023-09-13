#!/bin/bash

for arg in *.txt;do
	if grep -qE "cat" "$arg"; then
		echo "$arg"
	fi
done
