//Title: Caesar.cpp
//Author: Ebun Oyemade
//Date 4/21/22
//Description: Contains function to handle caesar ciphers

#include "Caesar.h"
using namespace std;

// Name: Caesar (Default Constructor)
// Desc: Constructor to build an empty Caesar Cipher (Defaults to shift 3)
// Preconditions - None
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar():Cipher(){
  m_shift = 3;
}

// Name: Caesar (Overloaded Constructor)
// Desc: Constructor to build a populated Caesar Cipher (Defaults to shift 3)
// Preconditions - Pass it the message, isEncrypted, and shift (any integer)
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar(string message, bool isEncrypted, int shift):Cipher(message, isEncrypted){
  m_shift = shift;
}

// Name: Caesar (Destructor)
// Desc: Destructor - Anything specific to Caesar to delete?
// Preconditions - ~Caesar exists
// Postconditions - Caesar destroyed
Caesar::~Caesar(){}

// Name: Encrypt
// Desc: Shifts characters right based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "right".
void Caesar::Encrypt(){
  string message = GetMessage();
  string newMessage = "";
  int len = message.length();
  const char UPPER = 'A';
  const char LOWER = 'a';
  const int  ABC_NUM = 26;

  for(int i = 0; i < len; i++ ){//checks to see if a character is a letter
    char letter = message[i];
    int value  = letter;
    
    if ((value >= LOWER) && (value <= LOWER + ABC_NUM)){//checks to see if a character is a lowercase letter
      letter = (letter + m_shift - LOWER) % ABC_NUM + LOWER;//formula for shift accounts for case when letter is shifted past z
      newMessage += letter;
      
    }else if ((value >= UPPER) && (value <= UPPER + ABC_NUM)){//checks to see if it is an upper case letter
	letter = (letter + m_shift - UPPER) % ABC_NUM + UPPER;
	newMessage += letter;

    }else{
      newMessage += letter;
    }

  }
  
  ToggleEncrypted();
  SetMessage(newMessage);
}

// Name: Decrypt
// Desc: Shifts characters left based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "left".
void Caesar::Decrypt(){
  string message = GetMessage();
  string newMessage = "";
  int len = message.length();
  const char UPPER = 'A';
  const char LOWER = 'a';
  const int  ABC_NUM = 26;
  
  for(int i = 0; i < len; i++ ){
    char letter = message[i];
    int value  = letter;
    
    if((value >= LOWER) && (value <= LOWER + ABC_NUM)){//checks to see if a character is a lowercase letter
      letter = ((letter - m_shift) - LOWER + ABC_NUM) % ABC_NUM + LOWER;//formula for shift accounts for case when letter is shifted past a
      newMessage += letter;
    }else if((value >= UPPER) && (value <= UPPER + ABC_NUM)){//checks to see if a character is a uppercase letter
      letter = ((letter - m_shift) - UPPER + ABC_NUM) % ABC_NUM + UPPER;
      newMessage += letter;
    }else{
       newMessage += letter;
    }    
  }
  
  ToggleEncrypted();
  SetMessage(newMessage);

}

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Caesar in this case)
string Caesar::ToString(){
  string name = "(Caesar)";
  
  return name;
}

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - c, delimiter, isencrypted, delimiter,
//                  message, delimiter, m_shift are returned for output
string Caesar::FormatOutput(){
  stringstream output;
  string message = GetMessage();
  bool isEncrypted = GetIsEncrypted();
  output << "c"<<DELIMITER << isEncrypted << DELIMITER << message << DELIMITER << m_shift;
  
  return output.str();
}
