//Title: Vigenere.h
//Author: Ebun Oyemade
//Date: 4/21/2022
//Description: This headerfile for the vigenere ciphers

#ifndef VIGENERE_H
#define VIGENERE_H
#include "Cipher.h"
#include <istream>
#include <string>
using namespace std;

class Vigenere: public Cipher{
public:
  // Name: Vigenere (Default Constructor)
  // Desc: Constructor to build an empty Vigenere Cipher (Defaults to hi)
  // Preconditions - None
  // Postconditions - Creates a Vigenere cipher
  Vigenere();
  
  // Name: Vigenere (Overloaded Constructor)
  // Desc: Constructor to build a populated Vigenere Cipher (Defaults to hi)
  // Preconditions - Pass it the message, isEncrypted, and word
  // Postconditions - Creates a Vigenere cipher to be encrypted
  Vigenere(string, bool, string);
  
  // Name: Vigenere (Destructor)
  // Desc: Destructor - Anything specific part of Vigenere to delete?
  // Preconditions - ~RailFence exists
  // Postconditions - RailFence destroyed
  ~Vigenere();
  
  // Name: Encrypt
  // Desc: Letters are from key word and message turned into a numbers [0,25] and put in an equation to get results       
  // Preconditions - Message exists
  // Postconditions - A single encrypted string is stored
  void Encrypt();
  
  // Name: Decrypt
  // Desc: Single encrypted
  // Preconditions - Message exists
  // Postconditions - The decrypted string is stored
  void Decrypt();
  
  // Name: ToString
    // Desc - A function that returns the string of the object type
  // Preconditions - The object exists
  // Postconditions - The subtype is returned (Vigenere in this case)
  string ToString();

  // Name: FormatOutput()
  // Desc - A function that returns the formatted output for Output function
  // Preconditions - The object exists (use stringstream)
  // Postconditions - v, delimiter, isencrypted, delimiter,
  //                  message, delimiter, m_word are returned for output
  string FormatOutput();
private:
  string  m_word; //word for the key.

};
#endif
