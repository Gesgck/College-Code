/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_#2
Description: Inputs and outputs data to and from files.
Input: file.
Output: file.
*/

#include<iostream>
#include"memberType.h"
#include"fileio.h"

using namespace std;

memberType::memberType(){
    memberID = " ";
    firstName = " ";
    lastName = " ";

    booksPurchased = 0;
    amountSpent = 0;
    booksDiscount = 0;
    lengthOfMembership = 0;
    //all values initialized
}

void memberType::setMemberInfo(string ID, string fName, string lName,
                       int bPurchased, double amount, double discount, int membership)
{
    //checks the variables and gets the setters if it passes
        setMemberID(ID);
        setName(fName,lName);
        booksPurchased = bPurchased;
        amountSpent = amount;
        if(booksPurchased >= 4){
            booksDiscount = discount + 4;
        }
        else{
            booksDiscount = discount;
        }
        lengthOfMembership = membership;

}
void memberType::setMemberID(string str){
    memberID = str;
}
void memberType::setName(string, string){

}
bool memberType::checkID(string str){
if(str.size() != 6){
    return false;
}
for (int i = 0; i < 3; i++){
    if(!isalpha(str[i])){
        return false;
    }
}
for (int i = 3; i < 6; i++){
    if(!isdigit(str[i])){
        return false;
    }
}
    return true;
}
bool memberType::checkBookCount(int booksCount){
    if(booksCount >= 0){
        return true;
    }
        return false;   
}
bool memberType::checkAmountSpent(int booksCount, double amountSpent){
    //check for the two conditions labled in the assignment
    if(booksCount <= 0 && amountSpent > 0){
        return false;
    }
    else if (booksCount > 0 && amountSpent <= 0){
        return false;
    }
    else{
        return true;
    }
}
bool memberType::checkMembership(int membership){
 if (lengthOfMembership >= 0){
    return true;
 }
 return false;
}
bool memberType::checkDiscount(int discount){
    if (discount >=0){
        return true;
    }
    return false;
}

string memberType::getID() const{
    return memberID;
}
string memberType::getFirstName() const{
    return firstName;
}
string memberType::getLastName() const{
    return lastName;
}
int memberType::getBookCount() const{
    return booksPurchased;
}
double memberType::getPurchaseBill() const{
    return amountSpent;
}
int memberType::getLenghtOfMembership() const{
    return lengthOfMembership;
}
double memberType::getDiscount() const{
    return booksDiscount;
}
double memberType::getDiscountAmount() const{
    return (amountSpent / 100) * booksDiscount;
}
double memberType::getFinalPrice() const{
    return (amountSpent-getDiscountAmount());
}

memberType::~memberType(){}
