#include "railroad.h"
Railroad::Railroad(){
    m_head = nullptr;
    m_tail = nullptr;
    m_numStations = 0;
}

Railroad::~Railroad(){
    clearNetwork();
}

void Railroad::clearNetwork(){
    clearAllRoutes();
    while(m_numStations > 0){//calls removeStation to remove m_tail until all are deleted
        Station *temp = m_head;
        removeStation(temp->m_code);
    }     

}

bool Railroad::extendAtHead(int newCode, int passengers){
    bool isSame = false;
    Station *temp = m_head;
    if(m_head != nullptr){
        while(temp != nullptr){//checks to see if newCode has not been used
            if(temp->m_code == newCode){
                return isSame;
            }
            temp = temp->m_next;
        }
        
    }
    
    if(isSame == false && newCode >= 1){
        Station *temp = new Station(newCode, passengers);
        if(m_numStations == 0){
            m_head = temp;
            m_tail = temp;
        }else{
            temp ->m_next = m_head;
            m_head ->m_previous = temp;
            m_head = temp;
        }
        
        m_numStations += 1;
        return true;
  }else{
    return false;
  }
}

bool Railroad::extendAtTail(int newCode, int passengers){
    bool isSame = false;
    Station *temp = m_head;
    
    if(m_head != nullptr){
        while(temp != nullptr){//checks to see if newCode has not been used
            if(temp->m_code == newCode){
                return isSame;
            }
            temp = temp->m_next;
        }
        
    }
    if(isSame == false && newCode >= 1){
       Station *temp = new Station(newCode, passengers);
       if(m_numStations == 0){
           m_head = temp;
           m_tail = temp;
         
       }else{
            m_tail->m_next = temp;
            temp->m_previous = m_tail;
            m_tail = temp;
       }
       
       m_numStations += 1;
       return true;
    }else{
      return false;
    }
}

void Railroad::dump(){
    if (m_head != nullptr){
        int northCode, southCode, eastCode, westCode;
        Station *temp = m_head;
        while(temp != nullptr){
            if (temp->m_north != nullptr) northCode = temp->m_north->m_code;
            else northCode = -1;
            if (temp->m_south != nullptr) southCode = temp->m_south->m_code;
            else southCode = -1;
            if (temp->m_east != nullptr) eastCode = temp->m_east->m_code;
            else eastCode = -1;
            if (temp->m_west != nullptr) westCode = temp->m_west->m_code;
            else westCode = -1;
            cout << temp->m_code << 
                    " (" << 
                    "P: " << temp->m_passengers << 
                    ", N: " << northCode <<
                    ", S: " << southCode <<
                    ", E: " << eastCode <<
                    ", W: " << westCode <<
                    ")" << endl;
            temp = temp->m_next;
        }
    }
}

bool Railroad::makeRoute(list< pair<int,DIRECTION> > route){
    bool inRoad = false;//checks to see if the list valid
    int codeList[(int)route.size()];//stores the code from every pair
    Station *temp = m_head;
    int count1 = 0;
    int checkRepeat = 0;//stores previous code in list to prevent a station from linking to its self
    int isRealCount = 0;//counts number of codes that are not in linked list
    
    if((int)route.size() == 0){
        return true;
    }
    
    if(m_head != nullptr){
        while(temp != nullptr){//checks to if the first code exists in the linked list
            if(temp->m_code == route.begin()->first){
                inRoad = true;
            }
            temp = temp->m_next;
        }   
    }
    
    for(list<pair<int,DIRECTION>>::iterator it = route.begin();it != route.end();it++){
        if(count1 + 1 == (int)route.size()){//sets DIRECTION of last element in list to NONE
            it->second = NONE;
        }else if(count1 + 1 != (int)route.size() && it->second == NONE){//checks if NONE is not last 
            inRoad = false;
        }else if(it->first == checkRepeat){//checks if a node is connected to itself 
            inRoad = false;
        }
        
        checkRepeat = it->first;
        count1 += 1;
    }
    
    if(inRoad){
        int count = 0;
        for(list<pair<int,DIRECTION>>::iterator it = route.begin();it != route.end();it++){
            bool isReal = false;
            codeList[count] = it->first;
            
            if(it != route.begin()){//checks list if on the first element
                Station *temp = m_head;
                if(m_head != nullptr){
                    while(temp != nullptr){//checks each element after the first if the code exists 
                        if(temp->m_code == it->first){
                            isReal = true;
                        }
                    temp = temp->m_next;
                    }   
                }
            }
            
            if(isReal == false){
                extendAtTail(it->first, DEFNUMPASS);
                isRealCount += 1;// counts added nodes
            }
            
            if(count + 1 == (int)route.size()){
                it->second = NONE;
            }
            count += 1;
        }
        
        count = 0;
        for(list<pair<int,DIRECTION>>::iterator it = route.begin();it != route.end();it++){
            count += 1;
            Station *temp = getStation(it->first);//gets the station of the code
            if(it->second == NORTH){
                if(temp->m_north != nullptr){//checks if m_north is not connected to another node
                    for(int i = 1; i < isRealCount; i++){//removes added nodes if m_north is connected
                        removeStation(m_tail->m_code);
                    }
                    return false;
                }else{
                    temp->setNorth(getStation(codeList[count]));
                }
                
            }
	    if(it->second == EAST){
                if(temp->m_east != nullptr){//checks if m_east is not connected to another node
                    for(int i = 0; i < isRealCount; i++){//removes added nodes if m_east is connected
                        removeStation(m_tail->m_code);
                    }
                    return false;
                }else{
                    temp->m_east = getStation(codeList[count]);
                }
                
            }
	    if(it->second == SOUTH){
                if(temp->m_south != nullptr){//checks if m_south is not connected to another node
                    for(int i = 0; i < isRealCount; i++){//removes added nodes if m_south is connected
                        removeStation(m_tail->m_code);
                    }
                    return false;
                }else{
                    temp->m_south = getStation(codeList[count]);
                }
                
            }
	    if(it->second == WEST){
                if(temp->m_west != nullptr){//checks if m_west is not connected to another node
                    for(int i = 0; i < isRealCount; i++){//removes added nodes if m_west is connected
                        removeStation(m_tail->m_code);
                    }
                    return false;
                }else{
                    temp->m_west = getStation(codeList[count]);
                }
            }
        }
        
    }else{
        return false;
    }
    return true;
}

