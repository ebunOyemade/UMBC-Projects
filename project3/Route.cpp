/*****************************************
** File:    Route.cpp
** Project: CMSC 202 Project 3, Spring 2022
** Author:  Ebun Oyemade
** Date:    4/5/2022
** Section: 54
** E-mail:  eoyemad1@umbc.edu
**
** This file contains the main driver program for Project 3.
** This controls all funtionality of the route class
** 
** 
** 
**
**
***********************************************/

#include "Route.h"
using namespace std;

// Name: Route() - Default Constructor
// Desc: Used to build a new Route (linked list) make up of ports
// Preconditions: None
// Postconditions: Creates a new Route where m_head and m_tail point to nullptr and size = 0
Route::Route(){
  m_name = "Test";
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// Name: SetName(string)
// Desc: Sets the name of the route (usually first port to last port)
// Preconditions: None
// Postconditions: Sets name of route
void Route::SetName(string name){
  m_name = name;
}

// Name: ~Route() - Destructor
// Desc: Used to destruct a strand of Route
// Preconditions: There is an existing Route strand with at least one port
// Postconditions: Route is deallocated (including all dynamically allocated ports)
//                 to have no memory leaks!
Route::~Route(){
  while(m_size > 0){
    RemovePort(m_size);
  }
  
  m_head = nullptr;
  m_tail = nullptr;
}

// Name: InsertEnd (string, string, double double)
// Desc: Creates a new port using the data passed to it.
//       Inserts the new port at the end of the route
// Preconditions: Takes in a Port
//                Requires a Route
// Postconditions: Adds the new port to the end of a route
void Route::InsertEnd(string name, string location, double north, double west){
  Port *temp = new Port(name, location, north, west);
  
  if (m_size == 0){// adds nodes at the end of the list
    m_head = temp;
    m_tail = temp;

  }else{
    m_tail -> SetNext(temp); // adds pointer to tail
    m_tail = temp; // set tail to the last element

  }

  m_size++;
}

// Name: RemovePort(int index)
// Desc: Removes a port from the route at the index provided
//       Hint: Special cases (first port, last port, middle port)
// Preconditions: Index must be less than the size of the route
//       Cannot make route less than two ports. If the route has
//       two or fewer ports, fails.
// Postconditions: Name may be updated. Size is reduced. Route has one less port.
void Route::RemovePort(int port){
  if ((port >= 1) && (port <= m_size)){
    Port *curr = m_head;
    
    if(port == 1){// special case for head
      m_head = m_head -> GetNext();// sets the head to next item
      delete curr;
      curr = nullptr;

    }else if(port == m_size){// special case for tail
      while(curr -> GetNext() != m_tail){
	curr = curr -> GetNext();
      }
     
      delete curr -> GetNext(); // deletes pointer of the new tail
      m_tail = curr;// sets new tail
      Port *tail = nullptr;
      m_tail -> SetNext(tail); // sets new tail pointer to null
     
    }else{
      int i = 1;
      Port *target = curr -> GetNext();
      Port *next = target -> GetNext();
      
      while(i != port - 1){//sets curr to point before the point to be removed, next is point after, and target is the point
	curr = curr -> GetNext();
	target = target -> GetNext();
	next = next -> GetNext();
	i++;
      }
      
      curr -> SetNext(next);// links the point before the target to connect to the node after it
      delete target;
      target = nullptr;
    }
  }
  m_size--;
}

// Name: GetName()
// Desc: Returns the name of the route (Usually starting port to last port)
//       For example: Baltimore to Brunswick
// Preconditions: Requires a Route
// Postconditions: Returns m_name;
string Route::GetName(){
  return m_name;
}

// Name: UpdateName()
// Desc: Updates m_name based on the name of the first port in the route
//       and the last port in the route
//       For example: Baltimore to Brunswick
// Preconditions: Requires a Route with at least two ports
// Postconditions: Returns m_name;
string Route::UpdateName(){
  string first = m_head -> GetName();
  string last = m_tail -> GetName();
  m_name = first + " to " + last;
  return m_name;
}

// Name: GetSize()
// Desc: Returns the number of ports in a route
// Preconditions: Requires a Route
// Postconditions: Returns m_size;
int Route::GetSize(){
  return m_size;
}

// Name: ReverseRoute
// Desc: Reverses a route
// Preconditions: Reverses the Route
// Postconditions: Route is reversed in place; nothing returned
void Route::ReverseRoute(){
  Port *curr = m_head;
  Port *prev = nullptr;
  Port *next = nullptr;
  m_tail = m_head;
  
  while(curr != nullptr){// loops until loop is reversed
    next = curr -> GetNext();
    curr -> SetNext(prev);
    prev = curr;
    curr = next; 
  }
  
  m_head = prev;
}

// Name: GetData (int)
// Desc: Returns a port at a specific index
// Preconditions: Requires a Route
// Postconditions: Returns the port from specific item
Port* Route::GetData(int index){
  Port *curr = m_head;
  int i = 0;
  
  while(i != index){
    curr -> GetNext();
    i++;
  }
  
  return curr;
}

// Name: DisplayRoute
// Desc: Displays all of the ports in a route
// Preconditions: Requires a Route
// Postconditions: Displays all of the ports in a route
// Formatted: Baltimore, Maryland (N39.209 W76.517)
void Route::DisplayRoute(){
  Port *port = m_head;
  int i = 1;
  cout << m_name << endl;
  
  while(i <= m_size){
    cout << i << ". " << port -> GetName()<<  ',' << port -> GetLocation()
	 << "(N" << port -> GetNorth() << " W" << port -> GetWest() << ")" << endl;
    port = port -> GetNext();
    i++;
  } 
}