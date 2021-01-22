#!/bin/bash

echo -e "\n*** Phase 1 - arg w/o no spaces ***"
./firewall.exe "src-ip=3.3.3.3/32" < test0-pkts.in

echo -e "\n*** Phase 2 - arg w/ spaces in = ***"
./firewall.exe "src-ip = 3.3.3.3/32" < test0-pkts.in

echo -e "\n*** Phase 3 - arg w/ tailing spaces ***"
./firewall.exe "   src-ip = 3.3.3.3/32   " < test0-pkts.in
