#!/bin/bash

debug=0

filejson=$1
filerunlist=${filejson:0:${#filejson}-8}RunList.txt

jsonnew=$(mktemp)

(cat $1 | sed "s:{\"::" | sed "s:}::" | sed "s: \":\n:g" | sed "s:\"::g" | sed "s:\[\[:\[:" | sed "s:]],:]:" | sed "s:]]:]:" | sed "s: ::g" ; echo) > $jsonnew

# Loop over new JSON entries

cp /dev/null $filerunlist

while read linenew ; do
  if [ ! -z "$linenew" ] ; then
   
    if [ $debug -eq 1 ] ; then echo "Checking new line: "$linenew; fi
    runnew=$(echo $linenew | awk -F":" '{print $1}')
    if [ $debug -eq 1 ]; then  echo -e "new run : ${runnew}\n"; fi
    echo $runnew >> $filerunlist    

  fi
done < $jsonnew

rm $jsonnew

