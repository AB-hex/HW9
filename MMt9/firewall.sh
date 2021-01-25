#!/bin/bash

if [ "$#" -ne 1 ]; then 
	exit 
fi


##sed command will remove empty lines 
##grep command will remove the comments
rules=$(cat $1 | sed 's:#.*$::g' | sed -r '/^[[:space:]]*$/d' | tr -d ' ' ) 

output=""

while read line; ##from packets stdin src-ip=234.249.119.176,  dst-ip=183.194.38.134,  src-port=123,  dst-port=3392  
do 
	while read rule; #src-ip= 255.174.107.144/32  ,dst-ip  =191.91.51.33/32,src-port=25-25,dst-port=0-65535
	do

		IFS=',' #delimeter
		read -a subrules <<< "$rule" 
		data=$(echo $line) # src-ip=234.249.119.176,  dst-ip=183.194.38.134,  src-port=123,  dst-port=3392  
		for val in "${subrules[@]}" # val = src-ip= 255.174.107.144/32
		do
			data=$( cat "$data" | /.firewall.exe "$val")

		done

		grep -qxF "$data" "$output"  ||  echo "$data" >> "$output" 

	done < "$rules"
done 

cat `sort "$output"` 