int Railroad::travel(list< pair<int,DIRECTION> > route){
    bool inRoad = true;//true if list contains valid stations
    int codeList[(int)route.size()];//stores all codes
    int count = 0;
    int passengers = 0;
    int checkRepeat = 0;//checks if a Station connects to itself
    
    for(list<pair<int,DIRECTION>>::iterator it = route.begin();it != route.end();it++){
        inRoad = false;//resets to false in order to valid each item
        Station *temp = m_head;
        codeList[count] = it->first;
        
        if(count + 1 == (int)route.size()){//sets DIRECTION of last element in list to NONE
            it->second = NONE;
        }else if(count + 1 != (int)route.size() && it->second == NONE){//checks if NONE is last
            return -1;
        }else if(it->first == checkRepeat){//checks if Station is connected to itself
            return -1;
        }
        count += 1;
        checkRepeat = it->first;
        
        if(m_head != nullptr){
            while(temp != nullptr){//checks if code is in the linked list
                if(temp->m_code == it->first){
                    inRoad = true;
                }
            temp = temp->m_next;
            }
        }
        
        if(inRoad == false){//returns false the list is invalid
            return -1;
        }
    }
    
    if(inRoad){
        count = 0;
        for(list<pair<int,DIRECTION>>::iterator it = route.begin();it != route.end();it++){
            count += 1;
            Station *temp = getStation(it->first);
            if(it->second == NORTH){
                if(temp->m_north == nullptr){//checks if m_north is point to nothing
                    return -1;
                }else if(temp->m_north->m_code != codeList[count]){//checks if m_north points to right Station
                    return -1;
                }
                passengers += temp->m_passengers;
                
            }else if(it->second == EAST){
                if(temp->m_east == nullptr){//checks if m_east is point to nothing
                    return -1;
                }else if(temp->m_east->m_code != codeList[count]){//checks if m_east points to right Station
                    return -1;
                }
                passengers += temp->m_passengers;
                
            }else if(it->second == SOUTH){
                if(temp->m_south == nullptr){//checks if m_south is point to nothing
                    return -1;
                }else if(temp->m_south->m_code != codeList[count]){//checks if m_south points to right Station
                    return -1;
                }
                passengers += temp->m_passengers;
                
            }else if(it->second == WEST){
                if(temp->m_west == nullptr){//checks if m_west is point to nothing
                    return -1;
                }else if(temp->m_west->m_code != codeList[count]){//checks if m_west points to right Station
                    return -1;
                }
                passengers += temp->m_passengers;
                
            }else{
               passengers += temp->m_passengers; 
            }
        }
        return passengers;
    }else{
        return 1;
    }
}

bool Railroad::setNumPassengers(int code, int passengers){
    Station *temp = m_head;
    bool inRoad = false;//true if code is in linked list
    
    if(m_head != nullptr){
        while(temp != nullptr){//checks if code is in linked list
            if(temp->m_code == code){
                inRoad = true;
            }
            temp = temp->m_next;
        }
    }
    
    Station *curr = getStation(code);
    if(inRoad){
        curr->m_passengers = passengers;
        return true;
    }else{
        return false;
    }
}

