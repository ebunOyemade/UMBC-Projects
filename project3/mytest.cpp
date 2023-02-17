// CMSC 341 - Fall 2022 - Project 3
#include "iqueue.h"
#include <random>
// the followings are sample priority functions to be used by IQueue class
// users can define their own priority functions
// Priority functions compute an integer priority for a crop.  Internal
// computations may be floating point, but must return an integer.
int priorityFn1(const Crop &crop);// works with a MAXHEAP
int priorityFn2(const Crop &crop);// works with a MINHEAP

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
    const char* FAIL_STATEMENT = "*****TEST FAILED: ";
    const char* PASS_STATEMENT = "     TEST PASSED: ";
    bool insertCropTest();///tests insertCrop
    bool getNextCropTest();//tests getNextCrop
    bool setPriorityTest();//tests setPriorityFn
    bool mergeWithEmptyTest();//tests merging with an empty queue
    bool copyConstructorTest();//tests copy constructor
    bool assignmentOperatorTest();//tests assignment operator
    bool emptyQueueTest();//tests if getNextCrop throws an error if given empty queue
    bool domainErrorTest();//tests if mergeWithQueue throws an error if given queues w/ different types
    bool insertionTime();//tests insertion time is logn
    bool deletionTime();//tests deletion time is logn
};

int main(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn2, MINHEAP);
    for (int i=0;i<10;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    cout << "\nDump of the queue with priorityFn2 (MINHEAP):\n";
    queue1.dump();
    queue1.setPriorityFn(priorityFn1, MAXHEAP);
    cout << "\nDump of the queue with priorityFn1 (MAXHEAP):\n";
    queue1.dump();
    cout << "\nPreorder traversal of the nodes in the queue with priorityFn1 (MAXHEAP):\n";
    queue1.printCropsQueue();
    Tester test;

    test.insertCropTest();
    test.getNextCropTest();
    test.setPriorityTest();
    test.mergeWithEmptyTest();
    test.copyConstructorTest();
    test.assignmentOperatorTest();
    test.emptyQueueTest();
    test.domainErrorTest();
    test.insertionTime();
    test.deletionTime();
    return 0;
}

int priorityFn1(const Crop &crop) {
    //needs MAXHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [30-116]
    //the highest priority would be 110+6 = 116
    //the lowest priority would be 30+0 = 30
    //the larger value means the higher priority
    int priority = crop.getTemperature() + crop.getType();
    return priority;
}

int priorityFn2(const Crop &crop) {
    //needs MINHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-103]
    //the highest priority would be 0+0 = 0
    //the lowest priority would be 100+3 = 103
    //the smaller value means the higher priority
    int priority = crop.getMoisture() + crop.getTime();
    return priority;
}

bool Tester::insertCropTest(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn2, MINHEAP);
    
    for (int i=0;i<300;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,
                    moistureGen.getRandNum(),
                    time,       
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    
    if(queue1.minProperty(queue1.m_heap)){//checks if heap has minheap priorities
        cout << PASS_STATEMENT << "insertCrop minheap test" << endl;
    }else{
        cout << FAIL_STATEMENT << "insertCrop minheap test" << endl;
        return false;
    }
    
    IQueue queue2(priorityFn2, MAXHEAP);
    for (int i=0;i<300;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,
                    moistureGen.getRandNum(),
                    time,       
                    typeGen.getRandNum());
        queue2.insertCrop(aCrop);
    }
    if(queue2.maxProperty(queue2.m_heap)){//checks if heap has max heap properties
        cout << PASS_STATEMENT << "insertCrop maxheap test" << endl;
        return true;
    }else{
        cout << FAIL_STATEMENT << "insertCrop maxheap test" << endl;
        return false;
    }
}

