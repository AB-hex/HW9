#!/bin/bash

echo -e "\n*** Phase 1 - exact match (src-ip) ***"
./firewall.exe "src-ip=3.3.3.3/32" < test1-pkts.in 2>/dev/null

echo -e "\n*** Phase 2 - wildcards (dst-ip=3.3.3.0/24) ***"
./firewall.exe "src-ip = 3.3.3.3/24" < test1-pkts.in 2>/dev/null

echo -e "\n*** Phase 3 - wildcards (dst-ip=3.0.0.0/8) ***"
./firewall.exe "src-ip = 3.0.0.0/8" < test1-pkts.in 2>/dev/null

echo -e "\n*** Phase 4 - exact match (dst-ip) ***"
./firewall.exe "dst-ip=4.4.4.4/32" < test1-pkts.in 2>/dev/null

echo -e "\n*** Phase 5 - wildcard (dst-ip=4.0.0.0/8) ***"
./firewall.exe "dst-ip=4.0.0.0/8" < test1-pkts.in 2>/dev/null

echo -e "\n*** Phase 6 - wildcard (dst-ip=0.0.0.0/0) ***"
./firewall.exe "dst-ip=0.0.0.0/0" < test1-pkts.in 2>/dev/null

echo -e "\n*** Phase 7 - exact match (src-port=1-1) ***"
./firewall.exe "src-port=1-1" < test1-pkts.in 2>/dev/null

echo -e "\n*** Phase 8 - wildcard (dst-port=1-50) ***"
./firewall.exe "dst-port=1-50" < test1-pkts.in 2>/dev/null