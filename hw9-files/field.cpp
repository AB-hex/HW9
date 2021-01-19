#include <iostream>
#include <cstring>


#include "field.h"
#include "ip.h"
#include "port.h"


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

	if(this->type == IP){
		return ((Ip*)this)->set_value(val);
	}
	else (this->type == PORT){
		return ((Port*)this)->set_value(val);
	}
	return false;
}

bool Field::match_value(String val) const {
    if(this->type == IP){
        return ((Ip*)this)->match_value(val);
    }
    else (this->type == PORT){
        return ((Port*)this)->match_value(val);
    }
    return false;
}


//bool Field::match_value (String val){
//
//	if(this->type == IP){
//		return ((Ip*)this)->match_value(val);
//	}
//	else (this->type == PORT){
//		return ((Port*)this)->match_value(val);
//	}
//	return false;
//}


bool Field::match(String packet) {
    String* temp;
    size_t size = 0;
    packet.split();


    return false;
}
