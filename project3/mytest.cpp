// CMSC 341 - Fall 2022 - Project 4
#include "cache.h"
#include <random>
#include <vector>
const int MINSEARCH = 0;
const int MAXSEARCH = 7;
// the following array defines sample search strings for testing
string searchStr[MAXSEARCH+1]={"c++","python","java","scheme","prolog","c#","c","js"};
enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }
    
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};

class Tester{
    public:
    bool insertionTest();
    bool getPersonTest();
    bool removeTest();
    bool loadFactorTest();
    bool deleteRatioTest();
    const char* FAIL_STATEMENT = "*****TEST FAILED: ";
    const char* PASS_STATEMENT = "     TEST PASSED: ";
};

unsigned int hashCode(const string str);

int main(){
    
    vector<Person> dataList;
    Random RndID(MINID,MAXID);
    Random RndStr(MINSEARCH,MAXSEARCH);
    Cache cache(MINPRIME, hashCode);
    bool result = true;
    for (int i=0;i<49;i++){
        // generating random data
        Person dataObj = Person(searchStr[RndStr.getRandNum()], RndID.getRandNum());
        // saving data for later use
        dataList.push_back(dataObj);
        // inserting data in to the Cache object
        cache.insert(dataObj);
    }
    // dumping the data points to the standard output
    cache.dump();
    // checking whether all data are inserted
    for (vector<Person>::iterator it = dataList.begin(); it != dataList.end(); it++){
        result = result && (*it == cache.getPerson((*it).getKey(), (*it).getID()));
    }
    if (result)
        cout << "All data points exist in the Cache object!\n";
    else
        cout << "Some data points are missing in the Cache object\n";
        
    Tester test;
    
    test.insertionTest();//tests insertion
    test.getPersonTest();//tests getPerson
    test.removeTest();//tests remove
    test.loadFactorTest();//tests rehashing case for insertion
    test.deleteRatioTest();//tests rehashing case for deletion
    return 0;
}

unsigned int hashCode(const string str) {
   unsigned int val = 0 ;
   const unsigned int thirtyThree = 33 ;  // magic number from textbook
   for ( unsigned int i = 0 ; i < str.length(); i++)
      val = val * thirtyThree + str[i] ;
   return val ;
}

