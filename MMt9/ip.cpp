#include <iostream>
#include <cstring>

#include "ip.h"
#define WORD_SIZE 32
#define MAX_32_BITS 4294967295
////


Ip::Ip(String pattern):Field(pattern,IP) {}

bool Ip::set_value(String val){
///exmp: val = XXX.XXX.XXX.XXX/8
	String* temp;
	size_t numOfStirngs=0;

	val.split("/" , &temp, &numOfStirngs );


	/*** checking if return number of new strings is as expected
	and deletes memory when num is not zero  ***/
	if(numOfStirngs != 2 ){
		if( !numOfStirngs ){
			delete[] temp;
		}
		return false;
	}

	
	int ip = temp[0].to_integer();
	int maskLngth = temp[1].to_integer(); //num of MSB bits mask

	if(maskLngth < 0 || maskLngth > WORD_SIZE ){
		delete[] temp;
		return false;
	}

	unsigned int mask = MAX_32_BITS<<(WORD_SIZE - maskLngth)  ;
	this->low = ip & mask;
	this->high = low|(~mask);

	delete[] temp;
	return true;

}


bool Ip::match_value(String val) const {
///exmp: val = XXX.XXX.XXX.XXX
    unsigned int ip = val.to_integer();
    if(ip < (this->low) || ip > (this->high)) {
        return false;
    }
    return true;
}

