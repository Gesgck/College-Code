/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_# 3B
Description: Takes a letter grade and gives a range.
Input: Letter grade.
Output: Numeric range.
*/
#include <iostream>
#include <iomanip>

using namespace std;

int main () {

    char grade;

    cout <<"Enter a letter grade" <<endl <<"**";
    cin >> grade;
    cout <<endl;

    switch (grade){
        case 'A':
        case 'a':
        cout <<"Grade range is 90 - 100";
        break;
        case 'B':
        case 'b':
        cout <<"Grade range is 80 - 89.99";
        break;
        case 'C':
        case 'c':
        cout <<"Grade range is 70 - 79.99";
        break;
        case 'D':
        case 'd':
        cout <<"Grade range is 60 - 69.99";
        break;
        case 'F':
        case 'f':
        cout <<"Grade range is 0 - 59.99";
        break;
        default:
        cout << "Error: '" <<grade <<"' is not a valid letter grade";
        
    }

return 0;

}