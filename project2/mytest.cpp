// UMBC - CMSC 341 - Fall 2022 - Proj2
#include "streak.h"
#include <vector>
#include <random>
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
    /******************************************
    * Test function declarations go here! *
    ******************************************/
    const char* FAIL_STATEMENT = "*****TEST FAILED: ";
    const char* PASS_STATEMENT = "     TEST PASSED: ";
    bool testInsertion();//tests insertion
    bool testDeletion();//tests deletion
    bool testCountTigerCubs();//tests countTigerCubs
    bool testRemoveDead();//tests removeDead
    bool testInsertionPerformance();//tests insertion time
    bool testDeletionPerformance();//tests deletion time
    bool testBSTProperty(Tiger * aTiger);//tests weather bst is preserved
};

int main(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    {
        Streak streak;
        int streakSize = 10;
        int tempID = 0;
        int ID = 0;
        for(int i=0;i<streakSize;i++){
            ID = idGen.getRandNum();
            cout << ID <<endl;
            if (i == streakSize / 2) tempID = ID;//we store this ID for later use
            Tiger tiger(ID,
                        static_cast<AGE>(ageGen.getRandNum()),
                        static_cast<GENDER>(genderGen.getRandNum()));
            streak.insert(tiger);
        }
    
        cout << "\nDump after inserting " << streakSize << " nodes:\n\n";
        streak.dumpTree();
        cout << "\n\nList of Tigers after inserting " << streakSize << " nodes:\n";
        streak.listTigers();
        cout << endl;
        
        streak.remove(tempID);
        cout << "\nDump after removig the node with ID: " << tempID << "\n\n";
        streak.dumpTree();
        cout << "\n\nList of Tigers after removing the node with ID: " << tempID << "\n";
        streak.listTigers();
        cout << endl;
        Tester test;
        test.testInsertion();
        test.testRemoveDead();
        test.testCountTigerCubs();
        test.testDeletion();
        test.testInsertionPerformance();
        test.testDeletionPerformance();
        
    }
    
    return 0;
}
bool Tester::testInsertion(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    
    Streak streak;
    int streakSize = 300;
    int ID = 0;
    int balanceFactor;
    for(int i=0;i<streakSize;i++){
        ID = idGen.getRandNum();
        Tiger tiger(ID,
                    static_cast<AGE>(0),//age to CUB to test count number nodes
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    }
    
    if(streak.countTigerCubs() != streakSize){//checks if 300 nodes where inserted
        cout << FAIL_STATEMENT << "insertion normal case" << endl;
            return false;
    }else{
        cout << PASS_STATEMENT << "insertion normal case" << endl;
    }
    
    bool isBST = testBSTProperty(streak.m_root);
    if(!isBST){//tests if BST was preserved
        cout << FAIL_STATEMENT << "insert BST Property maintained" <<endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "insert BST Property maintained" <<endl;
    }
    
    balanceFactor = streak.checkImbalance(streak.m_root);//checks to see if tree is balanced
    if(balanceFactor > 1 || balanceFactor < -1){
        cout << FAIL_STATEMENT << "balanced after insertion test" <<endl;
        cout << balanceFactor << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "balanced after insertion test" <<endl;
        cout << balanceFactor << endl;
    }
    
    Tiger aTiger(MINID,
                static_cast<AGE>(ageGen.getRandNum()),
                static_cast<GENDER>(genderGen.getRandNum()));
    streak.insert(aTiger);
    
    if(!streak.findTiger(MINID)){//checks if edge case is still inserted
        cout << FAIL_STATEMENT << "insertion edge case" <<endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "insertion edge case" <<endl;
    }
    
    Tiger bTiger(0,
                static_cast<AGE>(ageGen.getRandNum()),
                static_cast<GENDER>(genderGen.getRandNum()));
    streak.insert(aTiger);
    
    if(streak.findTiger(0)){//checks that invalid node is not inserted
        cout << FAIL_STATEMENT << "insertion error case" <<endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "insertion error case" <<endl;
    }
    return true;
}

bool Tester::testDeletion(){
    
    Random idGen(MINID,MAXID);
    Random idGen2(MINID,MAXID);
    Random genderGen(0,2);
    Streak streak;
    int streakSize = 300;
    int tempID = 0;
    int ID = 0;
    for(int i=0;i<streakSize;i++){
        ID = idGen.getRandNum();
        Tiger tiger(ID,
                    static_cast<AGE>(0),//set CUB to count numbe rof nodes
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    }
    
    for(int i=0;i<streakSize/2;i++){
        ID = idGen2.getRandNum();
        streak.remove(ID);
    }
    
    if(streak.countTigerCubs() != streakSize/2){//checks 150 were deleted
        cout << FAIL_STATEMENT << "remove normal case" <<endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "remove normal case" <<endl;
    }
    
    bool isBST = testBSTProperty(streak.m_root);
    if(!isBST){//checks if bst is maintained
        cout << FAIL_STATEMENT << "remove BST Property maintained" <<endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "remove BST Property maintained" <<endl;
    }
    
    Streak streak2;
    streak2.insert(tempID);
    streak2.remove(tempID);
     if(streak2.m_root != nullptr){//checks if edge case does not cause errors
        cout << FAIL_STATEMENT << "remove edge case" <<endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "remove edge case" <<endl;
        return true;
    }
    
}

bool Tester::testCountTigerCubs(){
    Random idGen(MINID,MAXID);
    Random genderGen(0,2);
    Streak streak;
    int streakSize = 300;
    int ID = 0;
    
    for(int i=0;i<streakSize;i++){
        ID = idGen.getRandNum();
        Tiger tiger(ID,
                    static_cast<AGE>(0),
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    }
    
    if(streak.countTigerCubs() != streakSize){//checks to see if countTigerCubs returns correct number
        cout << FAIL_STATEMENT << "countTigerCubs functionality" <<endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "countTigerCubs functionality" <<endl;
        return true;
    }
}

bool Tester::testRemoveDead(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    Streak streak;
    int streakSize = 10;
    int tempID = 0;
    int ID = 0;
    for(int i=0;i<streakSize;i++){
        ID = idGen.getRandNum();
        if (i == streakSize / 2) tempID = ID;//we store this ID for later use
        Tiger tiger(ID,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    }
    streak.setState(tempID,DEAD);//sets one node to Dead
    streak.removeDead();
     if(streak.findTiger(tempID)){//checks to see if node has been removed
        cout << FAIL_STATEMENT << "removeDead functionality" <<endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "removeDead functionality" <<endl;
        return true;
    }
    
}

bool Tester::testInsertionPerformance(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    
    Streak streak;
    Streak streak2;
    int streakSize = 1000;
    int ID = 0;
    clock_t start = clock();
    for(int i=0;i<streakSize;i++){
        ID = idGen.getRandNum();
        Tiger tiger(ID,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak2.insert(tiger);
    }
    clock_t a = clock() - start;
    
    clock_t start2 = clock();
    for(int i=0;i<streakSize*2;i++){
        ID = idGen.getRandNum();

        Tiger tiger(ID,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        
        streak.insert(tiger);
    }
    clock_t b = clock() - start2;
    
    double ratio = (double)b/(2*a);
    if(ratio > 1.5 || ratio < .7){//checks if insertion is O(logn)
        cout << FAIL_STATEMENT << "insertion O(log(n))" << endl;
        cout << "1000 insertions is " << a << " clock ticks" << endl;
        cout << "2000 insertions is " << b << " clock ticks" << endl;
        cout << "insertion ratio: " << ratio << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "insertion O(log(n))" << endl;
        cout << "1000 insertions is " << a << " clock ticks" << endl;
        cout << "2000 insertions is " << b << " clock ticks" << endl;
        cout << "insertion ratio: " << ratio << endl;
        return true;
    }
}

bool Tester::testDeletionPerformance(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    
    Streak streak;
    Streak streak2;
    int streakSize = 1000;
    int ID = 0;
    for(int i=0;i<streakSize;i++){
        ID = idGen.getRandNum();
        Tiger tiger(ID,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    }
    for(int i=0;i<streakSize * 2;i++){
        ID = idGen.getRandNum();
        Tiger tiger(ID,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        
        streak2.insert(tiger);
    }
    
    clock_t start = clock();
    for(int i=0;i<streakSize;i++){
        ID = idGen.getRandNum();
        streak.remove(ID);
    }
    clock_t a = clock() - start;
    
    clock_t start2 = clock();
    for(int i=0;i<streakSize*2;i++){
        ID = idGen.getRandNum();
        streak.remove(ID);
    }
    clock_t b = clock() - start2;
    
    double ratio = (double)b/(2*a);
    if(ratio > 1.5 || ratio < .7){//checks if deletion is O(logn)
        cout << FAIL_STATEMENT << "deletion O(log(n))" <<endl;
        cout << "1000 deletions is " << a << " clock ticks" << endl;
        cout << "2000 deletions is " << b << " clock ticks" << endl;
        cout << "deletion ratio: " << ratio << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "deletion O(log(n))" <<endl;
        cout << "1000 deletions is " << a << " clock ticks" << endl;
        cout << "2000 deletions is " << b << " clock ticks" << endl;
        cout << "deletion ratio: " << ratio << endl;
        return true;
    }
}

bool Tester::testBSTProperty(Tiger * aTiger){
    if(aTiger == nullptr){
        return true;
    }else{
        bool isLeft = testBSTProperty(aTiger->m_left);
        if(aTiger->m_left != nullptr){
            if(aTiger->m_left->m_id > aTiger->m_id){
                return false;
            }
            if(aTiger->m_right != nullptr){
                if( aTiger->m_right->m_id < aTiger->m_id){
                    return false;
                }
            }
        }
        bool isRight = testBSTProperty(aTiger->m_right);
        if(isLeft != false && isRight != false){
            return true;
        }else{
            return false;
        }
    }
}
