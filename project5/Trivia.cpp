/*****************************************************************************
 ** File: Trivia.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Kush Shah and CMSC202
 ** Date:    04/05/2022
 ** Email:   k216@umbc.edu
 **
 Description: CPP file for Trivia class. Includes both class definition and
 class function definitions. Loads a file of trivia questions
*****************************************************************************/

#ifndef TRIVIA_CPP
#define TRIVIA_CPP
#include "Lqueue.cpp"
#include "Question.cpp"
#include <fstream>
#include <vector>
using namespace std;

const string DEFAULT_FILE = "proj5_string.txt";
const char DELIMITER = '|';

template <class T>
class Trivia {
public:
  // Name: Default Constructor
  // Desc: Displays the title, Loads Questions and calls menu
  // Indicates if the file was not loaded.
  // Precondition: None
  // Postcondition: User is prompted with assignment menus
  Trivia(string filename= DEFAULT_FILE);
  // Name: Destructor
  // Desc: Deallocates memory allocated for the Questions and
  // resets all variables.
  // Precondition: A Trivia exists.
  // Postcondition: All dynamically allocated memory in Trivia is deleted.
  ~Trivia();
  // Name: LoadQuestions
  // Desc: Each input file will be for a specific type of question (int, double, string)
  //       Reads in Questions from a file and stores them in anLqueue.
  //       An input file will be for exactly one type of question (int, double, string)
  // Precondition: None.
  // Postcondition: Returns true if file was read. Otherwise, it returns false.
  bool LoadQuestions(string filename);
  // Name: MainMenu
  // Desc: Presents user with menu options for showing subjects and allowing
  // user to work on a subject.
  // Precondition: None.
  // Postcondition: The main menu is presented.
  void MainMenu();
  // Name: DisplaySubjects
  // Desc: Presents all Subjects with corresponding numerical identifiers.
  // Precondition: Subjects have been added.
  // Postcondition: All assignments are printed to the screen.
  void DisplaySubjects();
  // Name: StartSubject
  // Desc: Starts working on a selected Subject.
  // Displays the number of questions in subject.
  // Starts at beginning and goes through each question.
  // After all questions have been answered:
  //       displays total correct, incorrect, and percentage correct
  // Precondition: m_questions has been populated
  // Postcondition: Returns to main menu
  void StartSubject();
  // Name: AddSubject
  // Desc: Checks to see if a subject exists in m_subjects.
  //       If not, inserts subject into m_subjects.
  // Precondition: A Subject exists.
  // Postcondition: Add subject to m_subjects if new subject.
  void AddSubject(string subject);
  // Name: ChooseSubject
  // Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
  // in m_subjects and allows use to choose one. Returns value - 1 (location in vector)
  // Precondition: A Subject exists.
  // Postcondition: Returns value entered minus one
  int ChooseSubject();
  // Name: QuestionsPerSubject
  // Desc: Iterates over m_questions and counts how many questions match the subject
  // passed into function
  // Precondition: A Subject exists.
  // Postcondition: Returns number of questions of a particular subject
  int QuestionsPerSubject(string subject);
  // Name: DisplayTitle
  // Desc: Displays opening Welcome message
  // Precondition: None.
  // Postcondition: Title is displayed.
  void DisplayTitle();
private:
  Lqueue<Question<T>* >* m_questions; // Holds questions using a specific data type
  vector<string> m_subjects; //Populated as file is loaded
};

//**********Implement Trivia Class Here***********
//Author:Ebun Oyemade
///Date: 5/4/22
//File: Trivia.cpp
//Email: eoyemad1@umbc.edu
//Desc: trivia handles all game functions using Lqueue and Questions


// Name: Default Constructor
// Desc: Displays the title, Loads Questions and calls menu
// Indicates if the file was not loaded.
// Precondition: None
// Postcondition: User is prompted with assignment menus
template <class T>
Trivia<T>::Trivia(string filename){
  DisplayTitle();
  LoadQuestions(filename);
  MainMenu();
}

// Name: Destructor
// Desc: Deallocates memory allocated for the Questions and
// resets all variables.
// Precondition: A Trivia exists.
// Postcondition: All dynamically allocated memory in Trivia is deleted.
template <class T>
Trivia<T>::~Trivia(){
  int size = m_questions -> GetSize();
  Question<T> *question;
  for(int i = 0; i < size; i++){
    question = m_questions -> At(i);
    delete question;
  }
 
  delete m_questions;
  question = nullptr;
  cout << "Thank you trying UMBC Trivia!" << endl;
}

// Name: LoadQuestions
// Desc: Each input file will be for a specific type of question (int, double, string)
//       Reads in Questions from a file and stores them in anLqueue.
//       An input file will be for exactly one type of question (int, double, string)
// Precondition: None.
// Postcondition: Returns true if file was read. Otherwise, it returns false.
template <class T>
bool Trivia<T>::LoadQuestions(string filename){
  fstream questionFile;
  string subject;
  string question;
  string datatype;
  string temp_difficulty;
  int difficulty;
  string temp_answer;
  T answer;
  m_questions = new Lqueue<Question<T>*>();// makes a new question object to intialize variables
  string trash;
  questionFile.open(filename);
  
  if(questionFile.is_open()){
    while((getline(questionFile, subject, DELIMITER)) && (getline(questionFile, question, DELIMITER)) && (getline(questionFile, datatype, DELIMITER)) && (getline(questionFile, temp_difficulty, DELIMITER)) && (questionFile >> answer) && (getline(questionFile, trash))){//reads in line
      difficulty = stoi(temp_difficulty);// turn string to int       
      Question<T> *question1 = new Question(subject,question,datatype,difficulty,answer);
      m_questions -> Push(question1);
      AddSubject(subject);
    }
    
  }else{
    cout << "file can not open" << endl;
  }
  questionFile.close();
  cout << "The questions have loaded" << endl;

  return true;
}

