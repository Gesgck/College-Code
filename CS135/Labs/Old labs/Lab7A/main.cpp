/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_# 7A
Description: takes file input and adds rows and columns.
Input: file.
Output: sums of rows and columns.
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

//makes the array
    double arr[7][10];

//asks for a file
    do{
        cout <<"Enter a file name\n**";
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

//reads data into array
    for(int i=0; i<7; i++){
        for(int j=0; j<10; j++){
            iFile >> arr[i][j];
        }
    }

//closes the file
    iFile.close();

//does the math for the sums and outputs
    cout <<"ROW SUMS:" <<endl;
    for(int i=0; i<7; i++){
        for(int j=0; j<10; j++){
            b += arr[i][j];
            if(j<9){
                //sets the format for output
                cout <<fixed <<setprecision(1) <<setw(5) <<left << arr[i][j] <<"+ ";
            }
            if(j==9){
                cout <<setw(5) <<left <<arr[i][j] << "= " << b;
                b = 0;
            }
        }
        cout <<endl;
    }

//math and output for columns
    cout <<endl <<"COLUMN SUMS:" <<endl;
    for(int j=0; j<10; j++){
        for(int i=0; i<7; i++){
            b += arr[i][j];
            if(i<6){
                cout <<setw(5) <<left << arr[i][j] <<"+ ";
            }
            if(i==6){
                cout <<setw(5) <<left <<arr[i][j] << "= " << b;
                b = 0;
                
            }
        }
        cout <<endl;
    }

return 0;

}
