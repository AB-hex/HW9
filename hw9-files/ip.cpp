#include <iostream>
#include <cstring>

#include "ip.h"
#define WORD_SIZE 32



Ip::Ip(String pattern):Field(pattern,IP) {}

bool Ip::set_value(String val){

	String* temp;
	size_t num_of_stirngs=0;

	val.split('/' , &temp, &size_t );


	/*** checking if return number of new strings is as expected
	and deletes memory when num is not zeor  ***/
	if( num_of_stirngs != 2 ){
		if( !num_of_stirngs ){
			delete[] temp;
		}
		return false;
	}

	
	int ip = temp[0].to_integer();
	int mask_lngth = temp[1].to_integer; //num of MSB bits mask

	if( mask < 0 || mask > WORD_SIZE ){
		delete[] temp;
		return false;
	}

	unsigned int mask = 1<<(WORD_SIZE - mask_lngth) - 1 ;
	this->low = ip & (~mask);
	this->hight = ip | mask;


	delete[] temp;
	return TRUE;

}

bool I

bool Ip::match_value(String val) const {

    unsigned int ip = val.to_integer();
    if(ip < (this->low) || ip > (this->high)) {
        return false;
    }
    return true;
}

