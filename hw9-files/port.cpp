#include <iostream>
#include <cstring>

#include "port.h"
#define MAX_PORT 65535
#define START 0
#define END 1




Port::Port(String pattern):Field(pattern,PORT){}

bool Port::set_value(String val){
///example val = PRT1-PRT2
	String *temp;
	size_t size = 0;

	val.split("-", &temp, &size);
	if(size != 2){
		if( !size ){
			delete[] temp;
		}
		return false;
	}

	int val0 = temp[0].to_integer();
	int val1 = temp[1].to_integer();
	delete[] temp;

	if(val0<0 || val0 > MAX_PORT || val1 < 0 || val1 > MAX_PORT){
		return false;
	}

	if(val0 > val1) {
		return false;
	}

	this->range[START] = val0;
	this->range[END] = val1;

	return true;
}


bool Port::match_value(String val) const {
    ///exmple val = port
    int port = val.to_integer();
    return ( ( this->range[START]) <= port)
                 && (port <= (this->range[END]) );

}