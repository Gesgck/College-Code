/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#
Description: .
Input: .
Output: .
*/
#include <iostream>

using namespace std;



int main () {

    const int r = 1;
    const int c = 1;

    int **arr = new int*[r];
    for(int i = 0; i < r; i++)
        arr[i] = new int[c];

    for(int i = 0; i < r; i++)
        delete arr[i];
    delete[] arr;

return 0;



}
