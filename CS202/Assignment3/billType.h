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
#ifndef BillType_H
#define BillType_H

#include <string>
#include "doctorType.h"
#include "personType.h"
#include "dateType.h"
#include "patientType.h"
 
using namespace std;

class billType 
{
public:
   void printBill();
   //Function to output the first name and last name using pType obj
   //Function to output Billing details like ID, pharmacyCharges,
   //roomRent, doctorFee and finally total charges

   void setInfo(string id, double phCharges, double rRent,
                double docFee);
   //Function to setInfo of a bill
   //The member variables ID, pharmacyCharges, roomRent, doctorFee,
   //are set according to the parameters. 
   
   void setID(string id);
   //Function to setID according to the parameter

   string getID();
   //Function to return the ID.
   
   double billingAmount();
   //Function to return pharmacyCharges + roomRent + doctorFee

   billType(string id, double phCharges, double rRent,
      double docFee, patientType patientObj);
   //Parameterized Constructor
   //The member variables ID, pharmacyCharges, roomRent, doctorFee,
   //are set according to the parameters.
   //Also set pType with patientObj

   billType(); 
   // Default Constructor
   //The member variables ID, pharmacyCharges, roomRent, doctorFee,
   //have to be initialized; no need to initialize pType here
 private:
   string ID;
   double pharmacyCharges; //variable to store the pharmacy charges
   double roomRent; //variable to store the room rent
   double doctorFee; //variable to store the doctor fee
   patientType pType; // composition; With pType object you can access
                        //patientType functions
};

#endif
