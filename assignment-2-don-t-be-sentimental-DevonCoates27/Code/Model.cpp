//
// Created by Devon Coates on 9/29/22.
//

#include "Model.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

Model::Model(){
}

void Model::train(char* filename){
    ifstream inFile(filename);
    if(inFile.is_open()){
//        TokenString *token = new TokenString();
        char* buffer = new char[600];
        inFile.getline(buffer, 600, '\n');
        char* tweetString;
        char* sent;
        char* id;
        DSString tempTweet;
        int count = 0;
        cout << "\n\nTRAINING:" << endl;

        // Reading the File
        while(inFile.good()) {
            // Manage Memory
            tweetString = new char[300];
            sent = new char[2];
            id = new char[11];

            // Read sentiment and ID
            inFile.getline(sent, 2, ',');
            inFile.getline(id, 11, ',');

            // Discard information
            for(int k = 0; k < 3; k++) {
                inFile.getline(buffer, 600, ',');
            }

            // Retrieve the tweet
            inFile.getline(tweetString, 300, '\n');

            // Tokenize the tweet
            char* word = strtok(tweetString, " .~!@#$%^&*()_+`1234567890-=:;{[}]|\\<,>.?/\"");
            while(word != NULL){
                // Save individual word as DSString
                DSString DSWord(word);
                DSWord.lower();

                // Save individual word as TokenString
                if(DSWord.getLen() > 2){
                    // Create token of the word
                    TokenString temptok(atoi(sent) == 4?1:(-1), 0, DSWord);

                    // Iterate through the vector to see if the word already exists
                    bool exis = false;
                    for (int i = 0; i < (int)tokens.size(); i++) {
                        if(temptok.getWord() == tokens[i].getWord()){
                            exis = true;
                            tokens[i].setOccurances(tokens[i].getOccurances()+1);
                            tokens[i].setSentiment(tokens[i].getSentiment()+temptok.getSentiment());
                            if (i != 0)
                                swap(tokens[i], tokens[i - 1]);
                            break;
                        }
                    }
                    if(!exis)
                        tokens.push_back(temptok);
                }
                // Output percentage of training


                // Get next word
                word = strtok(NULL, " .~!@#$%^&*()_+`1234567890-=:;{[}]|\\<,>.?/\"");
            }
            if((count++ % 200) == 0){
                cout << "Program percentage: " << ((int)count/100)/2 << "%" << endl;
            }
        }
    }
//    for (int i = 0; i < tokens.size(); ++i) {
//        tokens[i].setSentiment(tokens[i].getSentiment()/(tokens.size()-i));
//    }

    inFile.close();
}

// Predict function
void Model::predict(char *testData) {
    ifstream inFile(testData);
    if(inFile.is_open()){
        // Create Variables
        char* buffer = new char[600];
        inFile.getline(buffer, 600, '\n');
        cout << buffer << endl;
        char* tweetString;
        char* id;
        int tweetSent;
        DSString tempTweet;
        int count = 0;
        cout << "\n\nPREDICTING: " << endl;

        while(inFile.good()){
            // Manage Memory
            tweetString = new char[300];
            id = new char[11];
            tweetSent = 0;

            // Read ID
            inFile.getline(id, 11, ',');

            // Discard information
            for(int k = 0; k < 3; k++) {
                inFile.getline(buffer, 600, ',');
            }

            // Retrieve the tweet
            inFile.getline(tweetString, 300, '\n');

            // Tokenize the tweet
            char* word = strtok(tweetString, " .~!@#$%^&*()_+`1234567890-=:;{[}]|\\<,>.?/\"");
            while(word != NULL){
                // Save individual word as DSString
                DSString DSWord(word);
                DSWord.lower();

                // Save individual word as TokenString
                if(DSWord.getLen() > 2){
                    // Create token of the word
                    TokenString temptok(0, 0, DSWord);

                    // Iterate through the vector to find sentiment
                    for(size_t j = 0; j < tokens.size(); j++){
                        if(temptok.getWord() == tokens[j].getWord()){
                            temptok.addSentiment(tokens[j]);
                            break;
                        }
                    }
                    tweetSent += temptok.getSentiment();
                }

                // Get next word
                word = strtok(NULL, " .~!@#$%^&*()_+`1234567890-=:;{[}]|\\<,>.?/\"");
            }
            TokenString predictTok(tweetSent >= 1?4:0, atoi(id), "");
            predictedTweets.push_back(predictTok);
            if((count++ % 100) == 0){
                cout << "Program percentage: " << (int)count/100 << "%" << endl;
            }
        }
    }
    inFile.close();
}

// Evaluate Predictions
void Model::evaluatePredictions(char* sentimentData, char* OutFile, char* falsePredictions) {
    ifstream inFile(sentimentData);
    char *buffer = new char[600];
    inFile.getline(buffer, 600, '\n');
    cout << buffer << endl;
    char *sent = new char[1];
    int intSent;
    int counter = 0;
    int correct = 0;
    int incorrect = 0;
    DSVector<TokenString> incorrectTweets;
    while (inFile.good()) {
        inFile.getline(sent, 2, ',');
        intSent = atoi(sent);
        inFile.getline(buffer, 11, '\n');
        if (intSent == predictedTweets[counter].getSentiment()) {
            correct++;
        } else {
            incorrect++;
            TokenString incorrectTweet(predictedTweets[counter].getSentiment(), intSent, buffer);
            if(incorrectTweet.getSentiment() != incorrectTweet.getOccurances()) {
                incorrectTweets.push_back(incorrectTweet);
            }
        }
        counter++;
    }

    double accuracy = (correct * 100.0) / (correct + incorrect);
    cout << "FINAL ACCURACY: " << accuracy << "%";

    // Output to inaccuracyOutput.csv
    ofstream incorrectFile(falsePredictions);
    incorrectFile << accuracy << endl;
    if(incorrectFile.is_open()){
        for(int i = 0; i < incorrectTweets.size(); i++){
            incorrectFile << incorrectTweets[i].getSentiment() << ", " << incorrectTweets[i].getOccurances() << ", " << incorrectTweets[i].getWord() << endl;
        }
    }

    // Output to output.csv
    ofstream outFile(OutFile);
    if(outFile.is_open()){
        for(int i = 0; i < predictedTweets.size(); i++){
            outFile << predictedTweets[i].getSentiment() << ", " << abs(predictedTweets[i].getOccurances()) << endl;
        }
    } else
        cout << "\n\nFILE NOT OPEN" << endl;


    inFile.close();
    outFile.close();
}


Model::~Model() = default;
