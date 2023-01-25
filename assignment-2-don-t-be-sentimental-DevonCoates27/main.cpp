#include <iostream>
#include <algorithm>

#include "DSString.h"
#include "TokenString.h"
#include "Model.h"
#include "test.h"

using namespace std;

int main(int argc, char** argv){
    if(argc == 1){
        return test();
    } else{
        Model *myModel = new Model();
        
        myModel->train(argv[1]);

        myModel->predict(argv[2]);
        myModel->evaluatePredictions(argv[3], argv[4], argv[5]);

    }
    return 0;

return 0;
}
