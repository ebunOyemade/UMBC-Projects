//Title: CipherTool.cpp
//Author: Ebun Oyemade
//Date 4/21/22
//Description: Contains function to ui and call functions from Cipher and its child functions and exports file

#include "CipherTool.h"
#include "Vigenere.cpp"
using namespace std;

// Name: CipherTool Constructor
// Desc - Creates a new CipherTool and sets m_filename based on string passed
// Preconditions - Input file passed and populated with Cipher
// Postconditions - CipherTool created
CipherTool::CipherTool(string filename){
  m_filename = filename;
}

// Name: CipherTool Destructor
// Desc - Calls destructor for all ciphers in m_ciphers
// Preconditions - m_ciphers is populated
// Postconditions - m_ciphers deallocated and vector emptied
CipherTool::~CipherTool(){
   for(unsigned int i = 0; i < m_ciphers.size(); i++){
     delete m_ciphers.at(i);
  }
}

// Name: LoadFile
// Desc - Opens file and reads in each Cipher. Each Cipher dynamically allocated
// and put into m_ciphers (c is Caesar, r is RailFence, and o is Ong)
// Preconditions - Input file passed and populated with Ciphers
// Postconditions - m_ciphers populated with Ciphers
void CipherTool::LoadFile(){
  fstream cipherFile;
  cipherFile.open(m_filename);
  string type;
  string temp_isEncrypted;//string for isEncrypted that converts to bool
  string message;
  string temp_railShift;//string for key that converts to an int
  bool isEncrypted;
  int railShift;//the key for the cipher
  const string CAESAR = "c";
  const string RAILFENCE = "r";
  const string ONG = "o";
  const string VIGENERE = "v";

  if(cipherFile.is_open()){
    while(getline(cipherFile, type, DELIMITER)&& getline(cipherFile, temp_isEncrypted, DELIMITER)&&getline(cipherFile, message, DELIMITER)&&getline(cipherFile, temp_railShift)){//checks to see if a line has all necessary info
      isEncrypted = StringToBoolean(temp_isEncrypted);

      if(type == CAESAR){//makes a cipher object based on type received from file
	railShift = stoi(temp_railShift);//converts a string to an int
	Caesar *cipher = new Caesar(message, isEncrypted, railShift);
     	m_ciphers.push_back(cipher);
	
      }else if(type == RAILFENCE){
	railShift = stoi(temp_railShift);//converts a string to an int
	RailFence *cipher = new RailFence(message, isEncrypted, railShift);
	m_ciphers.push_back(cipher);
	
      }else if(type == ONG){
	Ong *cipher = new Ong(message, isEncrypted);
	m_ciphers.push_back(cipher);
	
      }else if(type == VIGENERE){
        Vigenere *cipher = new Vigenere(message, isEncrypted, temp_railShift);
        m_ciphers.push_back(cipher);
      }

    }
    
  }else{
    cout << "File won't open" << endl;
  }
  
  cipherFile.close();
}

// Name: StringToBoolean
// Desc - Helper function that converts a string to a boolean for reading in file
// Preconditions - Passed string of either 0 or 1
// Postconditions - Returns false if 0 else true
bool CipherTool::StringToBoolean(string input){
  bool boolean = true;
  const string ZERO = "0";
  
  if(input == ZERO){
    boolean = false;
  } else{
    boolean = true;
  }
  
  return boolean;
}

// Name: DisplayCiphers
// Desc - Displays each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Displays ciphers
void CipherTool::DisplayCiphers(){
  for(unsigned int i = 0; i < m_ciphers.size();i++ ){
    cout << i + 1 << ". ";
    cout << *m_ciphers.at(i);
  }
}

// Name: EncryptDecrypt
// Desc - Encrypts or decrypts each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Either Encrypts or Decrypts each cipher in m_ciphers
void CipherTool::EncryptDecrypt(bool encrypt){
  int change = 0;//counts the number ciphers encrypted/decrypted
  
  if(encrypt){
    for(unsigned int i = 0; i < m_ciphers.size();i++ ){
      if(m_ciphers.at(i) -> GetIsEncrypted() == false){//checks to see if message is encryted
	m_ciphers.at(i) -> Encrypt();
	change += 1;
      }
    }

    cout << change << " ciphers Encrypted" << endl;
    
  }else{
     for(unsigned int i = 0; i < m_ciphers.size();i++ ){
       if(m_ciphers.at(i) -> GetIsEncrypted() == true){//checks to see if message is encrypted
	 m_ciphers.at(i) -> Decrypt();
	 change += 1;
       }
     }
     
     cout << change << " ciphers Decrypted" << endl;
  }

  DisplayCiphers();
}

// Name: Export
// Desc - Exports each of the ciphers in the m_ciphers (so they can be reused)
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - All ciphers exported
void CipherTool::Export(){
  string filename;
  cout << "What would you like to call the export file?" << endl;
  cin >> filename;
  ofstream myfile;
  myfile.open(filename);
  int numFiles = 0;//counts the number ciphers exported 
  
  for(unsigned int i = 0; i < m_ciphers.size();i++ ){
    myfile << m_ciphers[i] -> FormatOutput() << endl;
    numFiles += 1;
  }

  cout << numFiles << " ciphers exported" << endl;
  myfile.close();
}

// Name: Menu
// Desc - Displays menu and returns choice
// Preconditions - m_ciphers all populated
// Postconditions - Returns choice
int CipherTool::Menu(){
  int choice;
  cout << "What would you like to do?" << endl;
  cout << "1. Display All Ciphers" << endl;
  cout << "2. Encrypt All Ciphers" << endl;
  cout << "3. Decrypt All Ciphers" << endl;
  cout << "4. Export All Ciphers" << endl;
  cout << "5. Quit" << endl;
  cin >> choice;
  
  while((choice < 1) || (choice > 5)){//checks to if input is between 1-5
    cout << "Invalid input" << endl;
    cin >> choice;
  }
  
  return choice;
}

// Name: Start
// Desc - Loads input file, allows user to choose what to do
// Preconditions - m_ciphers populated with ciphers
// Postconditions - none
void CipherTool::Start(){
  LoadFile();
  int choice = Menu();
  
  while(choice != 5){
    if(choice == 1){
      DisplayCiphers();
      
    }else if(choice == 2){
      EncryptDecrypt(true);
      
    }else if(choice == 3){
      EncryptDecrypt(false);
      
    }else if(choice == 4){
      Export();
    }
    
    choice = Menu();
  }

  cout << "Thanks for using UMBC Encryption" << endl;
}

