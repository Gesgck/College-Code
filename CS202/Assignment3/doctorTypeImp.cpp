/*
Name:Alec Zheng,NSHE_ID_#2001982564,COURSE_SECTION 1004,ASSIGNMENT_#3
Description:Implamentation file for doctorType.h.
Input: doctor info.
Output: doctor info.
*/
#include "doctorType.h"
#include "personType.h"
#include <iostream>

doctorType::doctorType(string first, string last, string spl){
    setName(first,last);
    setSpecialty(spl);
}
//parameterized constructor

void doctorType::setSpecialty(string spl){
    specialty = spl;
    if(specialty == ""){
        cout <<"Specialty is missing for Dr." <<getFirstName() <<endl;
    }
}
//Function to set specialty according to the parameters

string doctorType::getSpecialty() const{
    return specialty;
}
//Function to return the specialty

void doctorType::print() const{
    cout <<"Dr." <<getFirstName() <<" " <<getLastName()
    <<"; Specialty: " <<specialty;
}