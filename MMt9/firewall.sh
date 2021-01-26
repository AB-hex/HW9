#!/bin/bash

if [ "$#" -ne 1 ]; then 
	exit 
fi


##sed command will remove empty lines 

## remove spaces, coments and empty lins from the rules

rules=`cat $1 | sed 's:#.*$::g' | sed -r '/^[[:space:]]*$/d' | tr -d ' '`
## remove spaces from the packets
packets=`cat </dev/stdin | tr -d ' '`
output=""
newline=$'\n'


while read packet; 
do 
	 while read rule; 
	do
		IFS=','
		##split a rule to sub rules
		read -a subrules <<< "$rule"
		data="$packet"   
		##check all the subrules for a packet
		for val in "${subrules[@]}" 
		do
			result=$(echo "$data" | ./firewall.exe "$val" 2>/dev/null )
			data="$result"

			if [ -z "$data" ];
			then
				break
			fi
		done
		## if the packet passed all the subrules it inters into output
		output="$output$data$newline"

	done <<< "$rules"
done <<< "$packets"
	
	## print all the packet that passed after sorting and omitting duplications

echo "$output" | sed -r '/^[[:space:]]*$/d'| sort | uniq
