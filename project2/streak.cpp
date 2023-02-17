// UMBC - CMSC 341 - Fall 2022 - Proj2
#include "streak.h"

Streak::Streak(){
    m_root = nullptr;
}

Streak::~Streak(){
    clear();
}

void Streak::insert(const Tiger& tiger){
    if(tigerInList(m_root,tiger.m_id) == false){//checks to see if id is unique
        if(tiger.m_id >= MINID && tiger.m_id <= MAXID){//checks to see if the id is in valid range
            if(m_root == nullptr){
                Tiger* temp = new Tiger;
                temp->m_id = tiger.m_id;
                temp->m_age = tiger.m_age;
                temp->m_gender = tiger.m_gender;
                temp->m_state = tiger.m_state;
                temp->m_left = nullptr;
                temp->m_right = nullptr;
                temp->m_height = 0;
                m_root = temp;
            }else{
                Tiger* temp = new Tiger;
                temp->m_id = tiger.m_id;
                temp->m_age = tiger.m_age;
                temp->m_gender = tiger.m_gender;
                temp->m_state = tiger.m_state;
                temp->m_left = nullptr;
                temp->m_right = nullptr;
                temp->m_height = 0;
                Tiger* prev = findPrevious(temp->m_id);//finds the parent node of the new node
                
                if(temp->m_id < prev->m_id){//adds new node to tree
                    prev->m_left = temp;
                }else{
                    prev->m_right = temp;
                }
                
                balanceAll(m_root);
                updateAll(m_root);
                
            }
        }
    }

}

void Streak::clear(){
    removeAll(m_root);
}

void Streak::remove(int id){
    removeNoBalance(id);
    balanceAll(m_root);
    updateAll(m_root);
}

void Streak::updateHeight(Tiger* aTiger){
    int height = getTreeHeight(aTiger);
    aTiger->m_height = height - 1;//subtracts one to get height from depth
}

int Streak::checkImbalance(Tiger* aTiger){
    int right = 0;
    int left = 0;
    int rebalanceFactor = 0;
    
    if(aTiger != nullptr){
        if(aTiger->m_left != nullptr){//gets balance factor of left subtree
            Tiger* temp = aTiger->m_left;
            left = getTreeHeight(temp);
        }
        if(aTiger->m_right != nullptr){//gets balance factor of right subtree
            Tiger* temp = aTiger->m_right;
            right = getTreeHeight(temp);
        }
    }
    
    rebalanceFactor = right - left;//determines the balance factor of selected node
    return rebalanceFactor;
}

Tiger* Streak::rebalance(Tiger* aTiger){
    int rebalanceFactor = checkImbalance(aTiger);
    
    if(rebalanceFactor > 1){//checks if rebalancing is necessary and which subtree it needs to take place
        if(checkImbalance(aTiger->m_right) < 0){//determines if a LL or RL rotation is needed
            aTiger = rotateRight(aTiger->m_right);//
            aTiger = rotateLeft(aTiger);
        }else{
            aTiger = rotateLeft(aTiger);  
        }
    }else if(rebalanceFactor < -1){//determines if a RR or LR rotation is needed
        if(checkImbalance(aTiger->m_left) > 0){
            aTiger = rotateLeft(aTiger->m_left);
            aTiger = rotateRight(aTiger);
        }else{
            aTiger = rotateRight(aTiger);
        }
    }
    return aTiger;
}

void Streak::dumpTree() const {dump(m_root);}

void Streak::dump(Tiger* aTiger) const{
    if (aTiger != nullptr){
        cout << "(";
        dump(aTiger->m_left);//first visit the left child
        cout << aTiger->m_id << ":" << aTiger->m_height;//second visit the node itself
        dump(aTiger->m_right);//third visit the right child
        cout << ")";
    }
}

void Streak::listTigers() const {
    inOrder(m_root);
}

bool Streak::setState(int id, STATE state){
    bool inTree = findTiger(id);
    if(inTree){
        Tiger* temp = getTiger(id);
        temp->m_state = state;
        return true;
    }else{
        return false;
    }
}

