#!/bin/bash

# Declare array
declare -a ARRAY

count=0

while read LINE; do
    ARRAY[$count]=$LINE
    ((count++))
done < $1

echo -e "number of runs: ${#ARRAY[@]}\n"
echo -e "${ARRAY[@]}\n"


