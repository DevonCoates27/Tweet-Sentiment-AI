//
// Created by Devon Coates on 9/29/22.
//

#include "TokenString.h"
#include "DSString.h"
#include <iostream>

using namespace std;

int test(){
    // constructor tests
    cout << "Testing Default Constructor: ";
    DSString test1;
    cout << "Done\n" << endl;

    cout << "Testing Cstring Constructor: ";
    DSString test2 = "word";
    cout << "Done\n" << endl;

    cout << "Testing Copy Constructor: ";
    DSString test3(test2);
    cout << "Done\n" << endl;

    cout << "Testing Cstring assignment operator: ";
    test2 = "word two";
    cout << "Done\n" << endl;

    cout << "Testing cout function: " << endl;
    cout << test2 << endl;
    cout << "Done\n" << endl;

    cout << "Testing addition operator: ";
    test2 = "one";
    test3 = "two";
    test1 = test2 + test3;
    cout << test1 << endl;
    cout << "Done\n" << endl;

    cout << "Testing comparison operator: ";
    test2 = "word";
    test3 = "word";
    if(test2 == test3){
        cout << "Pass" << endl;
    } else{
        cout << "Fail" << endl;
    }
    cout << "Done\n" << endl;

    cout << "Testing substring function: ";
    test1 = test2.substring(1,3);
    cout << test1 << endl;
    cout << "Done\n" << endl;

    cout << "Testing TokenString default constructor: " << endl;
    TokenString token1;
    cout << "Done\n" << endl;

    cout << "Testing TokenString overloaded constructor: " << endl;
    TokenString token2(-5, 1,  DSString("bomb"));
    cout << "Done\n" << endl;

    cout << "Testing TokenString assignment operator: " << endl;
    token1 = token2;
    cout << "Done\n" << endl;

    cout << "Testing TokenString comparison operator: " << endl;
    if(token1 == token2){
        cout << "PASS" << endl;
    } else
        cout << "FAIL" << endl;
    cout << "Done\n" << endl;

//    TokenString test1(1, 0, "bomb");
//    TokenString test2(1, 0, "bomb2");
//    test1.addSentiment(test2);
//    cout << test1.getWord() << ": " << test1.getSentiment() << endl;

    return 0;
}
