/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_# 4A
Description: asks for numbers to increment.
Input: starting number, ending number, and number to interment by.
Output: numbers from start to end incermented by number.
*/
#include <iostream>

using namespace std;

int main () {

    int a = 0;
    int b = 0;
    int c = 0;

//asks for inputs and checks for failures
    cout << "Enter a starting number\n" <<"**";
    cin >> a;
    cout <<endl;
        if (cin.fail()){
            cout <<"Error: invalid entry.";
            return 0;
        }


    cout << "Enter an ending number\n" <<"**";
    cin >> b;
    cout <<endl;
        if (cin.fail()){
            cout <<"Error: invalid entry.";
            return 0;
         } 
        if (a > b) {
            cout <<"Error: end must be greater than start.";
            return 0;
        }

    
    cout << "Enter a value to increment by\n" <<"**";
    cin >>c;
    cout <<endl;
        if (cin.fail()){
             cout <<"Error: invalid entry.";
             return 0;
        }


//does the number increments math
    b = b - c;
    cout <<a <<" ";

//output
        while (a<=b) {
        a = a+c;
        cout <<a <<" ";
        }

return 0;

}