bool Tester::getNextCropTest(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn2, MINHEAP);
    
    for (int i=0;i<300;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,
                    moistureGen.getRandNum(),
                    time,       
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    
    for(int i = 0; i < 300;i++){//checks nodes ar removed in the right order
        if(i < 299){
            Crop aCrop = queue1.getNextCrop();
            if(priorityFn2(aCrop) > priorityFn2(queue1.m_heap->m_crop)){
                cout << FAIL_STATEMENT << "getNextCrop MINHEAP test"<< endl;
                return false;
            }
        }else{
            queue1.getNextCrop();
        }
    }
    cout << PASS_STATEMENT << "getNextCrop MINHEAP test"<< endl;
    
    IQueue queue2(priorityFn2, MAXHEAP);
    for (int i=0;i<300;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,
                    moistureGen.getRandNum(),
                    time,       
                    typeGen.getRandNum());
        queue2.insertCrop(aCrop);
    }
    for(int i = 0; i < 300;i++){//checks if nodes are removed in right order
        if(i < 299){
            Crop aCrop = queue2.getNextCrop();
            if(priorityFn2(aCrop) < priorityFn2(queue2.m_heap->m_crop)){
                cout << FAIL_STATEMENT << "getNextCrop MAXHEAP test"<< endl;
                return false;
            }
        }else{
            queue2.getNextCrop();
        }
    }
    cout << PASS_STATEMENT << "getNextCrop MAXHEAP test"<< endl;
    return true;
}
bool Tester::setPriorityTest(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn2, MINHEAP);
    
    for (int i=0;i<10;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,
                    moistureGen.getRandNum(),
                    time,   
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    queue1.setPriorityFn(priorityFn1, MAXHEAP);
    if(queue1.maxProperty(queue1.m_heap)){//checks if converted heap has properties of new its new type
        cout << PASS_STATEMENT << "setPriorityFn() test" << endl;
        return true;
    }else{
        cout << FAIL_STATEMENT << "setPriorityFn() test" << endl;
        return false;
    }
    
}
bool Tester::mergeWithEmptyTest(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn2, MINHEAP);
    for (int i=0;i<10;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,
                    moistureGen.getRandNum(),
                    time,       
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    
    IQueue queue2(priorityFn2, MINHEAP);
    queue2.mergeWithQueue(queue1);
    if(queue2.numCrops() != 10 && queue1.numCrops() != 0){//checks if queue1 is empty and queue2 has correct nnumber of nodes
        cout << FAIL_STATEMENT << "merge with empty queue test" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "merge with empty queue test" << endl;
        return true;
    }
    
}
bool Tester::copyConstructorTest(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn2, MINHEAP);
    
    for (int i=0;i<10;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,
                    moistureGen.getRandNum(),
                    time,       
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    IQueue queue2(queue1);
    if(&queue2 == &queue1){//checks if queues have different memory addressess
        cout << FAIL_STATEMENT << "copy constructor normal case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "copy constructor normal case" << endl;
    }
    
    IQueue queue3(priorityFn2, MINHEAP);
    IQueue queue4(queue3);
    if(&queue3 == &queue1){//checks if queues have different memory addressess
        cout << FAIL_STATEMENT << "copy constructor normal case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "copy constructor normal case" << endl;
        return true;
    }
}

bool Tester::assignmentOperatorTest(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn2, MINHEAP);
    for (int i=0;i<10;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,
                    moistureGen.getRandNum(),
                    time,       
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    
    IQueue queue2(priorityFn2, MAXHEAP);
    for (int i=0;i<10;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,
                    moistureGen.getRandNum(),
                    time,       
                    typeGen.getRandNum());
        queue2.insertCrop(aCrop);
    }
    queue2 = queue1;
    if(&queue2 == &queue1){//checks if queues have different memory addressess
        cout << FAIL_STATEMENT << "assignment operator normal case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "assignment operator normal case" << endl;
    }
    
    IQueue queue3(priorityFn2, MINHEAP); 
    queue1 = queue3;
    if(&queue3 == &queue1){//checks if queues have different memory addressess
        cout << FAIL_STATEMENT << "assignment operator normal case" << endl;
        return false;
    }else{
        cout << PASS_STATEMENT << "assignment operator normal case" << endl;
        return true;
    }
}

bool Tester::emptyQueueTest(){
    IQueue queue1(priorityFn2, MINHEAP);
    try{
        queue1.getNextCrop();
        cout << FAIL_STATEMENT << "empty queue Test" << endl;
        return false;
    }catch(out_of_range & err){//checks if error is thrown & if it is correct error
        cout << PASS_STATEMENT << "empty queue Test" << endl;
        return true;
    }
}

bool Tester::domainErrorTest(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn2, MINHEAP);
    
    for (int i=0;i<10;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,
                    moistureGen.getRandNum(),
                    time,       
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }

    IQueue queue2(priorityFn2, MAXHEAP);
    for (int i=0;i<10;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,
                    moistureGen.getRandNum(),
                    time,       
                    typeGen.getRandNum());
        queue2.insertCrop(aCrop);
    }
    
    try{
        queue1.mergeWithQueue(queue2);
        cout << FAIL_STATEMENT << "domain_error" << endl;
        return false;
    }catch(domain_error & err){//checks if error is thrown & if it is correct error
        cout << PASS_STATEMENT << "domain_error test" << endl;
        return true;
    }
    
}

bool Tester::insertionTime(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn2, MINHEAP);
    IQueue queue2(priorityFn2, MINHEAP);
    clock_t start = clock();
    
    for (int i=0;i<1000;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,
                    moistureGen.getRandNum(),
                    time,       
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    clock_t a = clock() - start;
    clock_t start2 = clock();
    for (int i=0;i<2000;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue2.insertCrop(aCrop);
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
bool Tester::deletionTime(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn2, MINHEAP);
    IQueue queue2(priorityFn2, MINHEAP);
    
    for (int i=0;i<1000;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,
                    moistureGen.getRandNum(),
                    time,   
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    clock_t start = clock();
    for(int i = 0; i< 1000; i++){
        queue1.getNextCrop();
    }
    clock_t a = clock() - start;
    for (int i=0;i<2000;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue2.insertCrop(aCrop);
    }
    clock_t start2 = clock();
    for(int i = 0; i < 2000; i++){
        queue2.getNextCrop();
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
