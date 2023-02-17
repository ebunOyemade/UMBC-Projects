#include "Vigenere.h"
using namespace std;

// Name: Vigenere (Default Constructor)
// Desc: Constructor to build an empty Vigenere Cipher (Defaults to hi)
// Preconditions - None
// Postconditions - Creates a Vigenere cipher
Vigenere::Vigenere():Cipher(){
  m_word = "hi";
}

// Name: Vigenere (Overloaded Constructor)
// Desc: Constructor to build a populated Vigenere Cipher (Defaults to hi)
// Preconditions - Pass it the message, isEncrypted, and word
// Postconditions - Creates a Vigenere cipher to be encrypted
Vigenere::Vigenere(string message, bool isEncrypted, string word):Cipher(message, isEncrypted){
  m_word = word;
}

// Name: Vigenere (Overloaded Constructor)
// Desc: Constructor to build a populated Vigenere Cipher (Defaults to hi)
// Preconditions - Pass it the message, isEncrypted, and word
// Postconditions - Creates a Vigenere cipher to be encrypted
Vigenere::~Vigenere(){}

// Name: Encrypt
// Desc: Letters are from key word and message turned into a numbers [0,25] and put in an equation to get results
// Preconditions - Message exists
// Postconditions - A single encrypted string is stored
void Vigenere::Encrypt(){
  string message = GetMessage();
  string newMessage = "";
  int len = message.length();
  int len2 = m_word.length();
  int count = 0;
  const char UPPER = 'A';
  const char LOWER = 'a';
  const int  ABC_NUM = 26;
  

  for(int i = 0; i < len; i++ ){//checks to see if a character is a letter
    char letter = message[i];
    int value  = letter;

    if ((value >= LOWER) && (value <= LOWER + ABC_NUM)){//checks to see if a character is a lowercase letter
      letter = (letter - LOWER + (m_word[count % len2] - LOWER)) % ABC_NUM + LOWER;//formula for shift with  another letter
      newMessage += letter;
      count++;

    }else if ((value >= UPPER) && (value <= UPPER + ABC_NUM)){//checks to see if it is an upper case letter
        letter = (letter - UPPER + (m_word[count % len2] - LOWER)) % ABC_NUM + UPPER;
        newMessage += letter;
	count++;
    }else{
      newMessage += letter;
    }

  }

  ToggleEncrypted();
  SetMessage(newMessage);
}

// Name: Decrypt
// Desc: Single encrypted
// Preconditions - Message exists
// Postconditions - The decrypted string is stored
void Vigenere::Decrypt(){
  string message = GetMessage();
  string newMessage = "";
  int len = message.length();
  int len2 = m_word.length();
  const char UPPER = 'A';
  const char LOWER = 'a';
  const int  ABC_NUM = 26;
  int count = 0;


  for(int i = 0; i < len; i++ ){//checks to see if a character is a letter
    char letter = message[i];
    int value  = letter;
    if ((value >= LOWER) && (value <= LOWER + ABC_NUM)){//checks to see if a character is a lowercase letter
      letter = ((letter - LOWER - (m_word[count % len2] - LOWER))+ ABC_NUM) % ABC_NUM + LOWER;//formula for shift characters with another character
      newMessage += letter;
      count++;

    }else if ((value >= UPPER) && (value <= UPPER + ABC_NUM)){//checks to see if it is an upper case letter
      letter = ((letter - UPPER - (m_word[count % len2] - LOWER)) + ABC_NUM) % ABC_NUM + UPPER;
      newMessage += letter;
      count++;

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
// Postconditions - The subtype is returned (Vigenere in this case)
string Vigenere::ToString(){
  string name = "(Vigenere)";

  return name;
}

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - v, delimiter, isencrypted, delimiter,
//                  message, delimiter, m_word are returned for output
string Vigenere::FormatOutput(){
  stringstream output;
  string message = GetMessage();
  bool isEncrypted = GetIsEncrypted();
  output << "v"<<DELIMITER << isEncrypted << DELIMITER << message << DELIMITER << m_word;

  return output.str();
}
