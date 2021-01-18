#!/bin/bash

echo -e "*** Should be 20 lines! ***"

data=$(cat test2-pkts.in | \
       ./firewall.exe "src-ip=133.224.177.174/8" 2>/dev/null | \
       ./firewall.exe "dst-ip=130.175.1.84/16" 2>/dev/null| \
       ./firewall.exe "src-port=53-123" 2>/dev/null| \
       ./firewall.exe "dst-port=0-65535" 2>/dev/null)

echo "$data"

[[ $(echo "$data" | wc -l) -eq 20 ]] && \
	echo "*** Test passed *** " && \
	exit 0
	
echo "*** Test failed! ***"