#!/bin/bash


directory=$1
total_lines=$(find "$directory" -type f -name "*.txt" -exec cat {} \; | wc -l)
total_files=$(find "$directory" -type f -name "*.txt" | wc -l)

average_lines=$((total_lines / total_files))

echo The number of average lines is : $average_lines
