/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_#8B  
Description: gets a user defined radius and gives circle math.
Input: radius.
Output: circumference and area.
*/
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double pi = 3.14159;


//headers for functions
double getDoubleInput(string, double, double);
bool checkFailure(double, double, double);
double circumference(double);
double area(double);

int main () {

    const double min = 0.5;
    const double max = 20.5;

//string to output in "getDoubleInput"
    string prompt = "Enter a circle radius between " +
		to_string(min) + " and " +
		to_string(max) + "\n**";


//calls to functions for math
    double radius = getDoubleInput(prompt,min,max);

    double circum = circumference(radius);

    double ar = area(radius);

//outputs math
    cout <<fixed <<setprecision(2) 
        <<"Radius: " <<radius <<endl
        <<"Circumference: " <<circum <<endl
        <<"Area: " <<ar;


return 0;

}


//funtion to get radius
double getDoubleInput(string prompt, double min, double max){
    
    double input = 0;
    bool check = true;
    do{
        cout <<prompt;
        cin >>input;
        cout <<endl;
        check = checkFailure(input,min,max);
    }
    while (check == false);
        
   return input;
}

//error checking function for radius
bool checkFailure(double input, double min, double max){
    bool check = true;
    if (cin.fail() || input < min || input > max) {
                
        cout <<"Error: Invalid radius!\n";
        cin.clear();
        cin.ignore(100, '\n');
        check = false;
    }
    else{
        check = true;
    }
    return check;
}

//circumference calculation
double circumference(double radius){
    double cir = 2*pi*radius;
    return cir;
}

//area calculations
double area(double radius){
    double area = pi * pow(radius,2);
    return area;
}
