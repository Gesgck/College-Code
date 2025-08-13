/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_# 2A
Description: Computes trig stuff.
Input: Angles.
Output: Radians and trig.
*/
#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.141592;

int main () {

    double ang=0;
//prompts for and takes an angle
    cout <<"Enter an angle value, in degrees" <<endl <<"**";

    cin >> ang;

    cout <<endl;

//degrees to radians
    double rad = (ang*PI)/180;

    cout <<ang <<" degrees = " <<rad <<" radians" <<endl;
//sin
    cout <<"sin(" <<ang <<") = " <<sin(rad) <<endl;
//cos
    cout <<"cos(" <<ang <<") = " <<cos(rad) <<endl;
//tan
    cout <<"tan(" <<ang <<") = " <<tan(rad) <<endl;

    return 0;
}
