#include <iostream>
#include <cstring>

#include "port.h"
#define MAX_PORT 65535
#define START 0
#define END 1




Port::Port(String pattern):Field(pattern,PORT){}
/*valid arg for set_value is "PORT1-PORT2, is splitted by 
delimerter '-' and then converted to interger and stored 
in their sturct variables low and high
valid tests make sure that PORT1 smaller than PORT2 
and split value retuned size is 2 */
bool Port::set_value(String val){
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
/*valid arg for match value is PORT  */

bool Port::match_value(String val) const {
    int port = val.to_integer();
    return ( ( this->range[START]) <= port)
                 && (port <= (this->range[END]) );

}
