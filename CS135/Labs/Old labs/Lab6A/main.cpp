/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_# 6A
Description: takes a file, looks for numbers, does math.
Input: file with numbers.
Output: numbers along with math.
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

int main () {

//stuff is created
    ifstream iFile;
    string file,b;
    const int asize = 100;
    int a = 0;
    double c = 0;
    double e = 0;
    double d = 0;
    double array[asize];

//initialize the array
    for (int i = 0; i < asize; i++) {
        array[i] = 0;
    }

//asks for a file and checks it
    do
    {
        cout << "Enter a file name\n**";
        cin >> file;
        cout << endl;
        iFile.open(file);
        // checks if file name is real
        if (!iFile.is_open()){
            cout << "Error: Invalid file name.\n";
        }
        else{
            a = 1;
        }
    } while (a == 0);

//inputs values into array
    int cnt = 0;
    while (!iFile.eof()){
        iFile >>array[cnt];
//checks for failures
        if (iFile.fail()){

            if (!iFile.eof()){
                iFile.clear();
                iFile.ignore(100, '\n');
                cout << "Error: Invalid input in file.\n";
                continue;
            }
            
        }
        cnt++;
    }

    cout <<endl;

    iFile.close();

//finds the size and sum of the array
    for (int i = 0; i < asize; i++){
        if(array[i] != 0){
            e = e+array[i];
            d++;
        }
    }
    cout <<"Amount of Elements Read In: " <<d <<endl;
    d = d-1;

//prints all values in the array forwards
    cout <<fixed <<setprecision(2) <<"Forwards: ";
    for (int i = 0; i <= d; i++){
        if(i < d){
            cout << array[i] <<", ";
        }
        else if (i == d)
            cout << array[i] <<endl;
    }
    
//prints all values backwards   
    cout <<"Backwards: ";
    for (int i = d; i>=0; i--){
        if(i > 0){
            cout << array[i] <<", ";
        }
        else if (i == 0){
            cout << array[i] <<endl;
        }
    }


//sets the value to compare for step 4
    c = array[0];

//compares all values to find the smallest
    for(int i = 0; i<=d; i++){
        if (c>array[i]){
            c = array[i];
        }
        
    }    
    cout  << "Minimum: " <<c <<endl;

//comapres all values to find the biggest
    c = 0;

    for(int i = 0; i<asize; i++){
        if (c<array[i]){
            c = array[i];
        }
    }
    cout <<"Maximum: " <<c <<endl;

//prints the sum
    cout  <<"Sum: " <<e <<endl;

//finds the average and prints it
    d=d+1;
    c = e/d;
    cout <<"Average: "<<c;

return 0;

}
