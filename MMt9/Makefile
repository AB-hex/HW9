

CXX = g++  
CXXFLAGS = -Wall -Wextra -L. -g -std=c++11


all: firewall.exe

firewall:
	$(CXX) ${CXXFLAGS} -fPIC -shared string.cpp field.cpp ip.cpp port.cpp -o   libfirewall.so


firewall.exe: firewall 
	$(CXX) ${CXXFLAGS} main.cpp -o firewall.exe -l firewall -l input


clean:
	-rm -f firewall firewall.exe
