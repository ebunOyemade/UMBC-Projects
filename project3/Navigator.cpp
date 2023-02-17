/*****************************************
** File:    Navigator.cpp
** Project: CMSC 202 Project 3, Spring 2022
** Author:  Ebun Oyemade
** Date:    4/5/2002
** Section: 54
** E-mail:  eoyemad1@umbc.edu
**
** This file contains the driver program for Project 3.
** Navigator controls the actions in project 3 and displays 
** 
** 
** 
**
**
***********************************************/

#include "Navigator.h"
using namespace std;

// Name: Navigator (string) - Overloaded Constructor
// Desc: Creates a navigator object to manage routes
// Preconditions:  Provided with a filename of ports to load
// Postconditions: m_filename is populated with fileName
Navigator::Navigator(string fileName){
  m_fileName = fileName;
}

// Name: Navigator (destructor)
// Desc: Deallocates all dynamic aspects of a Navigator
// Preconditions: There is an existing Navigator
// Postconditions: All ports and routes are cleared
Navigator::~Navigator(){
  
  for(unsigned int i = 0; i < m_ports.size(); i++){
    delete m_ports.at(i);
  }
  
  for(unsigned int i = 0; i < m_routes.size(); i++){
    delete m_routes.at(i);
  }
  
  m_ports.clear();
  m_routes.clear();
  
  cout << "Routes removed from memory" << endl;
  cout << "Deleting Ports" << endl;
  cout << "Deleting Routes" << endl;
}

// Name: Start
// Desc: Loads the file and calls the main menu
// Preconditions: m_fileName is populated
// Postconditions: All ports are loaded and the main menu runs
void Navigator::Start(){
  ReadFile();  
  MainMenu();
}

// Name: DisplayPorts
// Desc: Displays each port in m_ports
// Preconditions: At least one port is in m_ports
// Postconditions: Displays all ports. Uses overloaded << provided in Port.h
void Navigator::DisplayPorts(){
   for(unsigned int i = 0; i < m_ports.size(); i++) {
     Port *port = m_ports.at(i);     
     cout << i + 1  << ". "; 
     cout << *port << endl;
    }
}

// Name: ReadFile
// Desc: Reads in a file that has data about each port including name, location, degrees
//       north and degrees west. Dynamically allocates ports and stores them in m_ports
//       The vector can hold many ports.
// Preconditions: Valid file name of ports
// Postconditions: Dynamically allocates each port and enters it into m_ports
void Navigator::ReadFile(){
  fstream portData;
  portData.open(m_fileName);
  const int FILESIZE = 36;
  string name;
  string location;
  string northTemp;
  string westTemp;
  double north;
  double west;

  if(portData.is_open()){
    for(int i = 0;i < FILESIZE; i++ ){// reads in lines from the text file
      getline(portData, name, ',');
      getline(portData, location, ',');
      getline(portData, northTemp, ',');
      getline(portData, westTemp);
   

      north = stod(northTemp);// converts string to double
      west = stod(westTemp);
      Port *port = new Port(name, location, north, west);
      m_ports.push_back(port);
    }

  }else{
    cout << "File can't Open" << endl;
  }
}

// Name: InsertNewRoute
// Desc: Dynamically allocates a new route with the user selecting each port in the route.
//       Route named based on the first and last port automatically
//       For example, Baltimore to Boston
//       Once route is created, inserted into m_routes.
// Preconditions: Populated m_routes
// Postconditions: Inserts a new route into m_routes
void Navigator::InsertNewRoute(){
  int portNum;
  Port *port;
  Route *route = new Route();
  const int LIMIT = -1;
			      
  cout << "Enter the number of the port to add to your Route: (-1 to end)" << endl;
  cin >> portNum;
 
  while(portNum != LIMIT){// adds ports until -1 is entered
    if((portNum <= (int)m_ports.size()) && (portNum > 0)){ //adds ports to the route if the index is valid
      port = m_ports.at(portNum - 1);
      string name = port -> GetName();
      string location = port -> GetLocation();
      double north = port -> GetNorth();
      double west = port -> GetWest();
      route -> InsertEnd(name, location, north, west);
      
    }else if(portNum != LIMIT){// input validation 
      cout << "invalid input" << endl;
    }

    if(portNum != LIMIT){
      cout << "Enter the number of the port to add to your Route: (-1 to end)" << endl;
      cin >> portNum;
    }
  }
  
  int size = route -> GetSize();
  
  if(size > 1){ // checks to see if route has at least 2 ports
    route -> UpdateName();
    m_routes.push_back(route);
  } else{
    cout << "Route too small" << endl;
  }
}

// Name: MainMenu
// Desc: Displays the main menu and manages exiting
// Preconditions: Populated m_ports
// Postconditions: Exits when someone chooses 5
void Navigator::MainMenu(){
  int choice = 0;
  const int TWO = 2;
  const int THREE = 3;
  const int FOUR = 4;
  const int FIVE = 5;

  while(choice != FIVE){ // runs/displays menu runs until 5 is Entered
    cout << "What would like to do?:" << endl;
    cout << "1. Create New Route" << endl;
    cout << "2. Display Route" << endl;
    cout << "3. Remove Port From Route" << endl;
    cout << "4. Reverse Route" << endl;
    cout << "5. Exit" << endl;
    cin >> choice;

    if(choice == 1){
      DisplayPorts();
      InsertNewRoute();
      
    }else if(choice == TWO){
      DisplayRoute();
      
    }else if(choice == THREE){
      if((int)m_routes.size() > 0){// checks to see if user has any routes
	RemovePortFromRoute();
      }else{
	cout << "add more routes" << endl;
      }
      
    }else if(choice == FOUR){
      if((int)m_routes.size() > 0){// checks if the user has any routes
	 ReverseRoute();
	 
      }else{	
	cout << "add more routes" << endl;
       }

    }else if(choice != FIVE){
      cout << "Invalid input pick a number 1-5" << endl;
    }
  }
}

