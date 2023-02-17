// CMSC 341 - Fall 2022 - Project 3
#include "iqueue.h"
IQueue::IQueue(prifn_t priFn, HEAPTYPE heapType){
    m_priorFunc = priFn;
    m_heapType = heapType;
    m_size = 0;
    m_heap = nullptr;
}

IQueue::~IQueue(){
    clear();
}

IQueue::IQueue(const IQueue& rhs){
    m_heapType = rhs.m_heapType;
    m_priorFunc = rhs.m_priorFunc;
    m_size = 0;
    m_heap = nullptr;
    m_heap = copy(rhs.m_heap);
    m_size = numCrops();
}

IQueue& IQueue::operator=(const IQueue& rhs){
    if(this != &rhs){
        clear();//clears old tree 
        m_heapType = rhs.m_heapType;//sets member varibles to new values
        m_priorFunc = rhs.m_priorFunc;
        m_size = 0;
        m_heap = copy(rhs.m_heap);
        m_size = numCrops();
    }
    return *this;
}

void IQueue::insertCrop(const Crop& crop) {
    Node *temp = new Node(crop);
    m_heap = merge(m_heap, temp);
    m_size += 1;
}

Crop IQueue::getNextCrop() {
    Crop aCrop;
    if(m_size != 0 && m_heap != nullptr){//checks if the heap is empty
        Node *left = m_heap->m_left;//takes left and right children
        Node *right = m_heap->m_right;
        aCrop = m_heap->m_crop;
        delete m_heap;
        m_heap = merge(left,right);
        m_size -= 1;//decreases the size by 1
    }else{
        throw out_of_range("out_of_range");
    }
    return aCrop;
}

void IQueue::mergeWithQueue(IQueue& rhs) {
    if(this != &rhs){
        if(m_heapType == rhs.m_heapType){//throws error if heaps are different types
            merge(m_heap, rhs.m_heap);
            rhs.clear();
        }else{
            throw domain_error("domain_error");
        }
    }
}
void IQueue::clear() {
    while(m_size != 0){//deletes top node until queue is empty
        getNextCrop();
    }
    m_heap = nullptr;
}

int IQueue::numCrops() const{
    int numCrops = countCrops(m_heap);
    return numCrops;
}

void IQueue::printCropsQueue() const {
    print(m_heap);
}

prifn_t IQueue::getPriorityFn() const {
    return m_priorFunc;
}

void IQueue::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {
    Crop crop[m_size];
    m_priorFunc = priFn;
    m_heapType = heapType;
    int count = 0;
    while(m_size != 0){//stores each crop into an array to insert later
        Crop aCrop = getNextCrop();
        crop[count] = aCrop;
        count += 1;
    }
    while(m_size != count){//reinserts crops with new function and or heap type
        Node *curr = new Node(crop[m_size]);
        m_heap = merge(m_heap,curr);
        m_size = numCrops();
    }
}

void IQueue::dump() const {
    if (m_size == 0) {
        cout << "Empty skew heap.\n" ;
    } else {
        dump(m_heap);
        cout << endl;
    }
}

void IQueue::dump(Node *pos) const {
    if ( pos != nullptr ) {
        cout << "(";
        dump(pos->m_left);
        cout << m_priorFunc(pos->m_crop) << ":" << pos->m_crop.getCropID();
        dump(pos->m_right);
        cout << ")";
    }
}

ostream& operator<<(ostream& sout, const Crop& crop) {
    sout << "Crop ID: " << crop.getCropID() 
        << ", current temperature: " << crop.getTemperature()
        << ", current soil moisture: " << crop.getMoisture() << "%"
        << ", current time: " << crop.getTimeString()
        << ", plant type: " << crop.getTypeString();
    return sout;
}

ostream& operator<<(ostream& sout, const Node& node) {
    sout << node.getCrop();
    return sout;
}
Node * IQueue::merge(Node *root, Node *newNode){
    if(root == nullptr){//returns the new node if tree is empty
        return newNode;
    }else if(newNode == nullptr){//
        return root;
    }else if(m_heapType == MINHEAP){
        if(m_priorFunc(root->m_crop) > m_priorFunc(newNode->m_crop)){//checks which node has the higher priority
            swap(root,newNode);
        }
        swap(root->m_left,root->m_right);//swaps subtrees
        root->m_left = merge(root->m_left, newNode);//recursive merges new node with heap
    }else{//case for maxheap
        if(m_priorFunc(root->m_crop) < m_priorFunc(newNode->m_crop)){
            swap(root, newNode);
        }
        swap(root->m_left,root->m_right);
        root->m_left = merge(root->m_left, newNode);
    } 
    return root; 
}
void IQueue::print(Node *root) const{
    if(root == nullptr){
        return;
    }else{
        cout <<"[" << m_priorFunc(root->m_crop) << "]"<< root->m_crop << endl;
        print(root->m_left);
        print(root->m_right);
    }
}

int IQueue::countCrops(Node *root) const{ 
    if(root == nullptr){
        return 0;
    }else{//adds 1 for each node traveled to
        int left = countCrops(root->m_left);
        int right = countCrops(root->m_right);
        int num = 1 + right + left;
        return num;
    }
}

Node * IQueue::copy(Node *root){
    if(root == nullptr){
        return nullptr;
    }else{
        Node *temp = new Node(root->m_crop);//inserts new node with the crop of given tree
        temp->m_left = copy(root->m_left);
        temp->m_right = copy(root->m_right);
        return temp;
    }
}

bool IQueue::minProperty(Node *root){
    if(root == nullptr){
        return true;
    }else{//checks whether child nodes have lower priority than parents
        if(root->m_left != nullptr){
            if(m_priorFunc(root->m_crop) > m_priorFunc(root->m_left->m_crop)){
                return false;
            }
        }
        if(root->m_right != nullptr){
            if(m_priorFunc(root->m_crop) > m_priorFunc(root->m_left->m_crop)){
                return false;
            }
        }
        bool left = minProperty(root->m_left);
        bool right = minProperty(root->m_right);
        if(left == true && right == true){
            return true;
        }else{
            return false;
        }
    }
}

bool IQueue::maxProperty(Node *root){
    if(root == nullptr){
        return true;
    }else{
        if(root->m_left != nullptr){//checks whether child nodes have lower priority than the parents
            if(m_priorFunc(root->m_crop) < m_priorFunc(root->m_left->m_crop)){
                return false;
            }
        }
        if(root->m_right != nullptr){
            if(m_priorFunc(root->m_crop) < m_priorFunc(root->m_left->m_crop)){
                return false;
            }
        }
        bool left = maxProperty(root->m_left);
        bool right = maxProperty(root->m_right);
        if(left == true && right == true){
            return true;
        }else{
            return false;
        }
    }
}