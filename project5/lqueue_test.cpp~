#include <iostream>
#include <string>
using namespace std;
#include "Lqueue.cpp"

// To test just queue follow these instructions:
//   1.  make ttest


int main () {

  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  int test1 = 10;
  int test2 = 20;
  int test3 = 30;
  //Test Default Constructor
  Lqueue <int> *newLQ1 = new Lqueue <int>();
  //Push 4 nodes into Lqueue
  newLQ1->Push(test1);
  newLQ1->Push(test2);
  newLQ1->Push(test3);
  cout << "After 3 Pushs size: " << newLQ1->GetSize() << endl;
  newLQ1->Display();
  cout << "End Test 1 - Constructor and Push" << endl << endl;
    
  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor Running" << endl;
  //Test Copy constructor
  Lqueue <int> *newLQ2 = new Lqueue <int>(*newLQ1);
  newLQ2->Display();
  cout << "size below should match. Location should not" << endl;
  cout << "Source size: " << newLQ1->GetSize() << " and Copied size: " << newLQ2->GetSize() << endl;
  cout << "Source location: " << &newLQ1 << " and Copied location: " << &newLQ2 << endl;
  cout << "End Test 2 - Copy" << endl << endl;
  
  //Test 3 - Overloaded Assignment Operator
  cout << "Test 3 - Overloaded Assignment Operator Running" << endl;
  //Create new Lqueue using constructor
  Lqueue <int> *newLQ3 = new Lqueue <int>();
  //Update using overloaded assignment operator
  *newLQ3 = *newLQ1;
  newLQ3->Display(); //Display contents of newLQ3
  cout << "size below should match. Location should not" << endl;
  cout << "Source size: " << newLQ1->GetSize() << " and Assigned size: " << newLQ3->GetSize() << endl;
  cout << "Source location: " << &newLQ1 << " and Assigned location: " << &newLQ3 << endl;
  cout << "End Test 3 - Assignment" << endl << endl;
  
  //Test 4 - Test Pop
  cout << "Test 4 - Pop" << endl;
  cout << "size before: " << newLQ1->GetSize() << " ";
  newLQ1->Pop();
  cout << "size after: " << newLQ1->GetSize() << endl;
  cout << "End Test 4 - Pop" << endl << endl;
  
  //Test 5 - Test size and Clear
  cout << "Test 5 - size and Clear Running" << endl;
  //Test size()
  cout << "Outputting the size" << endl;
  cout << newLQ2->GetSize() << endl;
  //Test Clear()
  cout << "Clearing all nodes" << endl;
  newLQ2->Clear();
  cout << "Outputting the size (should now be 0)" << endl;
  cout << newLQ2->GetSize() << endl;
  cout << endl;

  //Test 6 - Test Find
  cout << "Test 6 - Find" << endl;
  cout << "Try to find 10 (Should NOT find it)" << endl;
  if(newLQ1->Find(test1) != -1){
    cout << "10 Found" << endl;
  }else{
    cout << "10 NOT Found" << endl;
  }
  cout << "Try to find 20 (Should find it)" << endl;
  if(newLQ1->Find(test2) != -1){
    cout << "20 Found" << endl << endl;
  }else{
    cout << "20 NOT Found" << endl << endl;
  }
  
  //Test 7 - Test Destructor
  cout << "Test 7 - Test Destructor" << endl;
  cout << "delete newLQ1" << endl;
  delete newLQ1;
  cout << "delete newLQ2" << endl;
  delete newLQ2;
  cout << "delete newLQ3" << endl;
  delete newLQ3;
  cout << "End Test 6 - Destructors" << endl;
  return 0;
}
