/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_#2 
Description: read a file and sort it into a linked list.
Input: file.
Output: sorted linked list.
*/

#include <iostream>
#include <fstream>
#include <iomanip>

template <typename T>
class LL{
    // contents of each node
    struct Node{
        T data;
        Node *prev;
        Node *next;
    };
    // iterator class to allow access of each node in main
    public :
    class Iterator{
        public:
            friend class LL;
            Iterator ();
            Iterator (Node *);
            T operator *() const;
            const Iterator & operator ++(int);
            const Iterator & operator --(int);
            bool operator ==(const Iterator &) const;
            bool operator !=(const Iterator &) const;
        private:
            Node *current;
    };
    LL ();
    LL (const LL <T>&);
    const LL <T>& operator =(const LL <T>&);
    ~ LL ();
    void headInsert (const T &);
    void tailInsert (const T &);
    Iterator begin () const;
    Iterator end () const;
    void swapNodes (Iterator &, Iterator &);
    private:
    Node *head;
    Node *tail;
};

template <typename T>
LL<T>::LL(){
    head = nullptr;
    tail = nullptr;
}

template <typename T>
LL<T>::LL(const LL<T>& copy){                                       //deep copy constructor
    this->head = nullptr;
    this->tail = nullptr;
    if(copy.head && copy.tail == nullptr){                          //if copy is empty
        return;                                                     //return
    }
    Node *temp;
    temp = new Node;
    temp->prev = nullptr;
    this->head = temp;
    Node *temp2 = copy.head;
    while(temp2 != nullptr){
        temp->data = temp2->data;
        if(temp2->next != nullptr){
            temp->next = new Node;
            temp->next->prev = temp;
            temp = temp->next;
        }
        temp->next = nullptr;
        this->tail = temp;
        temp2 = temp2->next;
    }
    return;
}

template <typename T>
const LL<T>& LL<T>::operator=(const LL<T>& rhs){                    //deallocate and deep copy
    if(this == &rhs){                                               //self assignment check
        return *this;
    }
    Node *temp = this->head;
    while(this->head != nullptr){                                   //run through and delete
      this->head = this->head->next;
      delete temp; 
      temp = this->head;
    }
    temp = new Node;
    temp->prev = nullptr;
    this->head = temp;
    Node *temp2 = rhs.head;
    while(temp2 != nullptr){
        temp->data = temp2->data;
        if(temp2->next != nullptr){
            temp->next = new Node;
            temp->next->prev = temp;
            temp = temp->next;
        }
        temp->next = nullptr;
        this->tail = temp;
        temp2 = temp2->next;
    }
    return *this;
}

template <typename T>
LL<T>::~LL(){
    Node *temp = this->head;
    while(head != nullptr){                                           //run through and delete 
        head = head->next;
        delete temp;
        temp = head;
    }
}

template <typename T>
void LL<T>::headInsert(const T& item){                              //head insert
    Node *temp = new Node;
    temp->data = item;
    temp->prev = nullptr;
    if(head==nullptr && tail==nullptr){                             //if list is empty
        temp->next = nullptr;
        head = temp;
        tail = temp;
        return;
    }
    temp->next = head;                                              //else move things around
    head->prev = temp;
    head = temp;
    return;
}

template <typename T>
void LL<T>::tailInsert(const T& item){                              //tail insert
    Node *temp = new Node;
    temp->data = item;
    temp->next = nullptr;
    if(head==nullptr && tail==nullptr){                             //if list is empty
        temp->prev = nullptr;
        head = temp;
        tail = temp;
        return;
    }
    tail->next = temp;                                              //else move things around
    temp->prev = tail;
    tail = temp;
    return;
}

template <typename T>
typename LL<T>::Iterator LL<T>::begin() const{                      //move iterator to begining
Iterator obj(this->head);
return obj;
}

template <typename T>
typename LL<T>::Iterator LL<T>::end() const{                        //move iterator to the end
Iterator obj(this->tail);
return obj;
}

