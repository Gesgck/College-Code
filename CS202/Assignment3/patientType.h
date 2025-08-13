/*
Name: KISHORE CHIDELLA, NSHE: ABC123, CLASS-SECTION: CS202, ASSIGNMENT:3
Description: To set the patients and doctors data; print the bill of a 
patient
Input: Develop personType class that can be useful to set first and last 
names from personType class; set the patients data using setters or 
constructors from patienType class; set the doctors data using setters 
or constructors from doctorType class; set the birth date(mm, dd, year) 
of a patient from dateType class; set the charges(pharmacy, room rent, 
doctor fee) of a patient from billType class
Output: Write output to console; print error messages for Invalid IDs,
missing specialty, invalid biryh month and year;
check the sample output for reference
*/ 
#ifndef patientType_H
#define patientType_H

#include <string>
#include "doctorType.h"
#include "personType.h"
#include "dateType.h"

 
using namespace std;

class patientType: public personType
{
public: 
    void print() const;
    //Function to output the first name and last name of patient
    //Function to output doctors first name, last name, and specialty
    //using doctorType object(attendingPhysicain)

    void setInfo(string id = "", string fName = "", string lName = "",
                int bDay = 1, int bMth = 1, int bYear = 1910,
                string docFrName = "", string docLaName = "", 
                string docSpl = "");
    //Function to setInfo of a patient
    //The patient details like ID, first name, last name, 
    //birthday(dd,mm,yr); doctor details like first name, last name, 
    //specialty are set according to the parameters passed. 
    
    void setID(string id);
    //Function to set the ID according to the parameter.

    string getID() const;
    //Function to return the ID 

    void setBirthDate(int bDay = 1, int bMth = 1, int bYear = 1910);
    //Function to set the birthDate.
    //bDay, bMth, bYear are set according to the parameters.
    //if none given they are set to the above default values

    int getBirthYear() const;
    //Function to return the year

    void setDoctorName(string fName = "", string lName = "");
    //Function to set the doctor's first name and last name
    //according to the parameters.

    void setDoctorSpl(string spl = "");
    //Function to set the doctor's specialty according to the parameter

    string getDoctorFName() const;
    //Function to return doctor's first name.

    patientType(string id = "", string fName = "", string lName = "",
                int bDay = 1, int bMth = 1, int bYear = 1910,
                string docFrName = "", string docLaName = "", string docSpl = "");
    //Parameterized Constructor
    //The patient details like ID, first name, last name, 
    //birthday(dd,mm,yr); doctor details like first name, last name, 
    //specialty are set according to the parameters passed. 
    
    bool checkPatientID(string patientIDTmp) const;
    //Function to check patientID; It has totally 6 characters;
    //First character is upper case alphabet; Characters from 2 to 6
    //can be digits from 0 to 9; 
    //Failing to fulfill above conditions should return false else true

 private:
    string ID; //variable to store the ID
    dateType dateOfBirth; //composition; With dateOfBirth object you 
                          //can access dateType functions
    doctorType attendingPhysicain; //composition;  With dateOfBirth 
                            //object you can access dateType functions
};

#endif