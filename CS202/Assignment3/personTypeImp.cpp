/*
Name:Alec Zheng,NSHE_ID_#2001982564,COURSE_SECTION 1004,ASSIGNMENT_#3
Description:Implamentation file for personType.h.
Input: fist and last names.
Output: first and last names.
*/
#include <iostream>
#include "personType.h"

using namespace std;

personType::personType(string first, string last){
    setName(first,last);
}
//parameterized constructor

void personType::setName(string first, string last){
    firstName = first;
    lastName = last;
}
//Function to set firstName and lastName

string personType::getFirstName() const{
    return firstName;
}
//Function to return the first name.

string personType::getLastName() const{
    return lastName;
}
//Function to return the last name.

void personType::print() const{
    cout <<firstName <<lastName;
}
//Function to output the first name and last name