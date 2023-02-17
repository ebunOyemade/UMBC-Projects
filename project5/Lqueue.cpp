#ifndef LQUEUE_CPP
#define LQUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
   public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  // Required
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
  // Required
 ~Lqueue();
  
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue<T>& operator= (Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  // Required
  void Push(const T&);
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  // Required
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  // Required (used only for testing)
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front
  // Required
  T Front();
  //Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  // Required
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  // Required
  int GetSize();
  // Name: Find()
  // Preconditions: Requires a lqueue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  // Required
  int Find(T&);
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Required
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  // Required
  void Clear();
  // Name: At
  // Precondition: Existing Lqueue
  // Postcondition: Returns object from Lqueue at a specific location
  // Desc: Iterates to node x and returns data from Lqueue
  // Required
  T At (int x);
 private:
   Node <T> *m_head; //Node pointer for the head
   Node <T> *m_tail; //Node pointer for the tail
   int m_size; //Number of nodes in queue
};

//**********Implement Lqueue Class Here***********
//**********All Functions Are Required Even If Not Used for Trivia**************
//Author:Ebun Oyemade
///Date: 5/4/22
//File: Lqueue.cpp
//Email: eoyemad1@umbc.edu
//Desc: Lqueue handles linked lists and functions reguarding linked list

// Name: Lqueue() (Linked List Queue) - Default Constructor
// Desc: Used to build a new linked queue (as a linked list)
// Preconditions: None
// Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  template<class T>
  Lqueue<T>::Lqueue(){
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
  }
// Name: ~Lqueue() - Destructor
// Desc: Used to destruct a Lqueue
// Preconditions: There is an existing lqueue with at least one node
// Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!
template<class T>
Lqueue<T>::~Lqueue(){
  while(m_size > 0){
    Pop();
  }
  m_head = nullptr;
  m_tail = nullptr;
}

// Name: Lqueue (Copy Constructor)
// Preconditions: Creates a copy of existing LQueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
template<class T>
Lqueue<T>::Lqueue(const Lqueue& lqueue){
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
  Clear();
  Node<T> *curr = lqueue.m_head;
  
  for(int i = 0; i < lqueue.m_size; i++){// loops tho get data from each node to add to linked list
    T data = curr -> GetData();//gets data for current node 
    Push(data);
    curr = curr -> GetNext();
  }
}

// Name: operator= (Overloaded Assignment Operator)
// Preconditions: Copies an Lqueue into an existing Lqueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
template<class T>
Lqueue<T>& Lqueue<T>::operator= (Lqueue<T>& lqueue){
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
  Node<T> *curr = lqueue.m_head;
  
  if(this != &lqueue){
    Clear();
    for(int i = 0; i < lqueue.m_size; i++){// loops tho get data from each node to add to linked list
      T data = curr -> GetData();
      this -> Push(data);
      curr = curr -> GetNext();
    }    
  }
  
  return *this;
}

// Name: Push
// Preconditions: Takes in data. Creates new node.
//                Requires a Lqueue
// Postconditions: Adds a new node to the end of the lqueue.
template<class T>
void Lqueue<T>::Push(const T& data){
  Node<T> *temp = new Node(data);
  
  if (m_size == 0){// adds nodes at the end of the list
    m_head = temp;
    m_tail = temp;

  }else{
    m_tail -> SetNext(temp); // adds pointer to tail
    m_tail = temp; // set tail to the last element
  }
  
  m_size++;
}

// Name: Pop
// Preconditions: Lqueue with at least one node.
// Postconditions: Removes first node in the lqueue, returns data from first node.
template<class T>
T Lqueue<T>::Pop(){
   Node<T> *curr = m_head;
   m_head = m_head -> GetNext();
   T data = curr -> GetData();
   delete curr;
   curr = nullptr;
   m_size--;

   return data;
}

// Name: Display
// Preconditions: Outputs the lqueue.
// Postconditions: Displays the data in each node of lqueue
template<class T>
void Lqueue<T>::Display(){
  Node<T> *curr = m_head;
  
  for(int i = 1; i <= m_size; i++){
    cout << curr -> GetData() << endl;
    curr = curr -> GetNext();
  }
}

// Name: Front
// Preconditions: Requires a populated lqueue
// Postconditions: Returns whatever data is in front
template<class T>
T Lqueue<T>::Front(){
  bool isEmpty = IsEmpty();
  T empty = 0;
  
  if(isEmpty == false){// checks to if there are any nodes
    return m_head -> GetData();
    
  }else{
    cout << "Lqueue is Empty" << endl;
    return empty;
  }
}

//Name: IsEmpty
// Preconditions: Requires a lqueue
// Postconditions: Returns if the lqueue is empty.
template<class T>
bool Lqueue<T>::IsEmpty(){
  bool isEmpty = false;
  if(m_size == 0){
    isEmpty = true;
  }

  return isEmpty;
}

// Name: GetSize
// Preconditions: Requires a lqueue
// Postconditions: Returns m_size
template<class T>
int Lqueue<T>::GetSize(){
  return m_size;
}

// Name: Find()
// Preconditions: Requires a lqueue
// Postconditions: Iterates and if it finds the thing, returns index, else -1
template<class T>
int Lqueue<T>::Find(T& thing){
  Node<T> *curr = m_head;
  int i = 0;
  bool isFound = false;
  
  while((isFound == false) && (i < m_size)){//loops until thing is found or is at the end of the list
    T data = curr -> GetData();
    
    if(data == thing){
      isFound = true;
    }
    
    curr = curr -> GetNext();
    i++;
  }

  if(isFound){
    return i;

  }else{
    return -1;
  }

}

// Name: Swap(int)
// Preconditions: Requires a lqueue
// Postconditions: Swaps the nodes at the index with the node prior to it.
template<class T>
void Lqueue<T>::Swap(int x){
  Node<T> *curr = m_head;
  Node<T> *prev = nullptr;//tracks node behide curr
  Node<T> *last = nullptr;//tracks node behide prev
  
  for(int i = 1; i <= x; i++){// loops until curr = x
    last = prev;
    prev = curr;
    curr = curr -> GetNext();
  }
  
  prev -> SetNext(curr);
  curr -> SetNext(prev);
  
  if(x > 2){//sets node behide curr m_next to curr if there is 
    last -> SetNext(curr);//sets node behind curr m_next to curr
  }
}

// Name: Clear
// Preconditions: Requires a lqueue
// Postconditions: Removes all nodes in a lqueue
template<class T>
void Lqueue<T>::Clear(){
  while(m_size > 0){// clears list by calling Pop until m_size is 0
    Pop();
  }
  m_head = nullptr;
  m_tail = nullptr;
}

// Name: At
// Precondition: Existing Lqueue
// Postcondition: Returns object from Lqueue at a specific location
// Desc: Iterates to node x and returns data from Lqueue
template<class T>
T Lqueue<T>::At(int x){
  Node<T> *curr = m_head;
  
  for(int i = 1; i <= x; i++){
    curr = curr -> GetNext();
  }
  
  return curr -> GetData();
}
#endif
