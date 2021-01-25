#!/bin/bash

if [ "$#" -ne 1 ]; then 
	exit 
fi


##sed command will remove empty lines 
##grep command will remove the comments

rules=$(cat $1 | sed 's:#.*$::g' | sed -r '/^[[:space:]]*$/d' | tr -d ' ')
output=""

while read packet; ##from packets stdin src-ip=234.249.119.176,  dst-ip=183.194.38.134,  src-port=123,  dst-port=3392  
do 
	cat "$rules" | while read rule; do #src-ip= 255.174.107.144/32  ,dst-ip  =191.91.51.33/32,src-port=25-25,dst-port=0-65535

		# IFS=',' #delimeter
		# read -a subrules <<< "$rule"
		# data="$packet" # src-ip=234.249.119.176,  dst-ip=183.194.38.134,  src-port=123,  dst-port=3392  
		
		# for val in "${subrules[@]}" # val = src-ip= 255.174.107.144/32
		# do
		# 	data=$( cat "$data" | /.firewall.exe "$val")

		# done

		# grep -qxF "$data" "$output"  ||  echo "$data" >> "$output" 
	done
done <<(cat </dev/stdin | sed 's:#.*$::g' | sed -r '/^[[:space:]]*$/d' | tr -d ' ) 

# cat `cat "$output" | sort | uniq` 