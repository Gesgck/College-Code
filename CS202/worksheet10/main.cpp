#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* next;
};

class stackLinkedList{
    private:
        Node* head;
    public:
        stackLinkedList();
        ~stackLinkedList();
        bool isEmpty();
        void insert_node_at_top(int);
        void remove_node_from_top();
        int nodeCount();
        void printStackList();
        void showTop();
        void printStackListReverseRecursion();
        void printStackListReverse();
};

stackLinkedList::stackLinkedList(){
    head = nullptr;
}

stackLinkedList::~stackLinkedList(){
    if(head != nullptr){
        Node* temp = head;
        Node* temp2;
        while(temp != nullptr){
            temp2 = temp->next;
            delete temp;
            temp = temp2;
        }
    }
}

bool stackLinkedList::isEmpty(){
    if(head == nullptr){
        return true;
    }
    return false;

}

void stackLinkedList::insert_node_at_top(int var){
    Node *temp = new Node;
    temp->data = var;
    if(head != nullptr){
        temp->next = head;
    }
    else{
        temp->next = nullptr;
    }
    head = temp;
}

void stackLinkedList::remove_node_from_top(){
    Node *temp = head;
    head = head->next;
    delete temp;
}

int stackLinkedList::nodeCount(){
    if(head==nullptr)
        return 0;
    int count = 0;
    Node *temp = head;
    while(temp != nullptr){
        count++;
        temp = temp->next;
    }
    return count;
}

void stackLinkedList::printStackList(){
    if(head==nullptr){
        cout<<"Stack is empty\n";
        return;
    }
    Node* temp = head;
    while(temp != nullptr){
        cout<<temp->data <<" ";
        temp = temp->next;
    }
    cout<<endl;
}

void stackLinkedList::showTop(){
    if(head==nullptr){
        cout<<"Stack is empty\n";
        return;
    }
    cout<<head->data <<endl;
}

void stackLinkedList::printStackListReverseRecursion(){
    if(head==nullptr){
        cout<<"Stack is empty\n";
        return;
    }
    static int count = nodeCount();
    Node* temp = head;
    if(count==0){
        cout<<endl;
        return;
    }
    for(int i = 1; i < count; i++)
        temp = temp->next;
    cout<<temp->data <<" ";
    count--;
    return(printStackListReverseRecursion());
}

void stackLinkedList::printStackListReverse(){
    if(head==nullptr){
        cout<<"Stack is empty\n";
        return;
    }
    int count = nodeCount();
    while(count > 0){
        int track = 1;
        Node* temp = head;
        while(track < count){
            temp = temp->next;
            track++;
        }
        cout<<temp->data <<" ";
        count--;
    }
    cout<<endl;
}