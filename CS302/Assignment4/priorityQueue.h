#include<iostream>
template< class Type >
class priorityQ {
public :
    priorityQ (int = 10);
    priorityQ ( const priorityQ <Type>&);
    ~priorityQ ();
    const priorityQ <Type>& operator =( const priorityQ < Type >&);
    void insert ( const Type &);
    void deleteHighestPriority ();
    Type getHighestPriority () const;
    bool isEmpty () const;
    void bubbleUp (int);
    void bubbleDown (int);
    int getSize () const ;
private:
    int capacity;
    int items;
    Type* heapArray;
};

//constructor
template< class Type >
priorityQ<Type>::priorityQ (int capacity){
    this->capacity = capacity;
    heapArray = new Type [capacity+1];
    items = 0;
}

//copy constructor
template< class Type >
priorityQ<Type>::priorityQ(const priorityQ& copy){
    this->capacity = copy.capacity;
    this->items = copy.items;
    this->heapArray = new Type [capacity+1];
    for (int x = 0; x < capacity; x++){             // copy over array
        this->heapArray[x] = copy.heapArray[x];
    }
}

//destructor
template< class Type >
priorityQ<Type>::~priorityQ(){
    delete [] heapArray;
}

//= operator overload
template< class Type >
const priorityQ<Type>& priorityQ<Type>::operator=(const priorityQ<Type>& rhs){
    if(&rhs == this){                        //self assignment check
        return *this;
    }
    this->capacity = rhs.capacity;
    this->items = rhs.items;
    this->heapArray = new Type [capacity+1];
    for (int x = 0; x < capacity; x++){             // copy over array
        this->heapArray[x] = rhs.heapArray[x];
    }
    return *this;
}

template< class Type >
void priorityQ<Type>::insert(const Type& element){
    items++;
    if(items>capacity){
        std::cout<<"Error:Reached Maximum Capacity\n";
        return;
    }
    heapArray[items] = element;
    bubbleUp(items);
    return;
}

template< class Type >
void priorityQ<Type>::deleteHighestPriority(){
    if(items==0)                       // if array is empty
        return;
    heapArray[1] = heapArray[items];
    items--;
    bubbleDown(1);
}

template< class Type >
Type priorityQ<Type>::getHighestPriority() const{
    return heapArray[1];
}

template< class Type >
bool priorityQ<Type>::isEmpty() const{
    if(items == 0)
        return true;
    return false;
}

template< class Type >
void priorityQ<Type>::bubbleUp(int index){
    if(index <= 1 || items == 1)
        return;
    while(heapArray[index]>heapArray[index/2]){
        Type temp = heapArray[index];
        heapArray[index] = heapArray[index/2];
        heapArray[index/2] = temp;
        index = index/2;
        if(index <= 1)
            break;                          // reached root
        //TEST THIS
    }
    return;
}

template< class Type >
void priorityQ<Type>::bubbleDown(int index){
    while(2*index <= items){                 // make sure not leaf node
    
        if((2*index)+1 > items){            //if only 1 child
            if(!(heapArray[index]>heapArray[index*2])){
                Type temp = heapArray[index];
                heapArray[index] = heapArray[index*2];
                heapArray[index*2] = temp;
                index = index*2;
            }
            else{
                return;
            }
        }
        else{                               // if 2 children
            if(heapArray[(2*index)] > heapArray[(2*index)+1]){  // if the left node is bigger
                if(!(heapArray[index]>heapArray[index*2])){
                    Type temp = heapArray[index];
                    heapArray[index] = heapArray[index*2];
                    heapArray[index*2] = temp;
                    index = index*2;
                }
                else
                    return;
            }
            else{
                if(!(heapArray[index]>heapArray[(index*2)+1])){ // if the right node is bigger
                    Type temp = heapArray[index];
                    heapArray[index] = heapArray[(index*2)+1];
                    heapArray[(index*2)+1] = temp;
                    index = index*2+1;
                }
                else
                    return;
            }


        }

    }

    return;


}

template< class Type >
int priorityQ<Type>::getSize() const{
    return items;
}