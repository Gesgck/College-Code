/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#4
Description: main for worksheet 4.
Input: N/A.
Output: Employee Data.
*/
#include "employee-1.h"
using namespace std;

int main(){

    //part 1
    Employee eobj1("123",25,12500.25);
    eobj1.printData();

    //part 2
    employeeType tobj1("333",25,3500.25,"part-time",8);
    tobj1.printData();

    //part 3
    Employee eobj2(eobj1);

    //Part 4
    employeeType tobj2("111",40,12500.25,"Full-time",5);
    Employee *eobj3 = &tobj2;

    eobj3->printData();

    //part 5
    Employee *eobj4 = new employeeType ("444",30,100.25,"Full-time",10);
    employeeType *tobj3;

    tobj3 = dynamic_cast<employeeType*>(eobj4);
    tobj3 -> printData();

    delete eobj4;

    return 0;

}