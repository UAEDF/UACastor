#!/bin/bash

# Declare array
declare -a ARRAY

# stdin replaced with a file supplied as a first argument
# exec < $1

count=0

while read LINE; do
    ARRAY[$count]=$LINE
    ((count++))
done < $1

echo Number of elements: ${#ARRAY[@]}

# echo array's content
echo ${ARRAY[@]}


