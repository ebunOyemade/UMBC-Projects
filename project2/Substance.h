//Title: Substance.h
//Author: Jeremy Dixon
//Date: 2/24/2022
//Description: This is part of project 2 in CMSC 202 @ UMBC

#ifndef SUBSTANCE_H //Include/Header Guard
#define SUBSTANCE_H //Include/Header Guard

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

// Name: Substance struct
// Desc - Used to store data about substances
//        Type is either element or compound
//        Formula is the full formula of the substance. Elements have exactly one entry in the substance.
//        A compound is made by combining substance1 and substance2

struct Substance{
  Substance(){} //Default constructor - can leave empty
  Substance(string name, string type, string formula, string substance1, string substance2,
	   int quantity){
    m_name = name; //Name of this substance
    m_type = type; //Type of the substance (element or compound)
    m_formula = formula; //Full formula of the substance
    m_substance1 = substance1; //Name of first required substance to create
    m_substance2 = substance2; //Name of second required substance to create
    m_quantity = quantity; //Number of the substance
  }
  string m_name; //Name of the substance
  string m_type; //Type of the substance (element or compound)
  string m_formula; //Full formula of the substance
  string m_substance1; //Required substance 1 to create
  string m_substance2; //Required substance 2 to create
  int m_quantity = 0; //Quantity of substance owned
};

#endif
