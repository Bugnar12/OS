#!/bin/bash

for f in `find -type f -name '.txt'`; do
	if grep -iq 'w+@w+.' "$f"; then
		grep -io 'https\?://[a-z0-9]+' "$f"
	fi
done
