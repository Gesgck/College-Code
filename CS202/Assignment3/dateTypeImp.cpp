/*
Name:Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#3
Description: Implamentation file for dateType.h.
Input: data for date.
Output: the date.
*/

#include <iostream>
#include "dateType.h"

using namespace std;

dateType::dateType(int month, int day, int year){
    setDate(month,day,year);
}
//Constructor to set the date

void dateType::setDate(int month, int day, int year){
    dMonth = month;
    dDay = day;
    dYear = year;
}
//Function to set the date.

int dateType::getDay() const{
    return dDay;
}
//Function to return the day.

int dateType::getMonth() const{
    return dMonth;
}
//Function to return the month.  

int dateType::getYear() const{
    return dYear;
}
//Function to return the year.

void dateType::printDate() const{
    cout <<dDay <<"-" <<dMonth <<"-" <<dYear;
}
//Function to output the date in the form mm-dd-yyyy.