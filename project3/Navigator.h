//Name: Navigator.h
//Project: CMSC 202 Project 3, Spring 2022
//Author:  Jeremy Dixon
//Date:   3/10/2022
//Desc: This file contains the header details for the Navigator class

#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "Port.h"
#include "Route.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

//Constants used for calculating distance
#define PI 3.14159265358979323846
#define EARTH_RADIUS 3958.8 //in miles
#define DEG_2_RAD PI / 180
#define RAD_2_DEG 180 / PI

class Navigator {
 public:
  // Name: Navigator (string) - Overloaded Constructor
  // Desc: Creates a navigator object to manage routes
  // Preconditions:  Provided with a filename of ports to load
  // Postconditions: m_filename is populated with fileName
  Navigator(string fileName);
  // Name: Navigator (destructor)
  // Desc: Deallocates all dynamic aspects of a Navigator
  // Preconditions: There is an existing Navigator
  // Postconditions: All ports and routes are cleared
  ~Navigator();
  // Name: Start
  // Desc: Loads the file and calls the main menu
  // Preconditions: m_fileName is populated
  // Postconditions: All ports are loaded and the main menu runs
  void Start();
  // Name: DisplayPorts
  // Desc: Displays each port in m_ports
  // Preconditions: At least one port is in m_ports
  // Postconditions: Displays all ports. Uses overloaded << provided in Port.h
  void DisplayPorts();
  // Name: ReadFile
  // Desc: Reads in a file that has data about each port including name, location, degrees
  //       north and degrees west. Dynamically allocates ports and stores them in m_ports
  //       The vector can hold many ports.
  // Preconditions: Valid file name of ports
  // Postconditions: Dynamically allocates each port and enters it into m_ports
  void ReadFile();
  // Name: InsertNewRoute
  // Desc: Dynamically allocates a new route with the user selecting each port in the route.
  //       Route named based on the first and last port automatically
  //       For example, Baltimore to Boston
  //       Once route is created, inserted into m_routes.
  // Preconditions: Populated m_routes
  // Postconditions: Inserts a new route into m_routes
  void InsertNewRoute();
  // Name: MainMenu
  // Desc: Displays the main menu and manages exiting
  // Preconditions: Populated m_ports
  // Postconditions: Exits when someone chooses 5
  void MainMenu();
  // Name: ChooseRoute
  // Desc: Allows user to choose a specific route to work with by displaying numbered list
  // Preconditions: Populated m_routes
  // Postconditions: Returns the index of the selected route minus 1
  int ChooseRoute();
  // Name: DisplayRoute
  // Desc: Using ChooseRoute, displays a numbered list of all routes.
  //       If no routes, indicates that there are no routes to display
  //       User selects a route from list to display
  //       Displays numbered list of each port in route
  //       Displays total miles of a route using RouteDistance
  // Preconditions: Routes has more than one port
  // Postconditions: Displays all ports in a route and the total miles of the route
  void DisplayRoute();
  // Name: RemovePortFromRoute()
  // Desc: Using ChooseRoute, displays a numbered list of all routes.
  //       User selects one of the routes to remove a port from.
  //       Displays a numbered list of all ports in selected route.
  //       User selects port to remove from list.
  //       Removes port from route. If first or last port removed, updates name of route.
  // Preconditions: Routes has more than one port
  // Postconditions: Displays updated route with removed port and new name
  void RemovePortFromRoute();
  // Name: RouteDistance
  // Desc: Calculates the total distance of a route
  //       Goes from port 1 to port 2 then port 2 to port 3 and repeats for
  //       length of route. Calculates the distance using CalcDistance (provided)
  //       Aggregates the total and returns the total in miles
  // Preconditions: Populated route with more than one port
  // Postconditions: Returns the total miles between all ports in a route
  double RouteDistance(Route*);
  // Name: ReverseRoute
  // Desc: Using ChooseRoute, users chooses route  and the route is reversed
  //       If no routes in m_routes, indicates no routes available to reverse
  //       Renames route based on new starting port and ending port
  //       For example, Baltimore to Boston becomes Boston to Baltimore
  // Preconditions: Populated m_routes
  // Postconditions: Reverses a specific route by reversing the ports in place
  //                 Must move ports, cannot just change data in ports.
  void ReverseRoute();
  // Name:  CalcDistance (provided - DO NOT EDIT)
  // Desc: Calculates the distance between two ports by using their coordinates
  //       Takes in port1 latitude (North), Port1 Longitude (West)
  //       Takes in port2 latitude (North), Port2 longitude (West)
  // Preconditions: Requires two ports with their N (in degrees) and W (in degrees)
  // Postconditions: Returns distance in miles between two ports
  double CalcDistance(double port1_north, double port1_west,
				 double port2_north, double port2_west) {
    double lat_new = port2_north * DEG_2_RAD;
    double lat_old = port1_north * DEG_2_RAD;
    double lat_diff = (port1_north-port2_north) * DEG_2_RAD;
    double lng_diff = (port1_west-port2_west) * DEG_2_RAD;

    double a = sin(lat_diff/2) * sin(lat_diff/2) +
      cos(lat_new) * cos(lat_old) *
      sin(lng_diff/2) * sin(lng_diff/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return double(EARTH_RADIUS) * c;
  }
private:
  vector<Port*> m_ports; //Vector of all ports
  vector<Route*> m_routes; //Vector of all routes
  string m_fileName; //File to read in
};

#endif
