// CMSC 341 - Fall 2022 - Project 4
#include "cache.h"
Cache::Cache(int size, hash_fn hash){
    m_hash = hash;
    m_currentCap = size;
    m_currentSize = 0;
    m_currNumDeleted = 0;
    m_currentTable = new Person[size];
    for(int i = 0 ; i < size; i++){
        m_currentTable[i] = EMPTY;
    }
    
    m_oldCap = 0;
    m_oldSize = 0;
    m_oldNumDeleted = 0;
    m_oldTable = new Person[size];
    for(int i = 0 ; i < size; i++){
        m_oldTable[i] = EMPTY;
    }
}

Cache::~Cache(){
    delete[] m_currentTable;
    delete[] m_oldTable;
}

bool Cache::insert(Person person){
    bool freeSpace = false;
    float loadFactor = 0.5;
    //inserts new nodes
    if(person.getID() > MINID && person.getID() < MAXID){
        int index = m_hash(person.getKey()) % m_currentCap;
        if(m_currentTable[index] == EMPTY || m_currentTable[index] == DELETED){//checks for open space
            m_currentTable[index] = person;
        }else{//case for collision handling
            int count = 0;
            int newIndex;
            while(freeSpace == false){
                newIndex = (index + count * count) % m_currentCap;
                count += 1;
                if(m_currentTable[newIndex] == EMPTY || m_currentTable[newIndex] == DELETED){
                    m_currentTable[newIndex] = person;
                    freeSpace = true;
                }
            
            }
        }
        
        m_currentSize += 1;
        
        //if load factor > .5 hash new table
        if(lambda() > loadFactor){
            delete[] m_oldTable;//sets m_oldTable equal to m_currentTable
            m_oldTable = new Person[m_currentCap];
            m_oldCap = m_currentCap;
            m_oldSize = m_currentSize;
            m_oldNumDeleted = m_currNumDeleted;
            for(int i = 0 ; i < m_currentCap; i++){
                if(!(m_currentTable[i] == DELETED)){
                    m_oldTable[i] = m_currentTable[i];
                }
            }
        
            //clears m_currentTable
            delete[] m_currentTable;
            if(isPrime(((m_currentSize - m_currNumDeleted)*4))){
               m_currentCap = ((m_currentSize - m_currNumDeleted)*4);
            }else{
               m_currentCap = findNextPrime(((m_currentSize - m_currNumDeleted)*4));
            }
            m_currentSize = 0;
            m_currNumDeleted = 0;
            m_currentTable = new Person[m_currentCap];
            for(int i = 0 ; i < m_currentCap; i++){
               m_currentTable[i] = EMPTY;
            }

        }
        //transfer 25% nodes
        int i = 0;//counts number of insertions
        int count = 0;//interates through table
        int total = floor(m_oldSize/4);
        while(i != total){//loops until 25% of nodes have been added
            bool openSpace = false;// checks if a node is availible
            if(!(m_oldTable[count] == EMPTY || m_oldTable[count] == DELETED)){
                int key = m_hash(m_oldTable[count].getKey()) % m_currentCap;
                int count2 = 0;
                int newKey;
                while(openSpace == false){//automatic collision handling for simplicity
                    newKey = (key + count2 * count2) % m_currentCap;
                    count2 += 1;
                    if(m_currentTable[newKey] == EMPTY || m_currentTable[newKey] == DELETED){
                        m_currentTable[newKey] = m_oldTable[count];
                        openSpace = true;
                        m_oldTable[count] = DELETED;
                        m_currentSize += 1;
                        m_oldNumDeleted += 1;
                    }
                }
                i += 1;
                if(m_oldSize - m_oldNumDeleted == 0){//case for when the is less than %25 of orginal nodes
                    i = total;
                    delete[] m_oldTable;
                    m_oldCap = 0;
                    m_oldSize = 0;
                    m_oldNumDeleted = 0;
                    m_oldTable = new Person[0];
                }
            }
            count += 1;
        }
    }else{
        return false;
    }
    return true;
}

