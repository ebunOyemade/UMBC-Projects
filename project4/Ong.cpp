//Title: Ong.cpp
//Author: Ebun Oyemade
//Date 4/21/22
//Description: Contains function to handle ong ciphers

#include "Ong.h"
using namespace std;

// Name: Ong (Default Constructor)
// Desc: Constructor to build an empty Ong Cipher
// Preconditions - None
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong():Cipher(){}

// Name: Ong (Overloaded Constructor)
// Desc: Constructor to build a populated Ong Cipher
// Preconditions - Pass it the message and isEncrypted
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong(string message, bool isEncrypted):Cipher(message, isEncrypted){}

// Name: Ong (Destructor)
// Desc: Destructor - Anything unique to Ong to delete?
// Preconditions - ~Ong exists
// Postconditions - Ong destroyed
Ong::~Ong(){}

// Name: IsVowel (Helper function)
// Desc: Returns true if vowel, space, or punctuation
// Preconditions - Message exists
// Postconditions - Returns true or false as above
bool Ong::IsVowel(char letter){
  bool isVowel = false;
  const char VOWELS[10] = {'a','e','i','o','u','A','E','I','O','U'};
  const int VOWEL_SIZE = 10;
  
  for(int i = 0; i < VOWEL_SIZE; i++ ){
    if(letter == VOWELS[i]){//checks to see the letter matches a vowel on VOWELS
      isVowel = true;

      return isVowel;
    }
  }

  return isVowel;
}

// Name: Encrypt
// Desc: If vowel then vowel and dash displayed. dog = dong-o-gong
// If consonant then consonant and ong and dash displayed.
// Preconditions - Message exists
// Postconditions - Encrypts as above
void Ong::Encrypt(){
  string message = GetMessage();
  string newMessage = "";
  const int SPACE = 32;
  const int A_NUM = 64;
  const char DASH =  '-';
  int len = message.length();
  
  for(int i = 0; i < len; i++){//checks to see if ong- or - should be added
    if((int)message[i] > A_NUM){
      if(!IsVowel(message[i])){
	newMessage += message[i];
	newMessage += ong;
	newMessage += DASH;
	
      }else{
	newMessage += message[i];
	newMessage += DASH;
      }
      
    }else if ((int)message[i] != SPACE){//checks to see a character is a space
      newMessage += message[i];
      
      if(i != len - 1){// checks to see if there is a space and if  - should be added 
	newMessage += DASH;
      }
      
    }else{// add a space 
      int size = newMessage.length();
      newMessage[size - 1] = message[i];
    }
  }
  
  ToggleEncrypted();
  SetMessage(newMessage);
}

// Name: Decrypt
// Desc: Removes the dashes and "ong" when necessary cong-a-tong = cat
// Double check words like "wrong" so that they work correctly!
// Preconditions - Message exists
// Postconditions - Original message is displayed
void Ong::Decrypt(){
  string message = GetMessage();
  string newMessage = "";
  const int SPACE = 32;
  const char UPPER_A = 'A';
  int len = message.length();
  
  for(int i = 0; i < len; i++){//adds the characters of the original message 
    if(message[i] > UPPER_A){
      if(!IsVowel(message[i])){
	newMessage += message[i];
	i += 4;// skips over 'ong-'
	
      }else{
        newMessage += message[i];
	i += 1; // skips over '-'
      }
      
    }else if((int)message[i] != SPACE){
      newMessage += message[i];
      i += 1;// skips over '-'
    }
    
    if((int)message[i] == SPACE){//adds space
      newMessage += message[i];
    }
  }
  
  ToggleEncrypted();
  SetMessage(newMessage);  
}

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Ong in this case)
string Ong::ToString(){
  string name = "(Ong)";

  return name;
}

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - o, delimiter, isencrypted, delimiter,
//                  message, delimiter, blank are output
string Ong::FormatOutput(){
  stringstream output;
  string message = GetMessage();
  bool isEncrypted = GetIsEncrypted();
  output << "o"<<DELIMITER << isEncrypted << DELIMITER << message << DELIMITER;

  return output.str();
}


