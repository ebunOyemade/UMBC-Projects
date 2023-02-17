//UMBC - CSEE - CMSC 341 - Fall 2022 - Proj1
#include "railroad.h"

class Tester{ // Tester class to implement test functions
    public:

    /**************************************
    * Test function declarations go here! *
    **************************************/
};

int main(){
    Railroad aNetwork;
    for (int i=1;i<10;i++)
        aNetwork.extendAtTail(i,i*2);
    cout << "Create a route [(2,NORTH),(5,SOUTH),(8,NONE)]\n\n";
    list<pair<int,DIRECTION>> aRoute;
    aRoute.push_back(pair<int,DIRECTION>(2,NORTH));
    aRoute.push_back(pair<int,DIRECTION>(5,SOUTH));
    aRoute.push_back(pair<int,DIRECTION>(8,NONE));
    aNetwork.makeRoute(aRoute);
    cout << "Total travellers: " << aNetwork.travel(aRoute) << endl;
    cout << "\nDump of the list:\n\n";
    aNetwork.dump();
    cout << "\n\nRemove node 5.\n\n";
    aNetwork.removeStation(5);
    cout << "Removing node 5 invalidates the route passing through 5.\n\n";
    cout << "Total travellers: " << aNetwork.travel(aRoute) << endl;
    cout << "\nDump of the list:\n\n";
    aNetwork.dump();
    return 0;
}
