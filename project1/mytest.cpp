#include "railroad.h"

class Tester{				// Tester class to implement test functions
public:

    /**************************************
    * Test function declarations go here! *
    **************************************/
    bool extendAtTailTest();//tests extendAtTail
    bool extendAtHeadTest();//tests extendAtHead
    bool removeStationTest();//tests removeStation
    bool assignmentOperatorTest();//tests the assignment operator
    bool copyConstructorTest();//tests the copy constructor
    bool makeRouteTest();//tests makeRoute
    bool travelTest();//tests travel
    bool setNumPassengersTest();//tests setNumPassengers
    const char* FAIL_STATEMENT = "*****TEST FAILED: ";//test failed constant
    const char* PASS_STATEMENT = "     TEST PASSED: ";//test passed constant
    const int LIMIT = 301;//number of Stations default
    const int TWO = 2;
    const int THREE = 3;
    const int FOUR = 4;
};

int main (){
    Railroad aNetwork;
    for(int i = 1; i < 10; i++)
        aNetwork.extendAtTail(i, i * 2);
    cout << "Create a route [(2,NORTH),(5,SOUTH),(8,NONE)]\n\n";
    list<pair<int,DIRECTION>>aRoute;
    aRoute.push_back(pair<int,DIRECTION>(2,NORTH));
    aRoute.push_back(pair<int, DIRECTION>(5,SOUTH));
    aRoute.push_back(pair<int,DIRECTION>(8,EAST));
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
    Tester test;
    test.extendAtTailTest();
    test.extendAtHeadTest();
    test.removeStationTest();
    test.assignmentOperatorTest();
    test.copyConstructorTest();
    test.makeRouteTest();
    test.travelTest();
    test.setNumPassengersTest();
    return 0;
}

bool Tester::extendAtTailTest(){
    Railroad aNetwork;
    bool errorTest;
    bool normalTest = true;
    int count = 1;
    
    while(count < LIMIT && normalTest != false){
        normalTest = aNetwork.extendAtTail(count,count);
        count += 1;
    }
    
    if(normalTest != true){//checks if stations were added correctly
        cout << FAIL_STATEMENT << "extendAtTail() normal case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "extendAtTail() normal case" << endl;
    }
    
    errorTest = aNetwork.extendAtTail(0,DEFNUMPASS);
    if(errorTest != false){//checks a code less than 1 returns false
        cout << FAIL_STATEMENT << "extendAtTail() error case-invalid code" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "extendAtTail() error case-invalid code" << endl;
    }
    return true;
}

bool Tester::extendAtHeadTest(){
    Railroad aNetwork;
    bool errorTest;
    bool normalTest = true;
    int count = 1;
    
    while(count < LIMIT && normalTest != false){
        normalTest = aNetwork.extendAtHead(count,count);
        count += 1;
    }
    
    if(normalTest != true){//checks if stations were added correctly
        cout << FAIL_STATEMENT << "extendAtHead() normal case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "extendAtHead() normal case" << endl;
    }
    
    errorTest = aNetwork.extendAtHead(0,DEFNUMPASS);
    if(errorTest != false){//checks a Code less than 1 returns false
        cout << FAIL_STATEMENT << "extendAtHead() error case-invalid code" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "extendAtHead() error case-invalid code" << endl;
    }
    return true;
}

bool Tester::removeStationTest(){
    Railroad aNetwork;
    Railroad bNetwork;
    bool errorTest = true;
    bool normalTest = true;
    bool noNodeTest = true;
    
    for(int i = 1; i < LIMIT; i++){
        aNetwork.extendAtTail(i,i);
        bNetwork.extendAtTail(i,i);
    }
    
    int count = 1;
    while(count < LIMIT - 1 && normalTest != false){
        normalTest = aNetwork.removeStation(count);
        count += 1;
    }
    
    if(normalTest != true){//checks stations were removed correctly
        cout << FAIL_STATEMENT << "removeStation() normal case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "removeStation() normal case" << endl;
    }
    
    errorTest = bNetwork.removeStation(LIMIT);
    if(errorTest != false){//checks if false is returned when invalid code is given
        cout << FAIL_STATEMENT << "removeStation() error case-invalid code" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "removeStation() error case-invalid code" << endl;
    }
    
    noNodeTest = aNetwork.removeStation(1);
    if(noNodeTest != false){//checks if false is returned when removeStation is used on empty list
        cout << FAIL_STATEMENT << "removeStation() on empty List" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "removeStation() on empty List" << endl;
    }
    return true;
}

