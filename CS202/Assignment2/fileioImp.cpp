/*
Name:Alec Zheng,NSHE_ID_#2001982564,COURSE_SECTION 1007,ASSIGNMENT_#2 
Description: Inputs and outputs data to and from files.
Input: file.
Output: file.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include "memberType.h"
#include "fileio.h"

using namespace std;

FileClass::FileClass(string file_name){
    //opens and checks file
    inFile.open(file_name);
    if(!inFile){
        cout<<"###########################"
        <<"################################"
        <<endl
        <<"Error : Input file not present : " <<file_name
        <<endl
        <<"###########################"
        <<"################################";
        exit(0);
        //exits if no file
    }
} //constructor with a single par

bool getNextField(string &line, int &index, string &subString){

    int in2 = line.find(' ',index);
    //finds the next instance in the file
    if(in2 == -1){
        subString = line.substr(index);  
    }
    else{
        subString = line.substr(index,in2-index);
    }
    index = in2+1;
    //makes subLine equal what it finds
    return true;
}

unsigned int getMembersDataFromFile(ifstream &inFile,
memberType storeMembers[500]){
    string id, firstName, lastName;
    string fileLine, subLine;
    int i = 0;
    int bPurch;
    double amnt, dis; 
    int member;
    int j = 0;
    
    //grabs the data from the file
    getline (inFile,fileLine);
    do{
        i = 0;
        //i is index
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
        //uses the getNextField function
        storeMembers[j].setMemberInfo(id,firstName,lastName,bPurch,
        amnt,dis,member);
        //sets the memberType data
        j++;//counts the entries
    }while(!inFile.eof());
    
    inFile.close();

    return j;
}

void writeMembersDataToFile(ofstream &outFile, 
memberType storeMembers[500],unsigned int totalEntry){
    //outputs data to file
    outFile.open("membersData_output.txt");
 int h = 0;//counts failed entries
 outFile <<"ID firstName lastName bookCount purchaseBill "
 <<"lengthOfMembership discountPercentage discountedAmount finalPrice\n";
 for (int q = 0; q < totalEntry; q++){
    outFile <<fixed <<setprecision(2) 
    <<storeMembers[q].getID() 
    <<' ' <<storeMembers[q].getFirstName() 
    <<' ' <<storeMembers[q].getLastName()
    <<' ' <<storeMembers[q].getBookCount() 
    <<' ' <<storeMembers[q].getPurchaseBill() 
    <<' ' <<storeMembers[q].getLenghtOfMembership()
    <<' ' <<storeMembers[q].getDiscount();
    if(!storeMembers[q].checkID(storeMembers[q].getID())){
        outFile <<"\tInvalid ID";
        storeMembers[q].setMemberID("-1");
        h++;
    }
    else if(!storeMembers[q].
    checkBookCount(storeMembers[q].getBookCount())){
        outFile <<"\tInvalid Book purchased count";
        storeMembers[q].setMemberID("-1");
        h++;
    }
    else if(!storeMembers[q].
    checkAmountSpent(storeMembers[q].getBookCount(),
    storeMembers[q].getPurchaseBill())){
        outFile <<"\tInvalid purchaseBill";
        storeMembers[q].setMemberID("-1");
        h++;
    }
    else if(!storeMembers[q].checkMembership
    (storeMembers[q].getLenghtOfMembership())){
        outFile <<"\tInvalid lengthOfMembership";
        storeMembers[q].setMemberID("-1");
        h++;
    }
    else if(!storeMembers[q].checkDiscount
    (storeMembers[q].getDiscount())){
        outFile <<"\tInvalid discountPercentage";
        storeMembers[q].setMemberID("-1");
        h++;
    }
    if(storeMembers[q].getID() != "-1"){
        outFile <<' ' <<storeMembers[q].getDiscountAmount() 
        <<' ' <<storeMembers[q].getFinalPrice();
    }
    outFile <<endl;
 }
 
 //finds the total books sold
 //ignores entries with invalid book count
 int p = 0;
 for (int q = 0; q < totalEntry; q++){
    if(storeMembers[q].getID() != "-1"){
        p += storeMembers[q].getBookCount();
    }
 }

 //finds the total sales amount
double t = 0;
for (int q = 0; q < totalEntry; q++){
    if(storeMembers[q].getID() != "-1"){
        t += ceil(storeMembers[q].getFinalPrice() * 100.0) / 100.0;
    }
}
t -= .01;

//output of the summary
 outFile
 <<"\n------------+------------"
 <<"+------------+------------"
 <<"+------------+------------"
 <<"+------------+------------+"
 <<"\nTotal entries from file : " 
 <<totalEntry <<endl
 <<"Valid entries : " <<totalEntry-h <<endl
 <<"Total books Sold : " <<p <<endl
 <<"TotalSaleAmount : " <<t <<endl
 <<"------------+------------+------------"
 <<"+------------+------------+------------"
 <<"+------------+------------+";
 outFile.close();
}



FileClass::~FileClass(){} //Destructor
