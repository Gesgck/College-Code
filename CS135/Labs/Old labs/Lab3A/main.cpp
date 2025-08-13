/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_# 3A
Description: compares stuff by length.
Input: short stuff and long stuff.
Output: tells you which stuff is long.
*/
#include <iostream>

using namespace std;

int main () {
//numbers and strings initialized 
    float var = 0;
    float var1 = 0;
    string words = "a";
    string words1 = "a";

//prompts for numbers
    cout <<"Enter a floating point number" <<endl <<"**";
    cin >>var;
    cout <<endl;
    cout <<"Enter another floating point number" <<endl <<"**";
    cin >>var1;
    cout <<endl;

//compares and outputs
    cout <<"You entered " <<var <<" and " <<var1 <<endl;
    if (var>var1) {
        cout <<"The largest is " <<var <<endl <<endl;
    }
    else {
        cout <<"The largest is " <<var1 <<endl <<endl;
    }

//prompts for strings
    cout <<"Enter a string" <<endl <<"**";
    cin >>words;
    cout <<endl;
    cout <<"Enter a second string" <<endl <<"**";
    cin >>words1;
    cout <<endl;

//compares and outputs
    cout <<"You entered \"" <<words <<"\" and \"" <<words1 <<"\"" <<endl;
    if (words>words1) {
        cout <<"The largest is \"" <<words <<"\"";
    }
    else {
        cout <<"The largest is \"" <<words1 <<"\"";
    }

return 0;
}