bool Cache::remove(Person person){
    bool inTable = false;
    float ratio = .8;
    for(int i = 0; i < m_currentCap; i++){//loops through table to find specific person
        if(m_currentTable[i] == person){
            inTable = true;
            m_currentTable[i] = DELETED;
            m_currNumDeleted += 1;
        }
    }
    
    
    //if delete ratio > .8 rehash table
    if(deletedRatio() > ratio){
        delete[] m_oldTable;
        m_oldTable = new Person[m_currentCap];
        m_oldCap = m_currentCap;
        m_oldSize = m_currentSize;
        m_oldNumDeleted = m_currNumDeleted;
        for(int i = 0 ; i < m_oldCap; i++){
            if(!(m_currentTable[i] == DELETED)){
                m_oldTable[i] = m_currentTable[i];
            }
        }
    
    
        delete[] m_currentTable;
        if(isPrime(((m_currentSize - m_currNumDeleted)*4))){
           m_currentCap = ((m_currentSize - m_currNumDeleted)*4);
        }else{
           m_currentCap = findNextPrime(((m_currentSize - m_currNumDeleted)*4));
        }
        m_currentSize = 0;
        m_currNumDeleted = 0;
        m_currentTable = new Person[m_currentCap];
        for(int i = 0 ; i < m_currentCap; i++){
           m_currentTable[i] = EMPTY;
        }

    }
    //insert 25% of nodes
    int i = 0;
    int count = 0;
    int total = floor(m_oldSize/4);
    while(i != total){
        bool openSpace = false;
        if(!(m_oldTable[count] == EMPTY || m_oldTable[count] == DELETED)){
            int key = m_hash(m_oldTable[count].getKey()) % m_currentCap;
            int count2 = 0;
            int newKey;
            while(openSpace == false){
                newKey = (key + count2 * count2) % m_currentCap;
                count2 += 1;
                if(m_currentTable[newKey] == EMPTY || m_currentTable[newKey] == DELETED){
                    m_currentTable[newKey] = m_oldTable[count];
                    openSpace = true;
                    m_oldTable[count] = DELETED;
                    m_currentSize += 1;
                    m_oldNumDeleted += 1;
                }
            }
            i += 1;
            if(m_oldSize - m_oldNumDeleted == 0){
                i = total;
                delete[] m_oldTable;
                m_oldCap = 0;
                m_oldSize = 0;
                m_oldNumDeleted = 0;
                m_oldTable = new Person[0];
            }
        }
        count += 1;
    }
    return inTable;
}

Person Cache::getPerson(string key, int id) const{
    bool inTable = false;
    Person target;
    for(int i = 0; i < m_currentCap; i++){//loops through current table to find person
        if(m_currentTable[i].getKey() == key && m_currentTable[i].getID() == id){
            inTable = true;
            target = m_currentTable[i];
        }
        
    }
    for(int i = 0; i < m_oldCap; i++){//loops through old table to find person
        if(m_oldTable[i].getKey() == key && m_oldTable[i].getID() == id){
            inTable = true;
            target = m_oldTable[i];
        }
        
    }
    
    if(inTable == false){//if person not found sends EMPTY person
        return EMPTY;
    }else{
        return target;
    }
}

float Cache::lambda() const {
    float loadFactor = (float) (m_currentSize - m_currNumDeleted) / m_currentCap;
    return loadFactor;
}

float Cache::deletedRatio() const {
    float deleteRatio = (float) (m_currNumDeleted)/ m_currentSize;
    return deleteRatio;
    
}

void Cache::dump() const {
    cout << "Dump for the current table: " << endl;
    if (m_currentTable != nullptr)
        for (int i = 0; i < m_currentCap; i++) {
            cout << "[" << i << "] : " << m_currentTable[i] << endl;
        }
    cout << "Dump for the old table: " << endl;
    if (m_oldTable != nullptr)
        for (int i = 0; i < m_oldCap; i++) {
            cout << "[" << i << "] : " << m_oldTable[i] << endl;
        }
}

bool Cache::isPrime(int number){
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int Cache::findNextPrime(int current){
    //we always stay within the range [MINPRIME-MAXPRIME]
    //the smallest prime starts at MINPRIME
    if (current < MINPRIME) current = MINPRIME-1;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}

ostream& operator<<(ostream& sout, const Person &person ) {
    if (!person.m_key.empty())
        sout << person.m_key << " (ID " << person.m_id << ")";
    else
        sout << "";
  return sout;
}

bool operator==(const Person& lhs, const Person& rhs){
    return ((lhs.m_key == rhs.m_key) && (lhs.m_id == rhs.m_id));
}
