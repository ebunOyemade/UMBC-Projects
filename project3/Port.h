//Name: Port.h
//Project: CMSC 202 Project 3, Spring 2022
//Author:  Jeremy Dixon
//Date:    2/22/2022
//Desc: This file contains the header details for the Port class
//      The ports are nodes for a route

#ifndef PORT_H
#define PORT_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class Port {
 public:
  // Name: Port() - Default Constructor
  // Desc: Used to build a new empty port
  // Preconditions: None
  // Postconditions: Creates a new Port for use in a Route
  Port();
  // Name: Port(string, string, double, double) - Overloaded Constructor
  // Desc: Used to build a new Port passing it a name, location, north, and west
  // Preconditions: None
  // Postconditions: Creates a new port for use in a Route
  Port(string, string, double, double);
  // Name: ~Port() - Destructor
  // Desc: Used to destruct a port
  //**This function should be empty but must be implemented
  // Preconditions: There is an existing port
  // Postconditions: Port is deallocated and has no memory leaks!
 ~Port();
  // Name: GetName()
  // Desc: Returns the name of the port
  // Preconditions: None
  // Postconditions: Returns the name of the port
  string GetName();
  // Name: GetNext()
  // Desc: Returns the pointer to the next port
  // Preconditions: None (may return either port or nullptr)
  // Postconditions: Returns m_next;
  Port* GetNext();
  // Name: GetNorth()
  // Desc: Returns the northern coordinates of the port
  // Preconditions: None
  // Postconditions: Returns the N coordinates of the port
  double GetNorth();
  // Name: GetWest()
  // Desc: Returns the western coordinates of the port
  // Preconditions: None
  // Postconditions: Returns the W coordinates of the port
  double GetWest();
  // Name: GetLocation()
  // Desc: Returns the description of where the port is located
  // Preconditions: None
  // Postconditions: Returns the description of where the port is located
  string GetLocation();
  // Name: SetNext()
  // Desc: Updates the pointer to a new target (either a port or nullptr)
  // Preconditions: None
  // Postconditions: Sets the next port
  void SetNext(Port*);
  // Name: operator<<
  // Desc: Overloaded << operator to return ostream from an Port
  // Must not have a cout statement in this
  // Preconditions: Requires an Port
  // Postconditions: Returns ostream populated with Port's name and location
  // **PROVIDED** Do not edit
  friend ostream &operator<< (ostream &output, Port &myPort){
    output << myPort.m_name << ", " << myPort.m_location;
    return output;
  }
private:
  string m_name; //Name of Port
  string m_location; //Location of Port
  double m_north; //North of port
  double m_west; //West of port
  Port *m_next; //Port pointer to next port
};

#endif
