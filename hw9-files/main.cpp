
#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"

int main() {
   // std::cout << "Hello, World!" << std::endl;

    //String a("  169.5.19.4 ");
    //String b=a.trim();
    //bool g= a.equals("  169.5.19.4 ");
    //size_t size =0;
    //String *strings;
    //a.split("/.",&strings,&size);
    //unsigned ip=a.to_integer();
    String my_string("src-ip=133.224.177.174/4");
    Field field1(my_string);
    Ip new_ip(my_string);
    String test_str("133.224.177.174/8");
    bool j =new_ip.set_value(test_str);
    String packet_1("src-ip=133.145.84.201, dst-ip=189.112.138.228, src-port=53, dst-port=12106");
    bool is_ok= new_ip.match(packet_1);



    return 0;
}
