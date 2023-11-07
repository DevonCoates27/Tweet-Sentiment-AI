#include <iostream>
#include <algorithm>

#include "DSString.h"
#include "TokenString.h"
#include "Model.h"
#include "test.h"

using namespace std;

int main(int argc){
    if(argc == 1){
        return test();
    } else{
        Model *myModel = new Model();

        myModel->train("data/output.csv");

        myModel->predict("data/train_dataset_20k.csv");
        myModel->evaluatePredictions("data/test_dataset_sentiment_10k.csv", "data/test_dataset_sentiment_10k.csv", "data/test_dataset_sentiment_10k.csv");

    }
    return 0;
}