bool Tester::assignmentOperatorTest(){
    Railroad aNetwork;
    Railroad bNetwork;
    Railroad cNetwork;
    bool edgeTest = true;
    bool normalTest = true;
    
    for(int i = 1; i < LIMIT; i++){
        aNetwork.extendAtTail(i,i);
    }
    
    bNetwork = aNetwork;
    Station *temp = aNetwork.m_head;
    Station *curr = bNetwork.m_head;
    
    while(curr != nullptr && normalTest != false){//if linked lists have different memory addresses
        if(&temp == &curr){
            normalTest = false;
        }
        curr = curr->m_next;
        temp = temp->m_next;
    }
    
    if(normalTest != true){//checks if list was copied
        cout << FAIL_STATEMENT << "assignment Operator normal case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "assignment Operator normal case" << endl;
    }
    
    aNetwork = cNetwork;
    temp = cNetwork.m_head;
    curr = aNetwork.m_head;
    
    if(&curr == &temp){
        edgeTest = false;
    }
    
    if(edgeTest != true){//checks if empty list was copied
        cout << FAIL_STATEMENT << "assignment Operator edge case-(empty railroad)" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "assignment Operator edge case-(empty railroad)" << endl;
    }
    
    return true;
}

bool Tester::copyConstructorTest (){
    Railroad aNetwork;
    Railroad bNetwork;
    Railroad cNetwork;
    bool edgeTest = true;
    bool normalTest = true;
    
    for(int i = 1; i < LIMIT; i++){
        aNetwork.extendAtTail(i,i);
    }
    
    bNetwork = Railroad(aNetwork);
    Station *temp = aNetwork.m_head;
    Station *curr = bNetwork.m_head;
    
    while(curr != nullptr && normalTest != false){//if linked lists have different memory addresses
        if(&temp == &curr){
            normalTest = false;
        }
        curr = curr->m_next;
        temp = temp->m_next;
    }
    
    if(normalTest != true){//checks if list was copied
        cout << FAIL_STATEMENT << "copy Constructor normal case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "copy Constructor normal case" << endl;
    }
    
    aNetwork = Railroad(cNetwork);
    temp = cNetwork.m_head;
    curr = aNetwork.m_head;
    if(&curr == &temp){//if linked lists have different memory addresses
        edgeTest = false;
    }
    
    if(edgeTest != true){//checks if empty list was copied
        cout << FAIL_STATEMENT << "copy constructor edge case-empty railroad" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "copy constructor edge case-empty railroad" << endl;
    }
    return true;
}

