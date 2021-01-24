
#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include "input.h"
#include <iostream>
#include <stdlib.h>
#include <cstring>

#define ERROR 1

int main(int argc,char **argv) {

    String Ip_String(*argv);
    Ip rule(Ip_String);
    String *rule_format;
    size_t size;
    Ip_String.split("=",&rule_format,&size);
    if(rule.set_value(rule_format[1])){
        return ERROR;
    }


    for(std::string line ; std::getline(std::cin, line);){

    String adress(line.c_str());
    String *adressess;
    adress.trim().split("=",&adressess,&size);
    if(rule.match_value(adressess[1]) ){
           std::cout << line << std::endl;
       }

    }

delete[] rule_format;



    return 0;
}
