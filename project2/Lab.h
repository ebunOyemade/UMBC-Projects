//Title: Lab.h
//Author: Jeremy Dixon
//Date: 2/25/2022
//Description: This is part of the project 2 in CMSC 202 @ UMBC

#ifndef GAME_H //Header Guard
#define GAME_H //Header Guard
#include <fstream>
#include "Substance.h"
#include "Chemist.h"

//Constants (additional constants allowed)
const string PROJ2_DATA = "proj2_data.txt"; //File constant
const int START_ELEMENTS = 100; //For testing
//No additional functions allowed

class Lab{
public:
  // Name: Lab() Default Constructor
  // Desc - Instantiates an object of type Lab
  // Preconditions - None
  // Postconditions - None
  Lab(); //Default Constructor
  // Name: LoadSubstances
  // Desc - Loads each substance into m_substances from file
  //        The loads all substances from m_substances into m_myChemist's substance array
  // Preconditions - Requires file with valid substance data
  // Postconditions - m_substance is populated with substance structs
  void LoadSubstances();
  // Name: StartLab()
  // 1. Displays Lab Title (as implemented below)
  // 2. Loads all substances and their recipes into m_substances (Load Substances)
  // 3. Asks user for their chemist's name (store in m_myChemist as m_myName)
  // 4. Copies all substances from m_substances into the chemist's substance array
  // 5. Manages the game itself including win conditions continually calling the main menu 
  // Preconditions - None
  // Postconditions - m_substances and m_myChemist's substances populated
  void StartLab();
  // Name: DisplayMySubstances()
  // Desc - Iterates over m_myChemist's substances
  // Preconditions - Player's chemist has substances
  // Postconditions - Displays a numbered list of substances
  void DisplaySubstances();
  // Name: MainMenu()
  // Desc - Displays and manages menu
  // Preconditions - Player has an Chemist
  // Postconditions - Returns number including exit
  int MainMenu();
  // Name: SearchSubstances()
  // Desc - Attempts to search for raw substances (must be type "element")
  // Preconditions - Raw substances loaded
  // Postconditions - Increases quantity in Chemist's posession of substances
  void SearchSubstances();
  // Name: CombineSubstances()
  // Desc - Attempts to combine known substances. If combined, quantity of substance decreased
  // 1. Requests user to choose two substances (RequestSubstance)
  // 2. Checks to see if formula exists for combining two chosen substances
  //     (checks sub1, sub2 and sub2, sub1) using SearchFormula
  // 3. If there is an available formula for two chosen substances, checks
  //     quantity for two chosen substance.
  // If no quantity for two substances, tells user that there is no available quantity
  // If quantity is available, decreases quantity for two chosen substances
  //     from the chemist then increases new substance
  // 4. If there is no available formula, tells user that nothing happens when you try and merge two chosen substances
  // Preconditions - Chemist is populated with substances
  // Postconditions - Increments quantity of substance "made", decreases quantity of source items
  void CombineSubstances();
  // Name: RequestSubstance()
  // Desc - Allows the user to choose a substance to try and merge.
  //        Returns the index of chosen substance
  // Preconditions - Chemist has substances to try and merge
  // Postconditions - Returns integer of substance selected by user
  void RequestSubstance(int &choice);
  // Name: SearchFormula()
  // Desc - Searches formulas for two strings (name of item)
  // Preconditions - m_substances is populated
  // Postconditions - Returns int index of matching formula
  int SearchFormulas(string, string);
  // Name: CalcScore()
  // Desc - Displays current score for Chemist
  // Preconditions - Chemist is populated with substances
  // Postconditions - Displays total number of substances found. Displays
  //        percentange found as number found divided by total available
  void CalcScore();
  // Name: LabTitle()
  // Desc - Title for Lab (Do not edit)
  // Preconditions - None
  // Postconditions - None
  void LabTitle(){
    cout << "*******************************************************************" << endl;
    cout << "LL      AAA    BBB    OOOO  RRR    AAA   TTTTT  OOOO  RRR   YY  YY " << endl;
    cout << "LL     A   A   B  B   O  O  R  R  A   A    T    O  O  R  R   Y  Y  " << endl;
    cout << "LL     AAAAA   B  B   O  O  R  R  AAAAA    T    O  O  R  R    YY   " << endl;
    cout << "LL     A   A   BBBB   O  O  RRR   A   A    T    O  O  RRR     YY   " << endl;
    cout << "LL     A   A   B  B   O  O  R  R  A   A    T    O  O  R R     YY   " << endl;
    cout << "LLLLL  A   A   B  B   O  O  R  R  A   A    T    O  O  R  R    YY   " << endl;
    cout << "LLLLL  A   A   BBB    OOOO  R  R  A   A    T    OOOO  R  R    YY   " << endl;
    cout << "*******************************************************************" << endl;
  }
private:
  Chemist m_myChemist; //Player's Chemist for the game
  Substance m_substances[PROJ2_SIZE]; //All substances in the game (loaded from file)
};

#endif //Exit Header Guard