bool Railroad::removeStation(int aCode){
    bool inRoad = false;//true if code is in linked list
    
    if(m_head != nullptr){
        Station *temp = m_head;
        while(temp != nullptr){
            if(temp->m_code == aCode){//checks if aCode is in linked list
                inRoad = true;
            }
            temp = temp->m_next;
        }   
    }
    
    if(inRoad){
        if(m_head != nullptr){
            Station *temp = m_head;
            while(temp != nullptr){//removes all links linked to aCode
                if(temp->m_north != nullptr){
                    if(temp->m_north->m_code == aCode){
                        temp->m_north = nullptr;
                    }
                    
                }
                if(temp->m_east != nullptr){
                    if(temp->m_east->m_code == aCode){
                        temp->m_east = nullptr;
                    }
                    
                }
                if(temp->m_south != nullptr){
                    if(temp->m_south->m_code == aCode){
                        temp->m_south = nullptr;
                    }
                    
                }
                if(temp->m_west != nullptr){
                    if(temp->m_west->m_code == aCode){
                        temp->m_west = nullptr;
                    }
                    
                }
                temp = temp->m_next;
            }
            
        }
        if(aCode == m_head->m_code){//scenario for m_head being deleted
            Station *curr = getStation(aCode);
            if(m_numStations > 1){
                Station *next = curr->m_next;
                next->m_previous = nullptr;
                m_head = next;
            }
            delete curr;
            curr = nullptr;
            
        }else if(aCode == m_tail->m_code){//scenario for m_tail being deleted
            Station *curr = getStation(aCode);
            if(m_numStations > 1){
                Station *prev = curr->m_previous;
                prev->m_next = nullptr;
                m_tail = prev;
            }
            delete curr;
            curr = nullptr;
            
        }else{//scenario any node that is not m_head or m_tail
            Station *curr = getStation(aCode);
            Station *next = curr->m_next;
            Station *prev = curr->m_previous;
            next->m_previous = prev;
            prev->m_next = next;
            delete curr;
            curr = nullptr;
        }
        
        m_numStations -= 1;
        return true;
    }else{
        return false;
    }    
}

void Railroad::clearAllRoutes(){
    if(m_head != nullptr){
        Station *temp = m_head;
        while(temp != nullptr){//removes all routes in linked list
            if(temp->m_north != nullptr){
                temp->m_north = nullptr;
                
            }
            if(temp->m_east != nullptr){
                temp->m_east = nullptr;
                    
            }
            if(temp->m_south != nullptr){
                temp->m_south = nullptr;
                
            }
            if(temp->m_west != nullptr){
                temp->m_west = nullptr;
            }
            
            temp = temp->m_next;
        }
    }
}

const Railroad & Railroad::operator=(const Railroad & rhs){
    if(this != &rhs){//checks for self assign
        clearNetwork();
        m_head = nullptr;
        m_tail = nullptr;
        m_numStations = 0;
        Station *curr = rhs.m_head;
        
        for(int i = 0; i < rhs.m_numStations; i++){//copies nodes from rhs
            this->extendAtTail(curr->m_code, curr->m_passengers);
            curr = curr->m_next;
        }
        
        curr = rhs.m_head;
        if(m_head != nullptr){//copies routes from rhs
            Station *temp = m_head;
            while(temp != nullptr){
                if(curr->m_north != nullptr){
                    temp->m_north = getStation(curr->m_north->m_code);
                }
                
                if(curr->m_east != nullptr){
                    temp->m_east = getStation(curr->m_east->m_code);
                }
                
                if(curr->m_south != nullptr){
                    temp->m_south = getStation(curr->m_south->m_code);  
                }
                
                if(curr->m_west != nullptr){
                    temp->m_west = getStation(curr->m_west->m_code);
                }
                temp = temp->m_next;
                curr = curr->m_next;
            }   
        }
    } 

    return *this;
}

Railroad::Railroad(const Railroad & rhs){
    m_head = nullptr;
    m_tail = nullptr;
    m_numStations = 0;
    clearNetwork();
    Station *curr = rhs.m_head;
    
    for(int i = 0; i < rhs.m_numStations; i++){//copies nodes from rhs
        extendAtTail(curr->m_code,curr->m_passengers);

        curr = curr->m_next;
    }
    
    curr = rhs.m_head;
    if(m_head != nullptr){//copies routes from rhs
        Station *temp = m_head;
        while(temp != nullptr){
            if(curr->m_north != nullptr){
                temp->m_north = getStation(curr->m_north->m_code);
            }
            
            if(curr->m_east != nullptr){
                temp->m_east = getStation(curr->m_east->m_code);
            }
            
            if(curr->m_south != nullptr){
                temp->m_south = getStation(curr->m_south->m_code);  
            }
            
            if(curr->m_west != nullptr){
                temp->m_west = getStation(curr->m_west->m_code);
            }
            temp = temp->m_next;
            curr = curr->m_next;
        }   
    }

}
Station * Railroad::getStation(int code){//gets a node from its corresponding code
    Station *curr = m_head;
    if(m_head != nullptr){
        while(curr != nullptr){//searches for code in linked list
            if(curr->m_code == code){
                return curr;
            }
            
            curr = curr -> m_next;
        }
    }
    return curr;
}
