#!/bin/bash

directory=$1

find "$directory" -type f -name '*' | while read file; do
	if echo "$file" | grep -qE '[0-9]{5,}'; then
		echo "$file"
	fi
done
