/*****************************************************************************
 ** File: proj5.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Kush Shah and CMSC202
 ** Date:    04/05/2022
 ** Email:   k216@umbc.edu
 **
 Description: CPP file for main. Calls Trivia's start function. 
*****************************************************************************/

// Include basic io functions, strings, and the trivia class
#include <iostream>
#include <string>
#include "Trivia.cpp"
#include "Lqueue.cpp"

using namespace std;

// Global constant for maximum subjects
int main(int argc, char**argv) {
  const int EXPECTED_ARGS = 3;
  const int FILENAME = 1;
  const int DATATYPE = 2;
  string filename = DEFAULT_FILE;
  string datatype = argv[DATATYPE];

  //Usage ./proj5 [FILENAME] [DATATYPE]
  if (argc == EXPECTED_ARGS) { //Compares count of arguments vs EXPECTED_ARGS
    filename = argv[FILENAME]; //Pull filename from arguments
    if (datatype == "int") { //If datatype = "int" creates a new trivia object (int)
      Trivia<int>* newTrivia = new Trivia<int>(argv[FILENAME]);
      delete newTrivia;
    }
    else if (datatype == "double") {
      Trivia<double>* newTrivia = new Trivia<double>(argv[FILENAME]);
      delete newTrivia;
    }
    else if (datatype == "string") {
      Trivia<string>* newTrivia = new Trivia<string>(argv[FILENAME]);
      delete newTrivia;
    }else{
      cout << "Invalid data type" << endl;
    }
  }
  else {
    cout << "ERROR: Expected usage is ./proj5 [FILENAME] [DATATYPE]" << endl;
    return -1;
  }
  return 0;
}
