#!/bin/bash

for file in "$1"/*.txt
do
	if [[ -f "$file" ]]
	then
		if grep -q "cat" "$file"
		then
			echo "$file"
		fi
	fi
done

