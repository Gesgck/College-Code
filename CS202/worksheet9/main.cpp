#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
};

class singlyLinkedLists{
    Node *head; //This is the 1st node
    Node *tail; //This is the last Node
    int nodeCount;
public:
    ~singlyLinkedLists();
    void delete_at_tail();
    void displayLLinReverse();
};

singlyLinkedLists::~singlyLinkedLists(){

Node *temp = head;
Node *temp2;
while(temp->next != nullptr){
    temp2 = temp;
    temp = temp->next;
    delete temp2;
}

}

void singlyLinkedLists::delete_at_tail(){

    Node *temp = head;
    int count = 1;
    if(tail==nullptr){
        cout<<"List is empty!\n";
        return;
    }
    else{
        delete tail;
        while(count != nodeCount-1){
            temp = temp->next;
            count++;
        }
        temp->next = nullptr;
        tail = temp;
        nodeCount -= 1;
    }
}

void singlyLinkedLists::displayLLinReverse(){

    Node *temp = head;
    int count = 1;
    static int scount = nodeCount;
    if(scount == 0){
        return;
    }
    else{
        while(count != scount){
            temp = temp->next;
            count++;
        }
        cout <<temp->data <<" ";
        scount--;
        return displayLLinReverse();
    }

}