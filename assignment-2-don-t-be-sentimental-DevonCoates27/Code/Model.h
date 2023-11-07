//
// Created by Devon Coates on 9/29/22.
//

#ifndef ASSIGNMENT2_SENTIMENT_MODEL_H
#define ASSIGNMENT2_SENTIMENT_MODEL_H

#include <iostream>
#include "TokenString.h"
#include "DSString.h"
#include "DSVector.h"


class Model {
private:
    DSVector<TokenString> tokens;
    DSVector<TokenString> predictedTweets;

public:
    Model();
    void train(char*);
    void predict(char*);
    void evaluatePredictions(char*, char*, char*);
    ~Model();
};


#endif //ASSIGNMENT2_SENTIMENT_MODEL_H
