#include <iostream>
#include <cstring>


#include "field.h"
#include "ip.h"
#include "port.h"

#define FORMAT 0
#define DATA 1



Field::Field(String pattern) {
	this->pattern = pattern;
	this->type = GENERIC;
}


Field::Field (String pattern, field_type type){
	this->pattern = pattern;
	this->type = type;
}


Field::~Field(){}


field_type Field::get_type() const {
    return this->type;
}


bool Field::set_value(String val){
	if(this->get_type() == IP){
		return ((Ip*)this)->set_value(val);
	}
	else if (this->get_type() == PORT){
		return ((Port*)this)->set_value(val);
	}
	return false;
}


bool Field::match_value(String val) const {
    ///exmp: val = XXX.XXX.XXX.XXX
    ///or val = PRT1

    if(this->get_type() == IP){
        return ((Ip*)this)->match_value(val);
    }
    else if (this->get_type() == PORT){
        return ((Port*)this)->match_value(val);
    }
    return false;
}


bool Field::match(String packet) {

    String* data_rule;
    size_t pattern_cnt = 0;


    this->pattern.split("=", &data_rule, &pattern_cnt);
    if(pattern_cnt !=2 ) {
        if( pattern_cnt ){
            delete[] data_rule;
        }
        return false;
    }

    data_rule[FORMAT] = data_rule[FORMAT].trim();

    String* addresses;
    size_t addresses_cnt = 0;
    packet.split(",", &addresses, &addresses_cnt);
    ///validation test of data_address
    if(addresses_cnt != 4 ) {
        if( addresses_cnt ){
            delete[] addresses;
        }
        return false;
    }

    String* data_address;
    size_t data_cnt=0;
    bool result = false;

    for(size_t i=0 ; i < addresses_cnt; i++) {
        addresses[i] = addresses[i].trim();
        addresses[i].split("=", &data_address, &data_cnt);
        if( data_cnt != 2 ){
            continue;
        }
        data_address[FORMAT] = data_address[FORMAT].trim();
        if( data_address[FORMAT].equals(data_rule[FORMAT] ) ){
            result = this->match_value(data_address[DATA].trim() );
            break;
        }
    }

    delete[] data_address;
    delete[] data_rule;
    delete[] addresses;

    return result;
}
