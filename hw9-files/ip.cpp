#include <iostream>
#include <cstring>

#include "ip.h"
#define WORD_SIZE 32



Ip::Ip(String pattern):Field(pattern,IP) {}

bool Ip::set_value(String val){

	String* temp;
	size_t num_of_stirngs=0;

	val.split("/" , &temp, &num_of_stirngs );


	/*** checking if return number of new strings is as expected
	and deletes memory when num is not zeor  ***/
	if( num_of_stirngs != 2 ){
		if( !num_of_stirngs ){
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

	unsigned int mask = 1<<((WORD_SIZE - maskLngth) - 1) ;
	this->low = ip & (~mask);
	this->high = ip | mask;


	delete[] temp;
	return true;

}

bool I

bool Ip::match_value(String val) const {

    unsigned int ip = val.to_integer();
    if(ip < (this->low) || ip > (this->high)) {
        return false;
    }
    return true;
}

