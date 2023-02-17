//Title: RailFence.cpp
//Author: Ebun Oyemade
//Date 4/21/22
//Description: Contains function to handle rail fence ciphers

#include "RailFence.h"
using namespace std;

// Name: RailFence (Default Constructor)
// Desc: Constructor to build an empty RailFence Cipher (Defaults to 3 rails)
// Preconditions - None
// Postconditions - Creates a RailFence cipher
RailFence::RailFence():Cipher(){
  m_rails = 3;
}

// Name: RailFence (Overloaded Constructor)
// Desc: Constructor to build a populated RailFence Cipher (Defaults to 3 rails)
// Preconditions - Pass it the message, isEncrypted, and number of rails (any integer)
// Postconditions - Creates a RailFence cipher to be encrypted
RailFence::RailFence(string message, bool isEncrypted, int rails):Cipher(message, isEncrypted){
  m_rails = rails;
}

// Name: RailFence (Destructor)
// Desc: Destructor - Anything specific part of RailFence to delete?
// Preconditions - ~RailFence exists
// Postconditions - RailFence destroyed
RailFence::~RailFence(){}

// Name: Encrypt
// Desc: Letters are placed on a fence rail based on the number of rails
//       Letters are read from one rail at a time into a single string
// Preconditions - Message exists
// Postconditions - A single encrypted string is stored
void RailFence::Encrypt(){
  string message = GetMessage();
  string rails[m_rails] = {};
  string newMessage = "";
  int len = message.length();
  int count = 0;
  bool isCountUp = true;
  
  for(int i = 0; i < len; i++){//adds a character to an array to perform rail fence encryption
    rails[count] += message[i];
    
    if(isCountUp){//changes to keep array inbounds
      count += 1;
    }else{
      count -= 1;
    }
    
    if ((count == 0) || (count == m_rails - 1)){//checks to if the count is between 0 and m_rail
      isCountUp = !isCountUp;
    }
  }
  
  for(int i = 0; i < m_rails; i++){
    newMessage += rails[i];// adds rails to the new message
  }
  
  ToggleEncrypted();
  SetMessage(newMessage);
}

// Name: Decrypt
// Desc: Single encrypted string is pushed back on the rails and reversed
// Preconditions - Message exists
// Postconditions - The decrypted string is stored
void RailFence::Decrypt(){
  string message = GetMessage();
  string newMessage = "";
  int len = message.length();
  int railCalc  = (2 * (m_rails - 1));
  string rails[m_rails] = {};
  int count = 0;
  int numShift = len / railCalc;//length of the 1st row 
  int numShift2 = len / railCalc * 2;//length of other rows
  int extraRow = len % numShift;
  int railIndex[m_rails] = {0};
  bool isCountUp = true;
  
  for(int i = 0; i < m_rails; i++){//puts characters into an array to emulator rail fence grid 
    if(i == 0){//case 1st row
      int shift = numShift;
      if(extraRow >= 1){//adds 1 if there is a remainder
	shift += 1;
      }
      
      for(int j = 0;j < shift; j++){
	rails[i] += message[count];
	count++;
      }
      
    }else if(i == m_rails - 1){//case for last row
      for(int j = 0;count < len; j++){
	rails[i] += message[count];
	count++;
      }
      
    }else{
      int shift  = numShift2;
      
      if(extraRow >= i){//adds 1 if there is remainder & if row fits conditions
	shift += 1;
	if(m_rails - extraRow % m_rails <= i + 1){//adds 1 again if row fits conditions
	  shift += 1;
	}
      }
      
      for(int j = 0;j < shift; j++){
	rails[i] += message[count];
	count++;
      }
    }
  }
  
  count = 0;
  
  for(int i = 0; i < len; i++){//adds characters to put the message in it decrypted form
    newMessage += rails[count][railIndex[count]];
    railIndex[count] += 1;//counter for each the length of each index in rails
    
    if(isCountUp){//adds to emulator digagonal pattern of rail fence
      count += 1;
    }else{
      count -= 1;
    }
    
    if ((count == 0) || (count == m_rails - 1)){//switches when its at the end of the row
      isCountUp = !isCountUp;
    }
  }

  ToggleEncrypted();
  SetMessage(newMessage);
}

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (RailFence in this case)
string RailFence::ToString(){
  string name = "(RailFence)";

  return name;
}

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - r, delimiter, isencrypted, delimiter,
//                  message, delimiter, m_rails are returned for output
string RailFence::FormatOutput(){
  stringstream output;
  string message = GetMessage();
  bool isEncrypted = GetIsEncrypted();
  output << "r"<<DELIMITER << isEncrypted << DELIMITER << message << DELIMITER << m_rails;

  return output.str();
}

