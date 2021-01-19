#include <iostream>
#include <cstring>


#include "field.h"
#include "ip.h"
#include "port.h"


Field::Field(String pattern) {

	this->pattern = pattern;
	this->field_type = GENERIC;

}

Field::Field (String pattern, field_type type){
	this->pattern = pattern;
	this->attern = type;

}


Field::~Field(){}




field_type Field::get_type(){

	return this->type;
}

bool Field::set_value(String val){

	if(this->type == IP){

		
		return ((Ip*)this)->set_value(val);
	}
	else (this->type == PORT){
		Port port = new PORT(this->pattern);
		return ((Port*)port)->set_value(val);
	}
	return FALSE;
}

bool Field::match_value (String val){

	if(this->type == IP){
		return ((Ip*)this)->match_value(val);
	}
	else (this->type == PORT){
		return ((Port*)this)->match_value(val);
	}
	return FALSE;
}

bool Field::match(String packet){
	
	String* temp;
	size_t size = 0;
	packet.split()
	


	return FALSE;
}