void Streak::removeDead(){
    findDead(m_root);
    balanceAll(m_root);
    updateAll(m_root);
}

bool Streak::findTiger(int id) const {
    if(m_root != nullptr){//iteritively goes through tree to determine if a node is a tree
        Tiger* temp = m_root;
        while(temp != nullptr){
            if(temp->m_id == id){//returns true if node is found
                return true;
            }else if(id < temp->m_id){
                temp = temp->m_left;
            }else{
                temp = temp->m_right;
            }
        }
    }
    return false;
}

int Streak::countTigerCubs() const{
    int numCubs = countCubs(m_root);
    return numCubs;
}

Tiger* Streak::getTiger(int id) const{
    if(m_root != nullptr){
        Tiger* temp = m_root;
        while(temp != nullptr){//goes through tree to find id
            if(temp->m_id == id){//returns node if its id matchs the given id
                return temp;
            }else if(id < temp->m_id){//checks id to determine the where to go
                temp = temp->m_left;
            }else{
                temp = temp->m_right;
            }
        }
    }
    Tiger* temp = nullptr;//returns nullptr if given id is not in tree
    return temp;
}

int Streak::getTreeHeight(Tiger* aTiger)const{//recursively counts each level of both subtrees
    if(aTiger == nullptr){
        return 0;
    }else{
        int leftHeight = getTreeHeight(aTiger->m_left);
        int rightHeight = getTreeHeight(aTiger->m_right);
        if(leftHeight > rightHeight){//checks which subtree is taller
            return (leftHeight + 1);
        }else{
            return (rightHeight + 1);    
        }
    }
}

int Streak::countCubs(Tiger* aTiger) const{
    int numCubs = 0;
    if(aTiger == nullptr){
        return 0;
    }else{
        numCubs += countCubs(aTiger->m_left);
        numCubs += countCubs(aTiger->m_right);
        if(aTiger->m_age == CUB){//checks to see if a node is a CUB
            return numCubs + 1;
        }
        return numCubs;
    }
}
Tiger* Streak::rotateRight(Tiger* aTiger){
    Tiger* temp;
    if(aTiger != m_root){
        Tiger* prev = findPrevious(aTiger->m_id);//finds parent
        temp = aTiger->m_left;//stores given node m_left
        aTiger->m_left = temp->m_right;//sets targets left subtree as temporary nodes right tree
        temp->m_right = aTiger;//sets the right subtree to given node
        if(temp->m_id < prev->m_id){//attaches temporary to tree
            prev->m_left = temp;
        }else{
            prev->m_right = temp;
        }
    }else{//case where the root is passed
        temp = aTiger->m_left;
        aTiger->m_left = temp->m_right;
        temp->m_right = aTiger;
        m_root = temp;
    }
    return temp;
}

Tiger* Streak::rotateLeft(Tiger* aTiger){
    Tiger* temp;
    if(aTiger != m_root){
        Tiger* prev = findPrevious(aTiger->m_id);//finds parent
        temp = aTiger->m_right;//stores given node m_right
        aTiger->m_right = temp->m_left;//sets targets right subtree as temporary nodes left tree
        temp->m_left = aTiger;//sets the left subtree to given node
        if(temp->m_id < prev->m_id){//attaches temporary to tree
            prev->m_left = temp;
        }else{
            prev->m_right = temp;
        }
    }else{//case where the root is passed
        temp = aTiger->m_right;
        aTiger->m_right = temp->m_left;
        temp->m_left = aTiger;
        m_root = temp;
    }
    return temp;
}

void Streak::inOrder(Tiger* aTiger)const{
    if(aTiger == nullptr){
        return;
    }else{
        inOrder(aTiger->m_left);
        cout << aTiger->m_id << ":" << aTiger->getAgeStr() << ":" 
        << aTiger->getGenderStr() << ":" << aTiger->getStateStr() << endl;
        inOrder(aTiger->m_right);
    }
}

void Streak::balanceAll(Tiger* aTiger){
    if (aTiger == nullptr){
      return;
    }else{
        balanceAll(aTiger->m_left);
        balanceAll(aTiger->m_right);
        rebalance(aTiger);
        return;
    }
}

