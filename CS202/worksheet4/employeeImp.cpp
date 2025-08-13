/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#
Description: imp for worksheet 4.
Input: N/A.
Output: Employee Data.
*/
#include "employee-1.h"

using namespace std;

Employee::Employee(){
    ID = "N/A";
    age = -1;
    salary = -1;

}

Employee::Employee(string I, int ag, double sal){
    ID=I;
    age=ag;
    salary=sal;
}

void Employee::printData(){
    cout <<"Employee ID: "<<ID <<", Age: " <<age 
    <<", Salary: "<<salary <<endl;
}

Employee::Employee(Employee const &em){
    ID=em.ID;
    age = em.age;
    salary = em.salary;
    cout <<"Employee Copy Constructor invoked\n";
    cout <<"Employee ID: "<<ID <<", Age: " <<age 
    <<", Salary: "<<salary <<endl;
}

Employee::~Employee(){
    cout<<"Base destructor invoked\n";
}

employeeType::employeeType(){
    Employee();
    eType = "";
    serviceYears = new int;
}

employeeType::employeeType(string a, int b, double c, string d, int e):Employee(a,b,c)
{   
    eType = d;
    serviceYears = new int;
    *serviceYears = e;
}

void employeeType::printData(){
    Employee::printData();
    cout <<"Employee Type: " <<eType
    <<", serviceYears: " <<*serviceYears <<endl;
}

employeeType::~employeeType(){
    delete serviceYears;
    cout<<"Derived destructor invoked\n";
}