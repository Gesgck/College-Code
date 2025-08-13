/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_# 2B
Description:takes radius of a circle and gives circumference and area.
Input:radius.
Output:circumference and area.
*/
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double PI = 3.141592;

int main () {

    double rad=0;
    string sep ="+--------+---------------+---------+\n";

//prompts for radius
    cout << "Enter the radius of a circle" <<endl <<"**";

    cin >> rad;

    cout <<endl;

//math
    double circ=0, area=0;
    circ = PI*rad*2;
    area = pow(rad,2)*PI;

//output
    cout << sep;
    cout << "| radius | circumference | area    |" <<endl;
    cout << sep;
    cout 
        <<fixed <<setprecision(2) <<left
        << "| " <<setw(7) <<rad 
        <<"| " <<setw(14) <<circ 
        <<"| " <<setw(8) <<area 
        <<"|" <<endl;
    cout << sep;

    return 0;

}