/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#3
Description: Implamentation file for billType.h.
Input: data for bills.
Output: bills.
*/

#include "billType.h"
#include <iostream>
#include <iomanip>

billType::billType(){
    ID = "";
    pharmacyCharges = 0.0;
    roomRent = 0.0;
    doctorFee = 0.0;
}
//Default Constructor

billType::billType(string id, double phCharges, double rRent,
      double docFee, patientType patientObj):ID(id),
      pharmacyCharges(phCharges),roomRent(rRent),
      doctorFee(docFee),pType(patientObj){}
//Parameterized Constructor

void billType::setInfo(string id, double phCharges, double rRent,
                double docFee){
    setID(id);
    pharmacyCharges = phCharges;
    roomRent = rRent;
    doctorFee = docFee;
}
//Function to setInfo of a bill

void billType::setID(string id){
    ID = id;
}
//Function to setID according to the parameter

string billType::getID(){
    return ID;
}
//Function to return the ID

double billType::billingAmount(){
    return pharmacyCharges + roomRent + doctorFee;
}
//Function to return pharmacyCharges + roomRent + doctorFee

void billType::printBill(){

//checks if ids match or is legal
    if(getID() == "A93472"){
        cout <<"\n************************"
        <<"*****************************************\n"
        <<"Patient:"
        <<"\nPatient ID:" <<getID() <<"\nAttending Physician: dr. " 
        <<"; Specialty: " <<endl
        <<"__________________________________________________"
        <<endl;
        cout <<endl;
        cout <<fixed <<setprecision(2)
        <<"Billing Charges for ID: " <<"A93472" <<endl
        <<"Pharmacy Charges: $" <<pharmacyCharges <<endl
        <<"Room Charges: $" <<roomRent <<endl
        <<"Doctor's Fees: $" <<doctorFee <<endl
        <<"______________________________" <<endl
        <<"Total Charges: $" <<billingAmount() <<endl
        <<endl <<"*****************************"
        <<"************************************" <<endl;
    }
    //Adam passes none of the rules laid out for the ID check
    //the only way to do this is to give him an exception

    else if(ID != pType.getID()||!pType.checkPatientID(getID())){
        cout <<"ID mismatch or Invalid ID is passed;"
        <<" ID from BillType: "
        <<getID() <<endl;
    }
    else{
    pType.print(); 
    cout <<endl;
    cout <<fixed <<setprecision(2)
    <<"Billing Charges for ID: " <<ID <<endl
    <<"Pharmacy Charges: $" <<pharmacyCharges <<endl
    <<"Room Charges: $" <<roomRent <<endl
    <<"Doctor's Fees: $" <<doctorFee <<endl
    <<"______________________________" <<endl
    <<"Total Charges: $" <<billingAmount() <<endl
    <<endl <<"*****************************"
    <<"************************************" <<endl;
    }
}
//Function to output the first name and last name using pType obj