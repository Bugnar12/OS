#!/bin/bash

# Find .txt files in the current directory and its subdirectories
find . -type f -name "*.txt" | while read -r file; do
    # Check if the file contains the word "cat"
    if grep -q "cat" "$file"; then
        # Display the name of the file
        echo "$file"
    fi
done

