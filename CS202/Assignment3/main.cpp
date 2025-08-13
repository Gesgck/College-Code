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
#include <iostream>
#include <string>
#include "patientType.h"
#include "billType.h"

using namespace std;

int main()
{
    string poundSigns;
    poundSigns.append(70, '#');
    string spaceBars;
    spaceBars.append(20, ' ');
    cout << endl << poundSigns << endl;

    cout<< spaceBars << "Welcome to WE CARE Hospital";

    cout << endl << poundSigns << endl;

    patientType william("W12345", "William", "John", 23, 10, 1950,
        "David", "Jones");//bad data- Dr.Speciality missing

    patientType thomas("T12395", "Thomas", "Rodriguez", 30, 16, 1900,
        "Joe", "Roberts", "Ophthalmology"); //bad data-month and year

    patientType charles("C9832", "Charles", "Miller", 12, 6, 2015,
        "Donald", "Wilson", "Pediatric"); //Invalid Patient ID

    patientType dennis("d88888", "Dennis", "Hill", 30, 8, 1998,
        "Patrick", "Green", "Pathology");// Invalid patientID

    patientType paul("P33357", "Paul", "John", 8, 11, 1985,
        "Jose", "Clark", "Cardiac");
    //paul.print();
    patientType henry("H97651", "Henry", "Hall", 17, 5, 2000,
        "Eric", "Young", "Neurology");

    patientType brian("B97893", "Brian", "Jackson", 15, 8, 1998,
        "Walter", "Flores", "Cardiac");

    patientType jeffrey("J91761", "Jeffrey", "Lewis", 5, 10, 1980,
        "Fred", "Baker", "Radiology");

    //setting patienType using individual setter functions
    //case1
    patientType lara;
    lara.setID("L48532");
    lara.setName("Lara", "King");
    lara.setBirthDate(23, 10, 1900); //for bad data print error message
    lara.setDoctorName("Jerry", "Nguyen");
    lara.setDoctorSpl("Neurology");
    lara.print(); // This print function only prints patient
    //and doctor's data
    
    billType laraBill("L48532", 1896.50, 225.00, 345.95, lara);
    laraBill.printBill();
    cout << endl;
    
    //setting patienType using setInfo function
    //case2
    patientType frank;
    
    frank.setInfo("F65780", "Frank", "Lee", 14, 6, 2017, 
        "Bobby", "Scott", "Pediatric");
    billType frankBill("F65780", 986.50, 76.98, 124.95, frank);
    frankBill.printBill();
    cout << endl;


   //billType class functions
    billType williamBill("W12345", 245.50, 76.98, 124.95, william);

    billType thomasBill("T12395", 546.50, 120.00, 234.55, thomas);

    billType charlesBill("C98327", 465.00, 0.00, 154.25, charles);

    billType dennisBill("d88888", 632.40, 185.25, 420.65, dennis);

    billType paulBill("P33357", 5897.65, 1720.50, 1100.90, paul);

    billType henryBill("H97651", 1295.00, 250.00, 600.90, henry);

    billType brianBill("B97893", 3456.75, 2000.00, 1300.00, brian);

    billType jeffreyBill("J91761", 4256.90, 100.00, 180.00, jeffrey);

    

    williamBill.printBill();
    cout<<endl;
    thomasBill.printBill();
    cout<<endl;
    charlesBill.printBill();
    cout<<endl;
    dennisBill.printBill();
    cout<<endl;
    paulBill.printBill();
    cout<<endl;
    henryBill.printBill();
    cout<<endl;
    brianBill.printBill();
    cout<<endl;
    jeffreyBill.printBill();
    cout<<endl;

    // declare billType obj with no parameters and 
    // try to set data using setInfo
    
    billType adamBill; //This prints speciality missing of
    //doctor and patient; also invalid patient ID; 
    //Since you don't have declared patientType Adam
    adamBill.setInfo("A93472", 2356.75, 425.75, 125.25);
    adamBill.printBill();
    
    cout<<"End of Patients Data"<<endl;

    cout << endl << poundSigns << endl;
    //doctorType bad data
    doctorType kevin("Kevin", "Perez");
    doctorType david("David", "Jones");

    cout << endl << poundSigns << endl;
    doctorType joe("Joe", "Roberts", "Opthamology");
    doctorType donald("Donald", "Wilson", "Pediatrics");
    doctorType jose("Jose", "Clark", "Cardiac");
    doctorType patrick("Patrick", "Green", "Pathology");
    doctorType eric("Eric", "Young", "Neurology");
    doctorType walter("Walter", "Flores", "Cardiac");
    doctorType fred("Fred", "Baker", "Radiology");
    doctorType steven("Steven", "Taylor", "Radiology");
    doctorType anthony("Anthony", "Lee", "Anesthesiology");

    kevin.print();
    cout<<endl;
    david.print();
    cout<<endl;
    joe.print();
    cout<<endl;
    donald.print();
    cout<<endl;
    jose.print();
    cout<<endl;
    patrick.print();
    cout<<endl;
    eric.print();
    cout<<endl;
    walter.print();
    cout<<endl;
    fred.print();
    cout<<endl;
    steven.print();
    cout<<endl;
    anthony.print();
    cout<<endl;
    
    cout << endl << poundSigns << endl;

    return 0;
}
