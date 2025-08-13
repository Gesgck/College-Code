/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#8
Description: Pride pronouns in linked list.
Input: pronouns.
Output: pronouns.
*/
#include <iostream>
#include<fstream>

using namespace std;

template<class T>
class Node{//Node class for doublely linked list
    public:
        T data;//template data for node
        Node<T> *next;
        Node<T> *prev;
};

template<class T>
class DoublyLinkedList{
    //private members of the list
    Node<T> *head;
    Node<T> *tail;
    public:
    DoublyLinkedList();//Constructor
    ~DoublyLinkedList();//Destructor
    void insert(T);//To insert elements
    bool searchDelete(T);//To find and remove elements
    void print();//To print the list
    void backwardsPrint();//To print the list backwards
};

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(){//constructor
    head = nullptr;
    tail = nullptr;
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList(){
    //deletion of all values of list
    if(head!=nullptr&&tail!=nullptr){//if list is not empty
        Node<T> *temp = head;
        Node<T> *temp2;
        while(temp!=nullptr){
            //temp 2 so deletion of temp does not 
            //make the list inaccessible
            temp2 = temp->next;
            delete temp;
            temp = temp2;
        }
    }
}

template<class T>
void DoublyLinkedList<T>::insert(T item){
    Node<T> *temp = new Node<T>;
    temp->data = item;
    if(head==nullptr){//if list is empty
                      //both head and tail are now node
        temp->next = nullptr;
        temp->prev = nullptr;
        head = temp;
        tail = temp;
        return;
    }
    //alphabetical sorting of pronouns
    Node<T> *ptr = head;
    if(temp->data < head->data){
        //if value is smaller than head
        head = temp;
        temp->next = ptr;
        ptr->prev = temp;
        return;
    }
    while(ptr->next!=nullptr){//if value is not smaller than head
        if(ptr->next->data >= temp->data&&ptr->data <= temp->data){
            //check if next data is bigger or same
            //and if prev data is less or same
            temp->prev = ptr;
            temp->next = ptr->next;
            ptr->next = temp;
            ptr->next->next->prev = temp;
            return;
        }
        //if data is needs to keep going
        ptr = ptr->next;
    }
    //if the value is last in the list
    temp->prev = ptr;
    temp->next = nullptr;
    ptr->next = temp;
    tail = temp;
}

template<class T>
bool DoublyLinkedList<T>::searchDelete(T find){
    //Deletes a specified value
    Node<T> *temp = head;
    Node<T> *del;//node address to delete
    while(temp!=nullptr){//goes through entire list
        if((temp->data == find)&&(temp!=head)&&(temp!=tail)){
            //if value is neither head or tail
            del = temp;
            temp = temp->prev;
            temp->next = del->next;
            temp = del->next;
            temp->prev = del->prev;
            delete del;

        }
        else if(temp->data == find&&temp==head&&temp!=tail){
            //if value is the head
            del = temp;
            temp = temp->next;
            head = temp;
            temp->prev = nullptr;
            delete del;
        }
        else if(temp->data == find&&temp==tail&&temp!=head){
            //if value is the tail
            del = temp;
            temp = temp->prev;
            tail = temp;
            temp->next = nullptr;
            delete del;
        }
        else if(temp->data == find&&temp==head&&temp==tail){
            //if value is last one left
            //delete and break loop
            delete temp;
            head = nullptr;
            tail = nullptr;
            break;
        }
        else{
            //if value is not found in current node
            //continue to next node
            temp = temp->next;
        }
    }
    return true;//Why is this a bool and not void?
}

template<class T>
void DoublyLinkedList<T>::print(){
    if(head==nullptr){//if list is empty
        cout<<".\n";
        return;
    }
    Node<T> *temp;
    temp = head;
    while(temp != nullptr){//data a to z
        cout<<temp->data <<" -> ";
        temp = temp->next;
    }
    cout<<".\n";
}

template<class T>
void DoublyLinkedList<T>::backwardsPrint(){
    if(head==nullptr){//if list is empty
        cout<<".\n";
        return;
    }
    Node<T> *temp = tail;
    while(temp != nullptr){//data z to a
        cout<<temp->data <<" -> ";
        temp = temp->prev;
    }
    cout<<".\n";
}

template<class T>
void readData(DoublyLinkedList<T> &DLL){//reads data from file to list
    string data;
    ifstream iFile("pronouns.txt");//fixed file to read from
    iFile >>data;//simple input for data
    while(data != "Source:"){//loop stops at end of list
        DLL.insert(data);//uses insert function from DLL
        iFile >>data;
    }
    iFile.close();
    //closes file
}