// Name: MainMenu
// Desc: Presents user with menu options for showing subjects and allowing
// user to work on a subject.
// Precondition: None.
// Postcondition: The main menu is presented.
template <class T>
void Trivia<T>::MainMenu(){
  int choice = 0;
  
  while(choice != 3){
    cout << "Choose an Option" << endl;
    cout << "1. Display Subjects" << endl;
    cout << "2. Start Subjects" << endl;
    cout << "3. Quit" << endl;
    cin >> choice;
    
    if(choice == 1){
      DisplaySubjects();
    }else if(choice == 2){
      StartSubject();
    }else if (choice != 3){
      cout << "Invalid input" << endl;
    }
  }
}

// Name: DisplaySubjects
// Desc: Presents all Subjects with corresponding numerical identifiers.
// Precondition: Subjects have been added.
// Postcondition: All assignments are printed to the screen.
template <class T>
void Trivia<T>::DisplaySubjects(){
  cout << "Possible Subjects:" << endl;
  int size = (int)m_subjects.size();
  
  for(int i = 0; i < size; i++){
    string subject = m_subjects[i];    
    cout << i + 1 << ". " << m_subjects[i] << endl;
  }
}

// Name: StartSubject
// Desc: Starts working on a selected Subject.
// Displays the number of questions in subject.
// Starts at beginning and goes through each question.
// After all questions have been answered:
//       displays total correct, incorrect, and percentage correct
// Precondition: m_questions has been populated
// Postcondition: Returns to main menu
template <class T>
void Trivia<T>::StartSubject(){
  int choice;
  int numQuestions;
  string subject;
  int count = 0;
  T answer;
  bool isRight;
  int numCorrect = 0;
  double percent;
  
  cout << "What subject would you like to attempt?" << endl;
  choice = ChooseSubject();
  subject = m_subjects.at(choice - 1);//subtracts 1 from choice to get the index
  numQuestions = QuestionsPerSubject(subject);
  cout << "There are " << numQuestions <<" questions in this subject." << endl;
  
  for(int i = 0; count < numQuestions; i++){//loops until all questions in a subject have been found
    Question<T> *question = m_questions -> At(i);//gets the question object at current index
    
    if(question -> m_subject == subject){//checks if the subject matches the current subject
      count++;
      cout << count << ". " << *question;
      cin >> answer;
      
      isRight = question -> CheckAnswer(answer);
      if(isRight){
	numCorrect += 1;// number correct answers
	cout << "Correct" << endl;

      }else{
	cout << "Incorrect" << endl;
      }
    }
  }
  
  percent =(double) numCorrect / numQuestions * 100;// + .5;
  cout << "You got " << numCorrect << " answers correct." << endl;
  cout << "You got " << numQuestions - numCorrect << " answers incorrect." << endl;
  cout << "Which is a " << percent << "%" << endl;//(int)percent
}

// Name: AddSubject
// Desc: Checks to see if a subject exists in m_subjects.
//       If not, inserts subject into m_subjects.
// Precondition: A Subject exists.
// Postcondition: Add subject to m_subjects if new subject.
template <class T>
void Trivia<T>::AddSubject(string subject){
  bool inList = false;
  
  for(unsigned int i = 0; i < m_subjects.size(); ++i){
    if(m_subjects.at(i) == subject){//checks to see if a given subject matches any that in m_subject
      inList = true;
    }
  }
  
  if((inList == false) || ((int)m_subjects.size() == 0)){//add subject if not in m_subject
    m_subjects.push_back(subject);
  }
}

// Name: ChooseSubject
// Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
// in m_subjects and allows use to choose one. Returns value - 1 (location in vector)
// Precondition: A Subject exists.
// Postcondition: Returns value entered minus one
template <class T>
int Trivia<T>::ChooseSubject(){
  int choice = 0;
  int size = (int)m_subjects.size();
  
  while((choice < 1)||(choice > size)){//loops until a valid number is entered
    cout << "Choose an option." << endl;
    DisplaySubjects();
    cin >> choice;
  }
  return choice;
}

// Name: QuestionsPerSubject
// Desc: Iterates over m_questions and counts how many questions match the subject
// passed into function
// Precondition: A Subject exists.
// Postcondition: Returns number of questions of a particular subject
template <class T>
int Trivia<T>::QuestionsPerSubject(string subject){
  int numQuestions = 0;
  int size = m_questions -> GetSize();
  
  for(int i = 0; i < size; i++){
    Question<T> *temp = m_questions -> At(i);//creates question object in order to obtain its subject
    string quest =  temp -> m_subject;
    
    if(quest == subject){//checks to see if a question's subject matches the given subject 
      numQuestions += 1;
    }
  }
  
  return numQuestions;
}

// Name: DisplayTitle
// Desc: Displays opening Welcome message
// Precondition: None.
// Postcondition: Title is displayed.
template <class T>
void Trivia<T>::DisplayTitle(){
  cout << "Welcome to UMBC Trivia" << endl;
}
#endif
