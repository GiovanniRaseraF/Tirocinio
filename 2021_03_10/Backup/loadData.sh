#/bin/bash
while read p
do   
    echo "$p" >&3
    sleep $1 
done
