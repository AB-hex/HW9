
#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include "input.h"
#include <iostream>
#include <stdlib.h>
#include <cstring>

#define ERROR 1
#define FORMAT 0
#define RULE 1


int main(int argc,char **argv) {

      if( check_args( argc, argv ) ) {
        return ERROR;
      }

    String input(argv[1]);

    String *rule_format;
    size_t size;

    input.split("=",&rule_format,&size);
    
    String ip_dst("dst-ip");
    String ip_src("src-ip");
    String port_dst("dst-port");
    String port_src("src-port");

    input = input.trim();
     /** chek if it's a rule of ip or port*/
    if( ip_dst.trim().equals( rule_format[FORMAT].trim() ) ||
         ip_src.trim().equals( rule_format[FORMAT].trim() ) ){
        
        Ip ip_rule(input);
        ip_rule.set_value(rule_format[RULE]);
        parse_input(ip_rule);


      }
      else if( port_dst.trim().equals( rule_format[FORMAT].trim() ) ||
                 port_src.trim().equals( rule_format[FORMAT].trim())){
  
        
        Port port_rule(input);
        port_rule.set_value(rule_format[RULE]);
        parse_input(port_rule);
      }

  delete[] rule_format;



  return 0;
}
  