bool Tester::insertionTest(){
    vector<Person> dataList;
    Random RndID(MINID,MAXID);
    Random RndStr(MINSEARCH,MAXSEARCH);
    Cache cache(MINPRIME, hashCode);

    for (int i=0;i<5;i++){//loops through none colliding table
        Person dataObj = Person(searchStr[RndStr.getRandNum()], RndID.getRandNum());
        dataList.push_back(dataObj);
        cache.insert(dataObj);
        if(!(cache.m_currentTable[hashCode(dataObj.getKey())%MINPRIME] == dataObj)){//checks data is stored in right bukets
            cout << FAIL_STATEMENT << "insertion test" << endl;
            return false;
        }
        
    }
    if(cache.lambda() * MINPRIME != 5){ //checks for the correct amount of elements
        cout << FAIL_STATEMENT << "insertion test" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "insertion test" << endl;
        return true;
    }
    
}
bool Tester::getPersonTest(){
    vector<Person> dataList;
    Random RndID(MINID,MAXID);
    Random RndStr(MINSEARCH,MAXSEARCH);
    Cache cache(MINPRIME, hashCode);
    int id = 0;
    string key = "";
    Person check = cache.getPerson(searchStr[RndStr.getRandNum()], RndID.getRandNum());
    
    if(!(check == EMPTY)){//checks for when node is not in table
        cout << FAIL_STATEMENT << "getPerson() error case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "getPerson() error case" << endl;
    }
    
    for (int i=0;i<5;i++){//checks for a none colliding case
        Person dataObj = Person(searchStr[RndStr.getRandNum()], RndID.getRandNum());
        dataList.push_back(dataObj);
        cache.insert(dataObj);
        if(i == 5){
            check = dataObj;
            key = check.getKey();
            id = check.getID();
        }
    }
    
    Person target = cache.getPerson(key,id);
    if(!(check == target)){
        cout << FAIL_STATEMENT << "getPerson() normal (no collisions) case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "getPerson() normal (no collisions) case" << endl;
    }
    
    for (int i=0;i<43;i++){
        Person dataObj = Person(searchStr[RndStr.getRandNum()], RndID.getRandNum());
        dataList.push_back(dataObj);
        cache.insert(dataObj);
        if(i == 5){
            check = dataObj;
            key = check.getKey();
            id = check.getID();
        }
    }
    
    target = cache.getPerson(key,id);
    if(!(check == target)){//checks for colliding case
        cout << FAIL_STATEMENT << "getPerson() normal (collisions) case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "getPerson() normal (collisions) case" << endl;
        return true;
    }
    
}
bool Tester::removeTest(){
    vector<Person> dataList;
    Random RndID(MINID,MAXID);
    Random RndStr(MINSEARCH,MAXSEARCH);
    Cache cache(MINPRIME, hashCode);
    Person check;
    int id = 0;
    string key = "";
    
    for (int i=0;i<5;i++){//checks for none colliding case
        Person dataObj = Person(searchStr[RndStr.getRandNum()], RndID.getRandNum());
        dataList.push_back(dataObj);
        cache.insert(dataObj);
        if(i == 5){
            check = dataObj;
            key = check.getKey();
            id = check.getID();
            cache.remove(dataObj);
        }
    }
    
    if(!(cache.getPerson(key,id) == EMPTY)){//checks if node has been removed
        cout << FAIL_STATEMENT << "remove test (no collisions)" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "remove test (no collisions)" << endl;
    }
    
    for (int i=0;i<43;i++){//checks for colliding case
        Person dataObj = Person(searchStr[RndStr.getRandNum()], RndID.getRandNum());
        dataList.push_back(dataObj);
        cache.insert(dataObj);
        if(i == 5){
            check = dataObj;
            key = check.getKey();
            id = check.getID();
            cache.remove(dataObj);
        }
    }
    if(!(cache.getPerson(key,id) == EMPTY)){
        cout << FAIL_STATEMENT << "remove test (collisions)" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "remove test (collisions)" << endl;
        return true;
    }
}
bool Tester::loadFactorTest(){
    vector<Person> dataList;
    Random RndID(MINID,MAXID);
    Random RndStr(MINSEARCH,MAXSEARCH);
    Cache cache(MINPRIME, hashCode);
    bool result = true;
    
    for (int i=0;i<51;i++){
        Person dataObj = Person(searchStr[RndStr.getRandNum()], RndID.getRandNum());
        dataList.push_back(dataObj);
        cache.insert(dataObj);
    }
    for (vector<Person>::iterator it = dataList.begin(); it != dataList.end(); it++){
        result = result && (*it == cache.getPerson((*it).getKey(), (*it).getID()));
    }
    
    if(cache.m_currentSize != floor(cache.m_oldSize/4)){//checks to see if the correct amount of nodes are in new table
        cout << FAIL_STATEMENT << "load factor rehash trigger test" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "load factor rehash trigger test" << endl;
    }
    
    if(!(result)){//checks to see if all nodes where transfered
        cout << FAIL_STATEMENT << "load factor nodes copied rehash test" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "load factor nodes copied rehash test" << endl;
        return true;
    }
}
bool Tester::deleteRatioTest(){
    vector<Person> dataList;//stores nodes that are to be deleted
    vector<Person> dataList2;//stores nodes that remain
    Random RndID(MINID,MAXID);
    Random RndStr(MINSEARCH,MAXSEARCH);
    Cache cache(MINPRIME, hashCode);
    Person check;
    bool result = true;
    
    for (int i=0;i<50;i++){
        Person dataObj = Person(searchStr[RndStr.getRandNum()], RndID.getRandNum());
        
        cache.insert(dataObj);
        if(i < 42){
            check = dataObj;
            dataList.push_back(dataObj);
        }else{
            dataList2.push_back(dataObj);
        }
    }
    
    for(vector<Person>::iterator it = dataList.begin(); it != dataList.end(); it++){
        cache.remove(*it);
    }

    for (vector<Person>::iterator it = dataList2.begin(); it != dataList2.end(); it++){
        result = result && (*it == cache.getPerson((*it).getKey(), (*it).getID()));
    }
    
    if(cache.m_currentSize != 9 || cache.m_oldSize != 0){//checks if new has right amount of nodes and old table was deleted
        cout << FAIL_STATEMENT << "delete ratio rehash trigger test" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "delete ratio rehash trigger test" << endl;
    }
    
    if(!(result)){//checks if the correct amount was deleted
        cout << FAIL_STATEMENT << "delete ratio nodes copied rehash test" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "delete ratio nodes copied rehash test" << endl;
        return true;
    }
    
    
}
