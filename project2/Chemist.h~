//Title: Chemist.h
//Author: Jeremy Dixon
//Date: 2/25/2022
//Description: This is part of the project 2 in CMSC 202 @ UMBC
// This is the non-pointer version header files

#ifndef CHEMIST_H //Include/Header Guard
#define CHEMIST_H //Include/Header Guard

#include "Substance.h" //Include for the material struct
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

//Constants
const int PROJ2_SIZE = 283;

// class - do not add any functions to project 2
class Chemist{
 public:
  // Name: Chemist() - Default Constructor
  // Desc: Used to build a new Chemist
  // Preconditions - Requires default values
  // Postconditions - Creates a new Chemist (with a default name of "Beaker" and
  //      m_numSubstances = 0
  Chemist();
  // Name: Chemist(name) - Overloaded constructor
  // Desc - Used to build a new Chemist
  // Preconditions - Requires name
  // Postconditions - Creates a new Chemist (with passed name and m_numSubstance = 0)
  Chemist(string name);
  // Name: GetName()
  // Desc - Getter for Chemist name
  // Preconditions - Chemist exists
  // Postconditions - Returns the name of the Chemist
  string GetName();
  // Name: SetName(string)
  // Desc - Allows the user to change the name of the Chemist
  // Preconditions - Chemist exists
  // Postconditions - Sets name of Chemist
  // May not be used in the project explicitly but please impelement
  void SetName(string name);
  // Name: CheckSubstance(Substance)
  // Desc - Checks to see if the Chemist has a substance if so, returns
  //        the index where it exists, if not returns -1
  // Preconditions - Chemist already has substance
  // Postconditions - Returns index of substance if Chemist has it else -1
  int CheckSubstance(Substance);
  // Name: AddSubstance(string)
  // Desc - Inserts a material into the Chemist's list of substances. Has
  //        to see if it exists in m_mySubstances first to find location.
  //        Then adds substance and increments m_numSubstances
  // Preconditions - Chemist exists
  // Postconditions - Add a substances to the Chemist's m_mySubstances with a quantity of 0
  void AddSubstance(Substance);
  // Name: IncrementQuantity(Substance)
  // Desc - Adds quantity to list of substances the chemist knows.
  //        Has to find location in array first. Then increments quantity
  // Preconditions - Chemist exists
  // Postconditions - Increases quantity of material for chemist
  void IncrementQuantity(Substance);
  // Name: DecrementQuantity(Substance)
  // Desc - Reduces quantity from chemist's inventory with true, if no quantity false
  // Preconditions - Chemist exists
  // Postconditions - Reduces quantity of substance for chemist
  bool DecrementQuantity(Substance);
  // Name: CheckQuantity(Substance)
  // Desc - Checks to see if quantity of two merge substances is greater than one.
  //        if the quantity of substance 1 is greater than one and the
  //        quantity of substance two is greater than one, returns true else false
  // Preconditions - Chemist exists with substances
  // Postconditions - Returns true if both are available
  bool CheckQuantity(Substance, Substance);
  // Name: GetSubstance(int)
  // Desc - Returns a substance at at specific index
  // Preconditions - Chemist already has substances
  // Postconditions - Returns substance at specific index
  Substance GetSubstance(int);
  // Name: GetTotalSubstances
  // Desc - Iterates over m_mySubstances and counts each substance with a quantity higher than 0
  // Preconditions - Chemist may have no substances
  // Postconditions - Returns number of substances with a quantity greater than 0
  int GetTotalSubstances();
 private:
  string m_myName; //Name of Chemist
  Substance m_mySubstances[PROJ2_SIZE] = {}; //List of substances known to this chemist
  int m_numSubstances; //Total number of substances
};

#endif //Exit Header Guard
