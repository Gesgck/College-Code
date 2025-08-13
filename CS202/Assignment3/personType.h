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
#ifndef personType_H
#define personType_H

#include <string>
 
using namespace std;

class personType
{
public:
   void print() const;
   //Function to output the first name and last name
   //in the form firstName lastName.
  
   void setName(string first, string last);
   //Function to set firstName and lastName according 
   //to the parameters.

   string getFirstName() const;
   //Function to return the first name.
      
   string getLastName() const;
   //Function to return the last name.
       
   personType(string first = "", string last = "");
   // parameterized constructor
   //Sets firstName and lastName according to the parameters.
   //The default values of the parameters are empty strings.
       
 private:
   string firstName; //variable to store the first name
   string lastName;  //variable to store the last name
};

#endif