template <typename type>
void LL<type>::swapNodes(Iterator& it1, Iterator& it2){             //swap nodes
Node *i1Left = it1.current->prev;
Node *i1Right = it1.current->next;
Node *i2Left = it2.current->prev;
Node *i2Right = it2.current->next;
if(it1.current == head && it2.current == tail){                     //if swaping head and tail
    head = it2.current;
    tail = it1.current;
}
if(it1.current == head && it2.current != tail){                     //if it1 == head
    head = it2.current;
}
if(it2.current == tail && it1.current != head){                     //if it2 == tail
    tail = it1.current;
}

if(i1Right == it2.current){                                         //if swaping nodes next to eachother
    it2.current->next = it1.current;
    it1.current->prev = it2.current;
    it2.current->prev = i1Left;
    it1.current->next = i2Right;
    if(it2.current != head)
        i1Left->next = it2.current;
    if(it1.current != tail)
        i2Right->prev = it1.current;
}
else{                                                               //if swaping nodes not next to eachother
    it1.current->prev = i2Left;
    it2.current->next = i1Right;
    it1.current->next = i2Right;
    it2.current->prev = i1Left;
    i2Left->next = it1.current;
    i1Right->prev = it2.current;
    if(it2.current != head)
        i2Left->next = it1.current;
    if(it1.current != tail)
        i2Right->prev = it1.current;
}

return;
}

template <typename T>
LL<T>::Iterator::Iterator(){                                            //default constructor
    current = nullptr;
}

template <typename T>
LL<T>::Iterator::Iterator(Node* ptr){                                   //constructor with a node
    current = ptr;
}

template <typename T>
T LL<T>::Iterator::operator*() const{                                   //* operator
    return current->data;
}

template <typename T>
const typename LL<T>::Iterator& LL<T>::Iterator::operator++(int){       //++ operator
    this->current = this->current->next;
    return *this;
}

template <typename T>
const typename LL<T>::Iterator& LL<T>::Iterator::operator--(int){       //-- operator
    this->current = this->current->prev;
    return *this;
}

template <typename T>
bool LL<T>::Iterator::operator==(const Iterator& rhs) const{            //== operator
    if(this->current == rhs.current){
        return true;
    }
    return false;
}

template <typename T>
bool LL<T>::Iterator::operator!=(const Iterator& rhs) const{            //!= operator
    if(this->current != rhs.current){
        return true;
    }
    return false;
}

int main(){
    std::ifstream inFile;
    std::string fileName;

    std::cout<<"Enter File Name: ";                                     //user inputs file
    std::cin>>fileName;
    std::cout<<'\n';

    inFile.open(fileName);
    if(!inFile){                                                        //check for file
        std::cout<<"Error: File Not Found, Exiting\n";
        exit(0);
        //exits if no file
    }

    std::cout<<"Reading File...\n";                                     //file found
    LL<int> obj;
    std::string fileInt;
    int data;

    while(!inFile.eof()){                                               //read from file
        getline(inFile,fileInt);
        try{
            data = std::stoi(fileInt);
        }
        catch(...){                                                     //ignore junk data
            continue;
        }
        obj.tailInsert(data);
    }
    inFile.close();                                                     //reading finished

    LL<int>::Iterator it1, it2, it3, it4, it5, nil;                     //iterator declarations
    bool sorted = false;                                                //bool to keep track of if the LL is sorted or not

    it1 = obj.begin();                                                  //it1 keeps track of what is sorted at the begining
    it2 = obj.end();                                                    //it2 keeps track of sorted at the end
    
    while(sorted != true){
        sorted = true;
        it3 = it1;
        //forwards
        while(it3 != it2){                                              //forward sort loop
            it4 = it3;
            it4++;                                                      //it4 = it3 next
            if(*it3>*it4){                                              //if i > i+1
            if(it3 == it1 && it4 == it2){
                    obj.swapNodes(it3,it4);
                    sorted = true;
                    goto loopExit;
                }
                sorted = false;
                if(it3 == it1)                                          //checks to keep sorted nodes consistent
                    it1 = it4;
                if(it4 == it2)
                    it2 = it3;
                obj.swapNodes(it3,it4);
            }
            else
                it3++;
        }
        it2--;                                                         //move it2 back 1 as it is sorted

        //backwards
        it4 = it2;
        while(it4 != it1){                                              //backwards sort loop
            it3 = it4;
            it3--;
            if(*it3>*it4){                                              //if i-1 > i
            if(it3 == it1 && it4 == it2){
                    obj.swapNodes(it3,it4);
                    sorted = true;
                    goto loopExit;
                }
            sorted = false;
                if(it3 == it1)                                          //checks to keep sorted nodes consistent
                    it1 = it4;
                if(it4 == it2)
                    it2 = it3;
                obj.swapNodes(it3,it4);
            }
            else
                it4--;
        }
        it1++;                                                          //it1 moves as it is sorted
    }
    loopExit:

    std::cout<<"Sorted List:\n";
    for (it1 = obj.begin(); it1 != nil; it1++)
        std::cout << *it1 << " ";

    return 0;
}