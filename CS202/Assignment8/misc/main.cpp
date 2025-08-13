#include<iostream>
#include<string>
#include<fstream>
#include "prideImp.cpp"
using namespace std;

int main(){
    DoublyLinkedList<string> DLL;
    DLL.insert("ge"); DLL.insert("ge"); DLL.insert("gg");
    DLL.print(); //should do ge -> ge -> gg
    DLL.searchDelete("ge"); DLL.searchDelete("gg"); 
    //deletes all instances so both ge are gone, also gg
    DLL.print(); //empty
    DLL.backwardsPrint(); //empty
    readData(DLL); //read in pronouns.txt
    DLL.print(); //should print pronouns sorted alphabeticall a->z
    cout << endl << endl;
    DLL.backwardsPrint(); //z->a reverse alphabetical
    cout << "\nPride is for everyone." << endl; // <3
    return 0;
}

