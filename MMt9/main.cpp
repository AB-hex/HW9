
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

    char *input_line = (char*)malloc(strlen(rule_format[1].)+1);


   while(std::cin){
       std::cin.getline(input_line,  500);
       String adress(input_line);
       String *adressess;
       adress.trim().split("=",&adressess,&size);
       if(rule.match_value(adressess[1]) ){
           std::cout<<input_line<<std::endl;
       }
   }




    return 0;
}
