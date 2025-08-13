/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_#2 
Description: Inputs and outputs data to and from files.
Input: file.
Output: file.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "memberType.h"
#include "fileio.h"

using namespace std;

//variables to count entries and valid entries
int j = 0;
int h = 0;


FileClass::FileClass(string file_name){} //constructor with a single parameter

bool getNextField(string &line, int &index, string &subString){

    int in2 = line.find(' ',index);
    //finds the next instance in the file
    if(in2 != -1){
    subString = line.substr(index,in2-1);
    index = in2+1;
    //makes subLine equal what it finds
    }
    return true;
}

unsigned int getMembersDataFromFile(ifstream &inFile, memberType storeMembers[500]){
    string id, firstName, lastName;
    string fileLine, subLine;
    int i = 0;
    int bPurch;
    double amnt, dis; 
    int member;
    

    inFile.open("membersData.txt");//Opens the file and makes sure its there
    if(!inFile.is_open()){
        cout<<"Error : Input file not present : memberdata.txt";
        return -1;
    }
    //grabs the data from the file
    do{
        i = 0;
        getline (inFile,fileLine);
        getNextField(fileLine, i, subLine);
        id = subLine;
        getNextField(fileLine, i, subLine);
        firstName = subLine;
        getNextField(fileLine, i, subLine);
        lastName = subLine;
        getNextField(fileLine, i, subLine);
        bPurch = stoi(subLine);
        getNextField(fileLine, i, subLine);
        amnt = stod(subLine);
        getNextField(fileLine, i, subLine);
        member = stoi(subLine);
        getNextField(fileLine, i, subLine);
        dis = stod(subLine);
        //uses the getNextField function to get and then set the variables
        storeMembers[i].setMemberInfo(id,firstName,lastName,bPurch,amnt,dis,member);
        //sets the memberType data
        j++;//counts the entries
    }while(!inFile.eof());
    
    inFile.close();

    return j;
}

void writeMembersDataToFile(ofstream &outFile, memberType storeMembers[500], unsigned int totalEntry){
 cout <<"ID firstName lastName bookCount purchaseBill "
 <<"lengthOfMembership discountPercentage discountedAmount finalPrice\n";
 for (int q = 0; q < j; q++){
    cout <<storeMembers[q].getID() <<storeMembers[q].getFirstName() <<storeMembers[q].getLastName()
    <<storeMembers[q].getBookCount() <<storeMembers[q].getPurchaseBill() <<storeMembers[q].getLenghtOfMembership()
    <<storeMembers[q].getDiscount() <<storeMembers[q].getDiscountAmount() <<storeMembers[q].getFinalPrice();
    if(!storeMembers[q].checkID(storeMembers[q].getID())){
        cout <<"Invalid ID";
        h++;
    }
    if(!storeMembers[q].checkBookCount(storeMembers[q].getBookCount())){
        cout <<"Invalid Book purchased count";
        h++;
    }
    if(!storeMembers[q].checkAmountSpent(storeMembers[q].getBookCount(),storeMembers[q].getPurchaseBill())){
        cout <<"Invalid purchaseBill";
        h++;
    }
    if(!storeMembers[q].checkMembership(storeMembers[q].getLenghtOfMembership())){
        cout <<"Invalid lengthOfMembership";
        h++;
    }
    if(!storeMembers[q].checkDiscount(storeMembers[q].getDiscount())){
        cout <<"Invalid discountPercentage";
        h++;
    }
 }
 
 //finds the total books sold
 //ignores entries with invalid book count
 int p = 0;
 for (int q = 0; q < j; q++){
    if(storeMembers[q].checkBookCount(storeMembers[q].getBookCount())){
        p += storeMembers[q].getBookCount();
    }
 }

 //finds the total sales amount
int t = 0;
for (int q = 0; q < j; q++){
 t += storeMembers[q].getFinalPrice();
}

//output of the summary
 cout
 <<"Total entries from file : " <<j <<endl
 <<"Valid entries : " <<j-h <<endl
 <<"Total books Sold : " <<p
 <<"TotalSaleAmount : " <<t;
}

FileClass::~FileClass(){} //Destructor
