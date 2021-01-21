//
// Created by איתן on 1/18/2021.
//
#include "string.h"
#include "iostream"
#include <cstring>
#include <stdio.h>
#define NUM_IP_SEC 4
#include "math.h"
#define MAX_SIZE 255


using namespace std;

String::String():data(nullptr),length(0) {

}
String::~String(){
    delete[] this->data;
}

String::String(const String &str) {
    if((str.length==0)||(str.data== nullptr)){
        return;
    }
    this->length=str.length;
    char *new_data = new char[strlen(str.data)+1];
    for(int i=0;i<str.length;i++){
        new_data[i]=str.data[i];
    }
    this->data=new_data;


}

String::String(const char *str) {
    if((strlen(str)==0)||(str== nullptr)){
        return;
    }
    this->length=strlen(str);
    char *new_data = new char[strlen(str)+1];
    for(int i=0;i<strlen(str)+1;i++){
        new_data[i]=str[i];
    }
    this->data=new_data;

}

String& String::operator=(const char *str) {
    if((strlen(str)==0)||(str== nullptr)){
        return *this;
    }
    delete [] this->data;
    this->length=strlen(str);
    char *new_data = new char[strlen(str)+1];
    for(int i=0;i<strlen(str);i++){
        new_data[i]=str[i];
    }
    this->data=new_data;
    return *this;

}

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

bool String::equals(const String &rhs) const {
    if(&rhs == NULL){
        return false;
    }
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
        return;
    }
    /*calculate the how many times the sign appears*/
    size_t counter=0;
    int last_index=0;

    char *copied_data = new char[this->length+1];
    for(int i=0;i<this->length;i++){
        copied_data[i]=this->data[i];
    }
    /*insert "." to simplify the task*/
    for(int i=0;i<this->length;i++){
        for(int j =0;j<strlen(delimiters);j++){
            if(this->data[i]==delimiters[j]){
                last_index=i;
                copied_data[i]='.';
            }

        }
    }



    //count the num of strings
    for(int i=1;i<this->length;i++){
        if((copied_data[i]=='.')&&(copied_data[i-1]!='.')){
            counter++;
        }
    }

    if(copied_data[this->length-1]!='.'){
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
    for(int i=0;i<counter;i++){
        strings_locations[i]=new int[2];
    }

    //find the inits of the strings
    if(copied_data[0]!='.'){
        strings_locations[0][0]=0;
        int loc_index=1;
        for(int i=1;i<this->length;i++){
            if((copied_data[i]!='.')&&(copied_data[i-1]=='.')){
                strings_locations[loc_index][0]=i;
                loc_index++;
            }
        }
    }
    else{
        int loc_index=0;
        for(int i=1;i<this->length;i++){
            if((copied_data[i]!='.')&&(copied_data[i-1]=='.')){
                strings_locations[loc_index][0]=i;
                loc_index++;
            }
        }

        }
        //find the ends of the strings

        int loc_index=0;
        for(int i=0;i<length-1;i++){
           if((copied_data[i]!='.')&&(copied_data[i+1]=='.')){
               strings_locations[loc_index][1]=i;
               loc_index++;
           }
        }
        //check the last char, if smaller it means we missed the last char
        if(loc_index<length-1){
            strings_locations[counter-1][1]=length-1;
        }



    /*create all other strings expect the last one*/
    for(int i=0;i<counter;i++){
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



}

int String::to_integer() const {
    int outcome =0;
    size_t strings_num=0;
    String* output;
    split(".",&output,&strings_num);
    if(strings_num==NUM_IP_SEC){

        int addition=0;

        for(int i=0; i<strings_num;i++){
            output[i].trim();
            for(int j=0;j<output[i].length;j++){
                addition+=output[i].data[j]*pow(10,output[i].length);
            }
            outcome|=addition<<(24-8*i);
        }
        delete[] output;
        return outcome;
    }




    delete [] output;
    return 0;

}

String String::trim() const {
    if((this->data==NULL)||(this->length==0)){
        return *this;
    }
    /*find the indexes where the string should begin\finish */
    int init_char=0;
    int last_char= this->length-1;
    bool found= false;
    for(int i=0;(i<this->length)&&(found==false);i++) {
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

        /*in case that not change is needed*/
        if(init_char>last_char){
        return *this;
        }
        int new_len = last_char-init_char+1;
        char new_string[new_len+1];

        /*insert without the string*/
        for(int i=init_char;i<=last_char;i++){
            new_string[i-init_char]=data[i];
        }
        return String(new_string);




    }






