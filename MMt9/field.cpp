#include <iostream>
#include <cstring>


#include "field.h"
#include "ip.h"
#include "port.h"

#define FORMAT 0
#define DATA 1



Field::Field(String pattern) {
///Example = src-ip=XXX.XXX.XXX.XXX/8
///or dst-port=PRT1-PRT2
	this->pattern = pattern;
	this->type = GENERIC;

}

Field::Field (String pattern, field_type type){
    ///Example = src-ip=XXX.XXX.XXX.XXX/8
    ///or val = dst-port=PRT1-PRT2
	this->pattern = pattern;
	this->type = type;

}


Field::~Field(){}


field_type Field::get_type() const {
    return this->type;
}


bool Field::set_value(String val){
///exmp: val = XXX.XXX.XXX.XXX/8
///or val = PRT1-PRT2
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

    ///example packet =
    /// src-ip=XXX.XXX.XXX.XXX,dst-ip=YYY.YYY.YYY.YYY,src-port=PRT,dst-port=PRT


    ////data_rule[FORMAT] = src-ip - will use it for know looking packet is src or dst
    /// data_rule[DATA] = XXX.XXX.XXX.XXX/3
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


///example addresses[i] =  src-ip=XXX.XXX.XXX.XXX
/// dst-ip=YYY.YYY.YYY.YYY
/// src-port=PRT etc..
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





////data_address[0] = src-ip
/// data_address[1] = XXX.XXX.XXX.XXX
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
