/*****************************************
** File:    Port.cpp
** Project: CMSC 202 Project 3, Spring 2022
** Author:  Ebun Oyemade
** Date:    4/5/2022
** Section: 54
** E-mail:  eoyemad1@umbc.edu 
**
** This file contains the main driver program for Project 1.
** This program reads the file specified as the first command
** line argument, counts the number of words, spaces, and
** characters, and displays the results in the format specified 
** in the project description.
**
**
***********************************************/

#include "Port.h"
using namespace std;

// Name: Port() - Default Constructor
// Desc: Used to build a new empty port
// Preconditions: None
// Postconditions: Creates a new Port for use in a Route
Port::Port(){
  m_name = "New Port";
  m_name = "New Location";
  m_west = 0;
  m_north = 0;
  m_next = nullptr;
}

// Name: Port(string, string, double, double) - Overloaded Constructor
// Desc: Used to build a new Port passing it a name, location, north, and west
// Preconditions: None
// Postconditions: Creates a new port for use in a Route
Port::Port(string name, string location, double north, double west){
  m_name = name;
  m_location = location;
  m_north = north;
  m_west = west;
  m_next = nullptr;
}

// Name: ~Port() - Destructor
// Desc: Used to destruct a port
//**This function should be empty but must be implemented
// Preconditions: There is an existing port
// Postconditions: Port is deallocated and has no memory leaks!
Port::~Port(){
}

// Name: GetName()
// Desc: Returns the name of the port
// Preconditions: None
// Postconditions: Returns the name of the port
string Port::GetName(){
  return m_name;
}

// Name: GetNext()
// Desc: Returns the pointer to the next port
// Preconditions: None (may return either port or nullptr)
// Postconditions: Returns m_next;
Port* Port::GetNext(){
  return m_next;
}

// Name: GetNorth()
// Desc: Returns the northern coordinates of the port
// Preconditions: None
// Postconditions: Returns the N coordinates of the port
double Port::GetNorth(){
  return m_north;
}

// Name: GetWest()
// Desc: Returns the western coordinates of the port
// Preconditions: None
// Postconditions: Returns the W coordinates of the port
double Port::GetWest(){
  return m_west;
}

// Name: GetLocation()
// Desc: Returns the description of where the port is located
// Preconditions: None
// Postconditions: Returns the description of where the port is located
string Port::GetLocation(){
  return m_location;
}

// Name: SetNext()
// Desc: Updates the pointer to a new target (either a port or nullptr)
// Preconditions: None
// Postconditions: Sets the next port
void Port::SetNext(Port* curr){
  m_next = curr;
}
