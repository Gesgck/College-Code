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
 
#ifndef doctorType_H
#define doctorType_H

#include <string>
#include "personType.h"
 
using namespace std;

class doctorType: public personType
{
public:
   void print() const;
   //Function to output the doctor's first name, last name and specialty
   
   void setSpecialty(string spl);
   //Function to set specialty according to the parameters. 
   
   string getSpecialty() const;
   //Function to return the specialty.

   doctorType(string first = "", string last = "", string spl = "");
   // parameterized constructor
   //Sets firstName, lastName and specialty according to the parameters

private:
   string specialty; //variable to store the doctor's specialty
};

#endif