void Streak::updateAll(Tiger* aTiger){
    if (aTiger == nullptr){
        return;
    }else{
        updateAll(aTiger->m_left);
        updateHeight(aTiger);
        updateAll(aTiger->m_right);
        return;
    }
}

Tiger* Streak::findPrevious(int id){//finds parent node
    Tiger* prev;
    if(m_root != nullptr){
        Tiger* temp = m_root;
        while(temp != nullptr){//loops until parent is found
            if(temp->m_id == id){
                return prev;//returns parent node
            }else if(id < temp->m_id){
                prev = temp;
                temp = temp->m_left;
            }else{
                prev = temp;
                temp = temp->m_right;
            }
        }
    }
    return prev;//case if node is not in tree returns node possible parent tree
}

void Streak::removeAll(Tiger* aTiger){
    if(aTiger == nullptr){
        return;
    }else{
        removeAll(aTiger->m_left);
        removeAll(aTiger->m_right);
        removeNoBalance(aTiger->m_id);
    }
}
void Streak::findDead(Tiger* aTiger){
    if(aTiger == nullptr){
        return;
    }else{
        findDead(aTiger->m_left);
        findDead(aTiger->m_right);
        if(aTiger->m_state == DEAD){//removes dead node
            removeNoBalance(aTiger->m_id);
        }
        return;
    }
}
void Streak::removeNoBalance(int id){//remove function used for functions for consistent results
    bool inTree = findTiger(id);//checks given node in tree
    if(inTree){
        Tiger* temp = getTiger(id);
        Tiger* left = temp->m_left;
        Tiger* right = temp->m_right;
        if(temp != m_root){
            Tiger* prev = findPrevious(id);//finds parent nodw
            if(right != nullptr && left != nullptr){//case for node with 2 children
                if(prev->m_left == temp){//checks for open spot in parent node
                    prev->m_left = right;
                    Tiger* curr = right;
                    while(curr->m_left != nullptr){
                        curr = curr->m_left;
                    }
                    curr->m_left = left;
                }else{
                    prev->m_right = right;
                    Tiger* curr = right;
                    while(curr->m_left != nullptr){
                        curr = curr->m_left;
                    }
                    curr->m_left = left;
                }
                delete temp;
                
            }else if(right != nullptr || left != nullptr){//case for node with 1 child
                if(left != nullptr){//checks which subtree the child is in
                    if(prev->m_left == temp){//checks for open spot in parent node
                        prev->m_left = left;
                        delete temp;
                    }else{
                        prev->m_right = left;
                        delete temp;
                    }
                }else{
                    if(prev->m_left == temp){
                        prev->m_left = right;
                        delete temp;
                    }else{
                        prev->m_right = right;
                        delete temp;
                    }
                }
            }else{// no children case
                if(prev->m_left == temp){
                    prev->m_left = nullptr;
                }else{
                    prev->m_right = nullptr;
                }
                delete temp;
                 
            }
        }else{//root node case
            if(right != nullptr && left != nullptr){//case for 2 children
                m_root = right;
                Tiger* curr = right;
                while(curr->m_left != nullptr){
                    curr = curr->m_left;
                }
                curr->m_left = left;
                delete temp;
            }else if(right != nullptr || left != nullptr){//case for 1 child
                if(left != nullptr){
                    m_root = left;
                }else{
                    m_root = right;
                }
                delete temp;
            }else{//case for no children
                delete m_root;
                m_root = nullptr;
            }
            
        }
    }
}
bool Streak::tigerInList(Tiger * aTiger,int id){//checks to see in a node is in the list
    if(aTiger == nullptr){
        return false;
    }else{
        bool right = tigerInList(aTiger->m_left, id);
        if(aTiger->m_id == id){
            return true;
        }else{
            return false;
        }
        bool left = tigerInList(aTiger->m_right, id);
        if(right == true || left == true){//returns true if given node appeared in either subtree
            return true;
        }else{
            return false;
        }
    }
}
