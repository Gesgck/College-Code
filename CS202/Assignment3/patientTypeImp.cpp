/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#3
Description: Implamentation file for patientType.h.
Input: data for patient.
Output: stuff.
*/

#include "patientType.h"
#include "dateType.h"
#include <iostream>

doctorType temp("temp","temp","temp");

patientType::patientType(string id, string fName, string lName,
                int bDay, int bMth, int bYear,
                string docFrName, string docLaName, string docSpl):attendingPhysicain(temp)
    {
        setInfo(id,fName,lName,bDay,bMth,bYear,
                docFrName,docLaName, docSpl);
    }
//Parameterized Constructor

void patientType::setInfo(string id, string fName, string lName,
                int bDay, int bMth, int bYear,
                string docFrName, string docLaName, 
                string docSpl)
    {
        setName(fName,lName);
        setBirthDate(bDay,bMth,bYear);
        setDoctorName(docFrName,docLaName);
        setDoctorSpl(docSpl);
        if(checkPatientID(id)){
        setID(id);
        }
        else{
            cout <<"Error: " <<id <<" is invalid patientID for "
            <<getFirstName() <<endl;
        };
        if(attendingPhysicain.getSpecialty() == ""){
            cout <<"Doctor Specialty is missing for patient "
            <<getFirstName() <<endl;
        }
        
    }
//Function to setInfo of a patient

void patientType::setID(string id){
        ID = id;

}
//Function to set the ID according to the parameter

string patientType::getID() const{
    return ID;
}
//Function to return the ID

void patientType::setBirthDate(int bDay, int bMth, int bYear){
    dateOfBirth.setDate(bDay,bMth,bYear);
    if(bMth < 1 || bMth > 12){
        cout <<"Error: Invalid month entry for " <<getFirstName() <<endl;
    }
    if(bYear < 1910 || bYear > 2022){
        cout <<"Error: Invalid year entry for " <<getFirstName() <<endl;
    }
}
//Function to set the birthDate

int patientType::getBirthYear() const{
    return dateOfBirth.getYear();
}
//Function to return the year

void patientType::setDoctorName(string fName, string lName){
    attendingPhysicain.setName(fName,lName);
}
//Function to set the doctor's first name and last name

void patientType::setDoctorSpl(string spl){
    attendingPhysicain.setSpecialty(spl);
}
//Function to set the doctor's specialty according to the parameter

string patientType::getDoctorFName() const{
    return attendingPhysicain.getFirstName();
}
//Function to return doctor's first name.

bool patientType::checkPatientID(string patientIDTmp) const{
    if(patientIDTmp.size() != 6){
        return false;
    }
    if (int(patientIDTmp[0]) < 65||int(patientIDTmp[0]) > 90){
        return false;
    }
    for(int i=1; i<6; i++){
        if(!isdigit(patientIDTmp[i])){
            return false;
        }
    }
    return true;
}
//Function to check patientID

void patientType::print() const{
    cout <<"\n************************"
    <<"*****************************************\n"
    <<"Patient:" <<getFirstName() <<" " <<getLastName()
    <<"\nPatient ID:" <<getID() <<"\nAttending Physician: dr." 
    <<getDoctorFName() <<" " <<attendingPhysicain.getLastName()
    <<"; Specialty: " <<attendingPhysicain.getSpecialty() <<endl
    <<"__________________________________________________"
    <<endl;
}
//Function to output the first name and last name of patient