bool Tester::makeRouteTest(){
    Railroad aNetwork;
    list<pair<int,DIRECTION>>aRoute;
    list<pair<int,DIRECTION>>bRoute;
    list<pair<int,DIRECTION>>cRoute;
    bool normalTest;
    bool overrideTest;
    bool missingLinkTest;
    
    for(int i = 1; i < LIMIT; i++){
        aNetwork.extendAtTail(i,i);
    }
    
    aRoute.push_back(pair<int,DIRECTION>(1,NORTH));
    aRoute.push_back(pair<int,DIRECTION>(TWO,EAST));
    aRoute.push_back(pair<int,DIRECTION>(THREE,SOUTH));
    aRoute.push_back(pair<int,DIRECTION>(FOUR,WEST));
    normalTest = aNetwork.makeRoute(aRoute);
    
    if(normalTest != true){//checks if route copyed
        cout << FAIL_STATEMENT << "makeRoute() normal case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "makeRoute normal case" << endl;
    }
    
    bRoute.push_back(pair<int,DIRECTION>(LIMIT,NORTH));
    bRoute.push_back(pair<int,DIRECTION>(TWO,EAST));
    bRoute.push_back(pair<int,DIRECTION>(THREE,SOUTH));
    bRoute.push_back(pair<int,DIRECTION>(FOUR,WEST));
    
    missingLinkTest = aNetwork.makeRoute(bRoute);
    if(missingLinkTest != false){//tests if false is returned when given list w/ invalid first element
        cout << FAIL_STATEMENT << "makeRoute() error case-invalid code" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "makeRoute() error case-invalid code" << endl;
    }
    
    cRoute.push_back(pair<int,DIRECTION>(1,WEST));
    cRoute.push_back(pair<int,DIRECTION>(TWO,EAST));
    cRoute.push_back(pair<int,DIRECTION>(THREE,SOUTH));
    cRoute.push_back(pair<int,DIRECTION>(FOUR,WEST));
    
    overrideTest = aNetwork.makeRoute(cRoute);
    if(overrideTest != false){//checks if false is returned if a route would another route
        cout << FAIL_STATEMENT << "makeRoute() error case-override route" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "makeRoute() error case-override route" << endl;
    }
    return true;
}

bool Tester::travelTest(){
    Railroad aNetwork;
    list<pair<int,DIRECTION>>aRoute;
    list<pair<int,DIRECTION>>bRoute;
    int errorTest = 0;
    int normalTest = 0;
    
    for(int i = 1; i < LIMIT; i++){
        aNetwork.extendAtTail(i,i);
    }
    
    aRoute.push_back(pair<int,DIRECTION>(1,NORTH));
    aRoute.push_back(pair<int,DIRECTION>(TWO,EAST));
    aRoute.push_back(pair<int,DIRECTION>(THREE,SOUTH));
    aRoute.push_back(pair<int,DIRECTION>(FOUR,WEST));
    aNetwork.makeRoute(aRoute);
    
    normalTest = aNetwork.travel(aRoute);
    if(normalTest != DEFNUMPASS){//tests if travel() returns right value
        cout << FAIL_STATEMENT << "travel() normal case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "travel() normal case" << endl;
    }
    
    bRoute.push_back(pair<int,DIRECTION>(LIMIT,NORTH));
    bRoute.push_back(pair<int,DIRECTION>(TWO,EAST));
    bRoute.push_back(pair<int,DIRECTION>(THREE,SOUTH));
    bRoute.push_back(pair<int,DIRECTION>(FOUR,WEST));
    aNetwork.makeRoute(bRoute);
    
    errorTest = aNetwork.travel(bRoute);
    if(errorTest != -1){//tests if travel() returns -1 when given invalid list
        cout << FAIL_STATEMENT << "travel error case-invalid code" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "travel error case-invalid code" << endl;
    }
    return true;
}

bool Tester::setNumPassengersTest(){
    Railroad aNetwork;
    int errorTest = 0;
    int normalTest = 0;
    
    for(int i = 1; i < LIMIT; i++){
        aNetwork.extendAtTail(i,i);
    }
    
    normalTest = aNetwork.setNumPassengers(1,DEFNUMPASS);
    if(normalTest != true){//tests if setNumPassengers() sets passengers to DEFNUMPASS
        cout << FAIL_STATEMENT << "setNumPassengers() normal case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "setNumPassengers() normal case" << endl;
    }

    errorTest = aNetwork.setNumPassengers(LIMIT,DEFNUMPASS);
    if(errorTest != false){//checks if false is returned when invalid code is given
        cout << FAIL_STATEMENT << "setNumPassengers() error case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "setNumPassengers() error case-invalid code" << endl;
    }

    return true;
}
