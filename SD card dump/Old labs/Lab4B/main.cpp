/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_# 4B
Description: takes a number between 2 and 10000 and gives evens and odds.
Input: number between 2 and 10000.
Output: sum of evens and odds.
*/
#include <iostream>

using namespace std;

int main () {

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

//do while to get an input and check for correctness
    do{

        cout <<"Enter a count between 2 and 10000\n" <<"**";
        cin >> a;
        cout <<endl;
            if (cin.fail() || a < 2 || a > 10000) {
                cout <<"Error: Invalid entry, please retry\n";
                cin.clear();
                cin.ignore(100, '\n');
            }

    } while (a < 2 || a > 10000);

//stores input for later
    d = a;

// adds up the even numbers
    for (a=d;a>1;a--){

        if (a % 2 == 0){
            b = b + a;
        }

    }
    cout << "Sum of even numbers: " <<b <<endl;

//resets a to input
    a = d;

//adds up the odd numbers
    while (a > 0){

        if (a % 2 == 1){
            c = a + c;
            a--;
        }
        else {
            a--;
        }
    
    }
    cout <<"Sum of odd numbers:  " <<c;

return 0;

}
