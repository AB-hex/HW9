
TARGET_LIB = firewall
TARGET_APP = firewall.exe
OTHER_LIB = input

LIB_SRCS = string.cpp field.cpp ip.cpp port.cpp  # library source files
APP_SRCS = main.cpp # app source files

CXX = g++  # C compiler
CXXFLAGS = -Wall -Wextra -L. -g #-O2 -g  # C flags
LDFLAGS = -fPIC -shared # linking flags
RM = rm -f   # rm command


all:${TARGET_APP}

$(TARGET_LIB):
	$(CXX) ${CXXFLAGS} ${LDFLAGS} ${LIB_SRCS} -o lib${TARGET_LIB}.so


${TARGET_APP}: ${TARGET_LIB} 
	$(CXX) ${CXXFLAGS} ${APP_SRCS} -o ${TARGET_APP} -l$(TARGET_LIB) -l$(OTHER_LIB)


clean:
	-${RM} ${TARGET_LIB} ${TARGET_APP}