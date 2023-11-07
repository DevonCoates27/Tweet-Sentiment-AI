//
// Created by Devon Coates on 9/26/22.
//

#ifndef ASSIGNMENT2_SENTIMENT_TOKENSTRING_H
#define ASSIGNMENT2_SENTIMENT_TOKENSTRING_H

#include <iostream>
#include "DSString.h"

class TokenString{
private:
    int sentiment = 0;
    int ID = 0;
    DSString word;

public:
    // Constructors
    TokenString();
    TokenString(int sentiment, int ID, DSString input);

    // Rule of three
    TokenString(const TokenString &);
    ~TokenString();
    TokenString &operator=(const TokenString &);
//    TokenString &operator=(const char *);

    // comparison operators
    bool operator==(const TokenString &);
    bool operator!=(const TokenString &);

    // Addition operator
    void addSentiment(const TokenString &input){
        sentiment += input.sentiment;
    }



    // Getters and setters
    void setSentiment(int sent){ sentiment = sent; }
    void setOccurances(int occur){ ID = occur; }
    int getSentiment(){ return sentiment; }
    int getOccurances(){ return ID; }
    DSString getWord(){ return word; }

};


#endif //ASSIGNMENT2_SENTIMENT_TOKENSTRING_H
