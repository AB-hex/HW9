
#include "string.h"
#include "iostream"
#include <cstring>
#include <stdio.h>
#include "math.h"



using namespace std;
/**
 * default constructor
*/

String::String():data(nullptr),length(0) {

}
/**
 * destrucotor
*/
String::~String(){
    delete[] this->data;
}
/**
 * copy constructor from another String
 * param str the copied object
*/
String::String(const String &str) {
    if( ( str.length==0 )||( str.data == nullptr) ){
        return;
    }
    this->length=str.length;
    this->data = new char[strlen(str.data)+1];
    this->data=strcpy(this->data,str.data);


}
/**
 * Copy constructor from another char*
 * param str the string that we insert to our object
*/
String::String(const char *str) {
    if((strlen(str)==0)||(str== nullptr)){
        return;
    }
    this->length=strlen(str);
    data = new char[strlen(str)+1];
   this->data=strcpy(data,str);


}
/**
 * assignment operator
 * param str char* that inserted
 
*/
String& String::operator=(const char *str) {
    if((strlen(str)==0)||(str== nullptr)){
        return *this;
    }
    delete [] this->data;
    this->length=strlen(str);
    this->data = new char[strlen(str)+1];
    this->data=strcpy(this->data,str);
   
    return *this;

}
/**
 * assignment operator
 * param str String that inserted
 
*/
String& String::operator=(const String &rhs) {
    if(this==&rhs){
        return *this;
    }
    if((rhs.length==0)||(rhs.data== nullptr)){
        return *this;
    }
    if(length>0) {
        delete[] this->data;
    }
    this->length=rhs.length;
    int len= length+1;

    char *str=new char[len];
    str = strcpy(str,rhs.data);
    this->data=str;

    return *this;

}
/**
*/

bool String::equals(const String &rhs) const {
    // if(&rhs == NULL){
    //     return false;
    // }
    int result = strcmp(rhs.data,this->data);
    if(result==0){
        return true;
    }
    return false;
}

bool String::equals(const char *rhs) const {
    if(rhs== nullptr){
        return false;
    }
    if(strlen(rhs)!=this->length){
        return false;
    }
    if(strcmp(rhs,this->data)==0){
        return true;
    }
    return false;
}

void String::split(const char *delimiters, String **output,
                   size_t *size) const {

    if((delimiters== nullptr)||(output== nullptr)||(size== nullptr)){
        *size = 2;
        return;
    }
    /*calculate the how many times the sign appears*/
    size_t counter=0;


    // char *copied_data = new char[this->length+1];
    // copied_data = strcpy(copied_data,this->data);
    /*
    for(int i=0;i<this->length;i++){
        copied_data[i]=this->data[i];
    }
    */
    bool is_delimiter[this->length];
    for(int i=0;i < (int)this->length;i++){
        is_delimiter[i]= false;
    }

    /*sign in which indexes are delimiter*/
    for(int i=0;i<(int)this->length;i++){
        for(int j =0;j<(int)strlen(delimiters);j++){
            if(this->data[i]==delimiters[j]){

                is_delimiter[i]= true;
            }

        }
    }



    //count the num of strings
    for(int i=1;i< (int)this->length ; i++){
        if((is_delimiter[i]== true)&&(is_delimiter[i-1]== false)){
            counter++;
        }
    }

    if(is_delimiter[this->length-1]== false){
        counter++;
    }


    String *new_out = new String[counter];
    //*output =new String[counter];
    *size = counter;
    /*
   for(int i=0;i<counter;i++){

       *(new_out+i) =  String();

    }
     */
  *output=new_out;



    /*array 2D, the 1sr coulum in the initial index, 2nd is the end*/
    int** strings_locations = new int*[counter];
    for(int i=0;i<(int)counter;i++){
        strings_locations[i]=new int[2];
    }

    //find the inits of the strings
  //  if(is_delimiter[0]== false)
    if(is_delimiter[0]== false){
        strings_locations[0][0]=0;
        int loc_index=1;
        for(int i=1;i<(int)this->length;i++){
            if((is_delimiter[i]==false)&&(is_delimiter[i-1]== true)){
                strings_locations[loc_index][0]=i;
                loc_index++;
            }
        }
    }
    else{
        int loc_index=0;
        for(int i=1;i<(int)this->length;i++){
            if((is_delimiter[i]== false)&&(is_delimiter[i-1]== true)){
                strings_locations[loc_index][0]=i;
                loc_index++;
            }
        }

        }
        //find the ends of the strings

        int loc_index=0;
        for(int i=0;i<(int)length-1;i++){
           if((is_delimiter[i]== false)&&(is_delimiter[i+1]== true)){
               strings_locations[loc_index][1]=i;
               loc_index++;
           }
        }
        //check the last char, if smaller it means we missed the last char
        if(loc_index<(int)counter){
            strings_locations[counter-1][1]=length-1;
        }



    /*create all other strings expect the last one*/
    for(int i=0;i<(int)counter;i++){
        int word_len=strings_locations[i][1]-strings_locations[i][0]+1;
        char tmp_string [word_len+1];
        int j=strings_locations[i][0];
        for(;j<=strings_locations[i][1];j++){
            tmp_string[j-strings_locations[i][0]]=this->data[j];
        }
        tmp_string[j-strings_locations[i][0]]='\0';
        //tmp_string[word_len]= (char) '/0';
        String tmp(tmp_string);
        (*output)[i]=tmp;
    }
    for(int i=0; i< (int)counter ; i++){

    delete[] strings_locations[i]; 

    }

    delete[] strings_locations; 


}

int String::to_integer() const {
    unsigned integer =0;
    size_t strings_num=0;
    String* output;
    split(".",&output,&strings_num);



    for(int i=0; i < (int)strings_num ; i++ ){
        output[i] = output[i].trim();
        unsigned temp = (unsigned )stoi(output[i].data);
        integer += temp<<(8*(strings_num - i - 1));

    }
    delete[] output;
    return integer;
}











String String::trim() const {
    if((this->data==NULL)||(this->length==0)){
        return *this;
    }



    //find the indexes where the string should begin\finish
    int init_char=0;
    int last_char= this->length-1;
    bool found= false;
    for(int i=0;(i<(int)this->length)&&(found==false);i++) {
        if (this->data[i] != ' ') {
            init_char = i;
            found = true;

        }
    }
    found=false;
        for(int i=this->length-1;(i>=0)&&(found==false);i--){
            if(this->data[i]!=' '){
                last_char=i;
                found= true;
            }

    }
        //in case there are no space
        if((init_char==0)&&(last_char==(int)length-1)){
        return *this;
        }
        //in case it is all spaces

        int new_len = last_char-init_char+1;
        char new_string[new_len+1];
        strncpy(new_string,data+init_char,last_char-init_char+1);
       // insert without the string

        return String(new_string);




    }






