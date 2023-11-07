//
// Created by Devon Coates on 9/26/22.
//

#include "TokenString.h"
#include <string.h>
#include <stdexcept>
#include "DSString.h"
using namespace std;

    TokenString::TokenString(){
        ID = 0;
        sentiment = 0;
    }

    // Constructor with parameters
    TokenString::TokenString(int sent, int occur, DSString input){
        sentiment = sent;
        ID = occur;
        word = input;
    }

    // Copy constructor
    TokenString::TokenString(const TokenString &input){
        sentiment = input.sentiment;
        ID = input.ID;
        word = input.word;
    }

    // Destructor
    TokenString::~TokenString(){
        ID = 0;
        sentiment = 0;
    }

    // Assignment operator
    TokenString &TokenString::operator=(const TokenString &rhs){
        if(this != &rhs){
            ID = rhs.ID;
            sentiment = rhs.sentiment;
            word = rhs.word;
        }
        return *this;
    }

    bool TokenString::operator==(const TokenString &rhs){
        return (ID == rhs.ID && sentiment == rhs.sentiment && word == rhs.word);
    }

    bool TokenString::operator!=(const TokenString &rhs){
        return !(ID == rhs.ID && sentiment == rhs.sentiment && word == rhs.word);
    }

