#!/bin/bash

#check With TA:
#1. will there be rules with empty filters? "   ,,,,src-ip=1.1.1.1/32,,,, "
#2. how to treat recurring packets? (in out implementation we assume no recurring packets)


final_list=""

while read packet
do
	while read rule
	do
		rule_matched_packets=""

		#remove spaces, comments and empty lines
		rule=`echo "$rule" | tr -d ' ' | sed -e 's/#.*//'`
		if [[ "$rule" == "" ]]; then
			continue
		fi

		#split $rule with delimiter ',' and place the result into array called 'filters'
		readarray -d , -t filters <<< "$rule"
		for filter in "${filters[@]}"
		do
			#valgrind --leak-check=full 
			rule_matched_packets+=`echo "$packet" | ./firewall.exe "$filter"`
			rule_matched_packets+="\n"
		done


		# echo -e  treat \n as new line and print packets
		# sed:	remove empty lines
		# sort
		# uniq -c: get the number of repeating packets
		# grep -E: match all packets which repeted "number of filters" times 
		# grep -E: clean the numeric addition of "uniq -c" command from the packet
		final_list+=`echo -e "${rule_matched_packets}" | sed '/^$/d' | sort | uniq -c  | grep -E "^ *${#filters[@]} " | sed -e "s/^ *${#filters[@]} //"`
		final_list+="\n"


	 done < "$1"

done

	echo -e "${final_list}" | sed '/^$/d' | tr -d ' ' | sort




#rule:		src-ip=1.1.1.1/32 , dst-ip=2.2.2.2/32 

#packet1:	src-ip=1.1.1.1 , dst-ip=2.2.2.2
#packet2:	src-ip=1.1.1.1	



#output after for
#src-ip=1.1.1.1,dst-ip=2.2.2.2
#src-ip=1.1.1.1,dst-ip=2.2.2.2
#src-ip=1.1.1.1


#output after uniq -c
#       2 src-ip=1.1.1.1,dst-ip=2.2.2.2
#       1 src-ip=1.1.1.1



#output after sed 
#src-ip=1.1.1.1,dst-ip=2.2.2.2