// Name: ChooseRoute
// Desc: Allows user to choose a specific route to work with by displaying numbered list
// Preconditions: Populated m_routes
// Postconditions: Returns the index of the selected route minus 1
int Navigator::ChooseRoute(){
  int choice;
  
  cout << "Which route would you like to use?" << endl;
  
  for(unsigned int i = 0; i < m_routes.size(); i++ ) { // prints routes
    cout << i + 1 << ". " << m_routes[i] -> UpdateName() << endl;
  }
  
  cin >> choice;
  
  while((choice < (int)m_routes.size()) || (choice < 0)){ // validates input sees if enterd index is valid
    cout << "Invalid Input" << endl;
    cout << "Which route would you like to use?" << endl;
    
    for(unsigned int i = 0; i < m_routes.size(); i++) {
      cout << i << ". " << m_routes[i] -> UpdateName() << endl;
    }
    
    cin >> choice;
  }

  return choice - 1;//subtracts one so the index can plugged into an array 
}

// Name: DisplayRoute
// Desc: Using ChooseRoute, displays a numbered list of all routes.
//       If no routes, indicates that there are no routes to display
//       User selects a route from list to display
//       Displays numbered list of each port in route
//       Displays total miles of a route using RouteDistance
// Preconditions: Routes has more than one port
// Postconditions: Displays all ports in a route and the total miles of the route
void Navigator::DisplayRoute(){
  if((int)m_routes.size() > 0){// checks to if there are routes to display
    int routeNum = ChooseRoute();
    Route *route = m_routes.at(routeNum);
    route -> DisplayRoute();
    
    double distance = RouteDistance(route); // calculates distance
    cout << "The total miles of this route is "<< distance << " miles" << endl;
    
  } else{
    cout << "add more routes" << endl;

  }
}

// Name: RemovePortFromRoute()
// Desc: Using ChooseRoute, displays a numbered list of all routes.
//       User selects one of the routes to remove a port from.
//       Displays a numbered list of all ports in selected route.
//       User selects port to remove from list.
//       Removes port from route. If first or last port removed, updates name of route.
// Preconditions: Routes has more than one port
// Postconditions: Displays updated route with removed port and new name
void Navigator::RemovePortFromRoute(){
  int portNum;
  int routeNum = ChooseRoute();
  Route *route = m_routes.at(routeNum);
  
  route -> DisplayRoute();
  cout << "Which port would you like to remove?" << endl;
  cin >> portNum;
  
  while((portNum < 0)|| (portNum > route -> GetSize())){// validates input to see if a valid port was entered
    cout << "Invalid input" << endl;
    route -> DisplayRoute();
    cout << "Which port would you like to remove?" << endl;
    cin >> portNum;
  }

  int size = route -> GetSize();
  
  if(size > 2){// checks to see if the route has more than 2 ports
    route -> RemovePort(portNum);
    route -> DisplayRoute();
  }else{
    cout << "Route too small" << endl;
  }
}

// Name: RouteDistance
// Desc: Calculates the total distance of a route
//       Goes from port 1 to port 2 then port 2 to port 3 and repeats for
//       length of route. Calculates the distance using CalcDistance (provided)
//       Aggregates the total and returns the total in miles
// Preconditions: Populated route with more than one port
// Postconditions: Returns the total miles between all ports in a route
double Navigator::RouteDistance(Route* route){
  int i = 0;
  double distance = 0;
  Port *port1 = route -> GetData(i);//gets the first port in the route
  Port *port2 = port1 -> GetNext();//gets second port

  while(i < route -> GetSize() - 1){// loops until distance is calculated
    double north = port1 -> GetNorth();
    double west  = port1 -> GetWest();
    double north2 = port2 -> GetNorth();
    double west2 = port2 -> GetWest();

    distance += CalcDistance(north, west, north2, west2);// adds distance between 2 ports to total distance
    port1 = port2;
    port2 = port1 -> GetNext();

    i++;
  }
  
  return distance;
}

// Name: ReverseRoute
// Desc: Using ChooseRoute, users chooses route  and the route is reversed
//       If no routes in m_routes, indicates no routes available to reverse
//       Renames route based on new starting port and ending port
//       For example, Baltimore to Boston becomes Boston to Baltimore
// Preconditions: Populated m_routes
// Postconditions: Reverses a specific route by reversing the ports in place
//                 Must move ports, cannot just change data in ports.
void Navigator::ReverseRoute(){
  int routeNum = ChooseRoute();
  Route *route = m_routes.at(routeNum);
  
  route -> ReverseRoute();
  route -> UpdateName();
  cout << "Done reversing Route " << routeNum + 1  << endl;
  route -> DisplayRoute();
}
