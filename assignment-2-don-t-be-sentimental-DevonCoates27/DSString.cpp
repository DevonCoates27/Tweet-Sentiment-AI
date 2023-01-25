//
// Created by Devon Coates on 9/9/22.
//

#include "DSString.h"
#include <string.h>
#include <stdexcept>
using namespace std;

// Default constructor
DSString::DSString(){
    len = 1;
    data = new char[len];
    data[0] = '\0';
}

DSString::DSString(const char* input){
    len = (strlen(input) + 1);
    data = new char[len];
    for(int i = 0; i < len-1; ++i){
        data[i] = input[i];
    }
    data[len-1] = '\0';
}

// copy constructor
DSString::DSString(const DSString &rhs){
    len = rhs.getLen();
    data = new char[len];
    strcpy(data, rhs.data);
}

// destructor
DSString::~DSString(){
    len = 0;
    delete[] data;
}

// assignment operator using DSString&
DSString &DSString::operator=(const DSString &rhs){
    if(this != &rhs){
        if(this->data != nullptr){
            delete[] data;
        }
        len = rhs.len;
        data = new char[rhs.len + 1];
        strcpy(data, rhs.data);
    }
    return *this;
}

// assignment operator using cstring
DSString &DSString::operator=(const char *rhs){
    if(this->data != rhs) {
        if (this->data != nullptr) {
            delete[] data;
        }
        len = strlen(rhs) + 1;
        data = new char[len];
        strcpy(data, rhs);
    }
    return *this;
}

// cout function
std::ostream &operator<<(std::ostream &out, const DSString &x){
    for(int i = 0; i < x.getLen()-1; ++i){
        out << x.data[i];
    }

    return out;
}

// addition operator
DSString DSString::operator+(const DSString &rhs) {
    DSString temp;
    delete[] temp.data;
    temp.len = (len-1) + (rhs.getLen()-1) + 1;
    temp.data = new char[temp.getLen()];
    for(int i = 0; i < len - 1; ++i){
        temp.data[i] = data[i];
    }
    for(int i = len - 1; i < temp.getLen() - 1; ++i){
        temp.data[i] = rhs.data[i - (rhs.getLen() - 1)];
    }
    temp.data[temp.getLen() -1] = '\0';

    return temp;
}

// comparison operator
bool DSString::operator==(const DSString &rhs){
    return strcmp(data, rhs.data)==0;
}

// equals operator
bool DSString::operator==(const DSString rhs) const{
    if (len != rhs.getLen())
        return false;

    for (size_t i = 0; i < (size_t)len; ++i)
        if (data[i] != rhs.data[i])
            return false;

    return true;
}

// comparison operator
bool DSString::operator!=(const DSString &rhs){
    return strcmp(data, rhs.data)!=0;
}

// equals operator
bool DSString::operator!=(const DSString rhs) const{
    if (len != rhs.getLen())
        return true;

    for (size_t i = 0; i < (size_t)len; ++i)
        if (data[i] != rhs.data[i])
            return true;

    return false;
}

// substring function
DSString DSString::substring(size_t start, size_t numChars) const {
    //       12345
    //data = word\0
    //       01234
    //start = 1
    //numChars = 3
    if(start + numChars > (size_t)len-1){
        throw std::runtime_error("out of bounds!");
    }
    DSString temp;
    temp.len = numChars + 1;
    delete[] temp.data;
    temp.data = new char[numChars+1];
    for (size_t i = 0; i < numChars; i++)
    {
        temp.data[i] = data[(start + i)];
    }
    temp.data[numChars] = '\0';
    return temp;
}

// c_str returner
const char *DSString::c_str() const{
    return data;
}

// cast to lower
void DSString::lower(){
    for(int i = 0; i < len; i++){
        if(data[i] >= 65 && data[i] <= 90){
            data[i] += 32;
        }
    }
}