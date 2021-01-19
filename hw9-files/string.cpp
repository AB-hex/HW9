//
// Created by user on 1/19/2021.
//


/* Includes */
#include "string.h"
#include <iostream>
#include <cstring>
#include "ip.h"

/* Namespace */
using namespace std;




































/* Default Const. */
String::String()
{
    data = NULL;
    length = 0;
}








/* Const. */
String::String(const char *str)
{
    /* Check Arg */
    if (NULL == str)
    {
        length = 0;
        data = NULL;
        return;
    }

    length = strlen(str);
    data = new char[length + 1];

    if (NULL != data)
    {
        strncpy(data, str, length + 1);
    }
    else
    {
        length = 0;
        data = NULL;
    }
}








/* Copy Const. */
String::String(const String &str)
{
    // Modify according to str
    length = str.length;

    if (0 == length)
    {
        data = NULL;
    }
    else
    {
        data = new char[length + 1];
        if (NULL != data)
        {
            strncpy(data, str.data, length + 1);
        }
    }
}







String::~String()
{
    if (NULL != data)
    {
        delete[] data;
    }
}









String& String::operator=(const String &rhs)
{
    // Free Old string
    if (NULL != data)
    {
        delete[] data;
    }


    // Modify According to rhs
    length = rhs.length;

    if (0 == length)
    {
        data = NULL;
    }
    else
    {
        data = new char[length + 1];
        if (NULL != data)
        {
            strncpy(data, rhs.data, length + 1);
        }
    }

    return *this;
}





String& String::operator=(const char *str)
{
    /* Check Arg */
    if (NULL == str)
    {
        length = 0;
        data = NULL;
        return *this;
    }

    // Free Old string
    if (NULL != data)
    {
        delete[] data;
    }

    // Modify According to str
    length = strlen(str);

    data = new char[length + 1];
    if (NULL != data)
    {
        strncpy(data, str, length + 1);
    }
    else
    {
        length = 0;
        data = NULL;
    }

    return *this;
}






bool String::equals(const String &rhs) const
{
    if(length != rhs.length)
    {
        return false;
    }

    if (0 != strncmp(data, rhs.data, length))
    {
        return false;
    }

    return true;
}



bool String::equals(const char *rhs) const
{
    /* Check Arg */
    if (NULL == rhs)
    {
        return false;
    }

    if (length != strlen(rhs))
    {
        return false;
    }

    if (0 != strncmp(data, rhs, length))
    {
        return false;
    }

    return true;
}








void String::split(const char *delimiters, String **output, size_t *size) const
{
    int start = 0, substr = 0;
    unsigned int i = 0 , delimiter = 0 , numDelimiters = 0 , numSubstrings = 1; //at least 1 substring - the Whole string
    char dataCopy[length + 1] = {0};


    //Ask TA what to do here!!
    if (NULL == delimiters || NULL == output || NULL == size || NULL == data)
    {
        //Ask TA what to do here!!
        if (NULL != size)
        {
            *size=0;
        }
        return;
    }


    /* copy original string and change it */
    strncpy(dataCopy, data, length);
    dataCopy[length] = '\0';



    //count number of substrings = how many chars are equal to delimiter
    numDelimiters = strlen(delimiters);
    for (i = 0; i < length; i++)
    {
        for (delimiter = 0; delimiter < numDelimiters; delimiter++)
        {
            if (dataCopy[i] == delimiters[delimiter])
            {
                numSubstrings++;
            }
        }
    }


    /* Update size */
    *size = numSubstrings;

    //allocate substrings
    *output = new String[numSubstrings];

    /* datacopy: Aasdasd=aaaaa,bbb=ccc   , delimiters: =,

                Aasdasd'\0'aaaaa'\0'bbb'\0'ccc
                output[0]="Aasdasd"
                output[1]="aaaaa"
                output[2]="bbb"
                output[3]="ccc"
    */

    //copy each substring to output
    for (i = 0; i < length; i++)
    {
        for (delimiter = 0; delimiter < numDelimiters; delimiter++)
        {
            if (dataCopy[i] == delimiters[delimiter])
            {
                dataCopy[i] = '\0';
                (*output)[substr] = String(&dataCopy[start]);
                start = i + 1;
                substr++;
            }
        }
    }

    //set the last substring
    (*output)[substr] = String(&dataCopy[start]);

    return;
}


/* Remove Spaces */
String String::trim() const
{
    int start = 0 , end = length - 1;

    if (NULL == data)
    {
        return String();
    }

    while (data[start] == ' ')
    {
        start++;
    }

    while( (data[end] == ' ') && (start != end) )
    {
        end--;
    }

    end++;

    if (start >= end)
    {
        return String();
    }

    char newData[end - start + 1];
    strncpy(newData, &data[start], end - start);
    newData[end - start] = '\0';

    return String(newData);
}



/*  convert ip address/port to integer.
TA: what if string.data=NULL? what if string.data="yoav"? (not ip, not number). atoi will fail and return 0. see (2) below.
*/
int String::to_integer() const
{

    int ret = 0;
    String* substrs = NULL;
    size_t size = 0;
    unsigned int i = 0;


/* Two options:
	1. string represents ip address
	2. string represents a number
*/

    /* Check which option: splits data according to delimeter . */
    split(".", &substrs, &size);


    /* 1) size = 4. Its an IP Address. */

    /*	12.3.5.7
        12  3  5  7
        12 = 0xC	-> 	0x0C000000
        3 = 0x3 	->	0x00030000
        5 = 0x5 	-> 	0x00000500
        7 = 0x7 	-> 	0x00000007
        12.3.5.7	->	0x0C030507
    */

    if(SEGMENTS == size)
    {
        //trim each substring and build full integer
        for(i = 0; i < size; i++){
            int byte = substrs[i].trim().to_integer();
            //if substring is > 255 - the address is not valid
            if ( (byte > 255) || (byte<0) )
            {
                delete[] substrs;
                return 0;  // return 0 or -1?
            }

            ret |= byte << (24 - (8 * i));
        }

        delete[] substrs;
        return ret;
    }

        /* 2. Parse as integer.  problem: return 0 for error and for 0 */
    else
    {
        ret = atoi(data);
        if(0 != ret)
        {
            delete[] substrs;
            return ret;
        }
    }

    delete[] substrs;

    return 0;
}

