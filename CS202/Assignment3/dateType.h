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
#ifndef dateType_H
#define dateType_H
   
class dateType
{
public:
    void setDate(int month, int day, int year);
      //Function to set the date.
      //The member variables dMonth, dDay, and dYear are set  
      //according to the parameters.
      
    int getDay() const;
      //Function to return the day.

    int getMonth() const;
      //Function to return the month.  

    int getYear() const;
      //Function to return the year.     

    void printDate() const;
      //Function to output the date in the form mm-dd-yyyy.

    dateType(int month = 1, int day = 1, int year = 1910);
      //Constructor to set the date
      //The member variables dMonth, dDay, and dYear are set 
      //according to the parameters.
private:
    int dMonth; //variable to store the month
    int dDay;   //variable to store the day
    int dYear;  //variable to store the year
};

#endif