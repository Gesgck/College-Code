/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_#9A
Description: does math via functions.
Input: doubles.
Output: math.
*/
#include <iostream>
#include <iomanip>

using namespace std;

//prototypes
double getDoubleInput(string, double, double);
bool checkFailure(double, double, double);
void getDoubleInputs(double&, double&);
void addSubtract(double&, double&);
void multiplyDivide(double&, double&);

//global min and max
const double minimum = 0.5;
const double maximum = 20.5;

int main () {
//variables for the functions
    double input1 = 0;
    double input2 = 0;
    double num1 = 0;
    double num2 = 0;
    

    getDoubleInputs(input1,input2);

//sets num1 and num2 for addSubtract()
    num1 = input1;
    num2 = input2;

    addSubtract(num1,num2);

//outputs the addition and subtraction
    cout <<fixed <<setprecision(2) <<input1 <<" + " << input2
    <<" = " <<num1 <<endl <<input1 <<" - " <<input2
    <<" = " <<num2 <<endl;

//resets num1 and num2
    num1 = input1;
    num2 = input2;

    multiplyDivide(num1,num2);

//outputs the multiplication and division
    cout <<input1 <<" * " << input2
    <<" = " <<num1 <<endl <<input1 <<" / " <<input2
    <<" = " <<num2 <<endl;


return 0;

}

//funtion to get a double
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

//error checking function
bool checkFailure(double input, double min, double max){
    bool check = true;
    if (cin.fail() || input < min || input > max) {
                
        cout <<"Error: Invalid input!\n";
        cin.clear();
        cin.ignore(100, '\n');
        check = false;
    }
    else{
        check = true;
    }
    return check;
}

//gets both doubles for main
void getDoubleInputs(double &input1, double &input2){
    string p1 ="Enter double between 0.500000 and 20.500000\n**";
    string p2 ="Enter another double between 0.500000 and 20.500000\n**";

    input1 = getDoubleInput(p1, minimum, maximum);
    input2 = getDoubleInput(p2, minimum, maximum);
}

//adds and subtracts
void addSubtract(double &num1, double &num2){
    double a = num1 + num2;
    num2 = num1 - num2;
    num1 = a;

}

//multiplys and divides
void multiplyDivide(double &num1, double &num2){
    double a = num1*num2;
    num2 = num1 / num2;
    num1 = a;
}
