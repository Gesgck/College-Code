/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_# 7B
Description: takes a list of temps and finds values from it.
Input: temperature file.
Output: high, low, and averages.
*/
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main () {

//makes stuff for the program
    ifstream iFile;
    string file;
    int a = 0;
    double b = 0;
    string city;
    int year = 0;

//makes the array
    double arr[12][2];

//asks for a file
    do{
        cout <<"Enter file name\n**";
        cin >>file;
        cout <<endl;
        iFile.open(file);
//checks if file is valid
        if (!iFile.is_open())
        {
            cout << "Error: Invalid file name\n";
        }
        else
        {
            a = 1;
        }
    } while( a == 0);

//reads city and year into variables
    iFile >> city;
    iFile >> year;
    cout <<city <<" " <<year <<endl;

//reads data into array
    for(int i=0; i<12; i++){
        for(int j=0; j<2; j++){
            iFile >> arr[i][j];
        }
    }

//closes the file
    iFile.close();

//reads through the array to find the lowest

//sets intital value for comparison
    b= arr[0][0];

//cycles through array and compares
    for(int i=0; i<12; i++){
        for(int j=0; j<2; j++){
            if(b > arr[i][j]){
                b = arr[i][j];
            }
        }
    }

//outputs lowest temp
    cout <<fixed <<setprecision(2) <<"Lowest temperature of the year was "
    << b << "° F." <<endl;

//sets b for comparison
    b = arr[0][0];

//finds the highest value 
    for(int i=0; i<12; i++){
        for(int j=0; j<2; j++){
            if(b < arr[i][j]){
                b = arr[i][j];
            }
        }
    }

//outputs the highest
    cout  <<"Highest temperature of the year was "
    << b << "° F." <<endl;

//math for the low
    b = 0;
    for (int i = 0; i <12; i++){
        b += arr[i][0];
    }

    b = b/12;

//outputs low average
    cout <<"Average low temperature of the year was " 
    <<b << "° F." <<endl;

//math for high
    b = 0;
    for (int i = 0; i <12; i++){
        b += arr[i][1];
    }

    b = b/12;

//outputs high average
    cout <<"Average high temperature of the year was "
    <<b <<"° F.";

return 0;

}
