/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_#9B
Description: uses funtion overloading.
Input: integers and strings.
Output: math and strings.
*/
#include <iostream>

using namespace std;

//protypes
int add(int, int);
string add(string, string);
int multiply(int, int);
string multiply(string, int);


int main () {

    int int1 = 0;
    int int2 = 0;
    string user1 = "";
    string user2 = "";


    do{
//asks for first int
        cout <<"Enter an integer between 1 and 50\n**";
        cin >>int1;
        cout <<endl;
//checks first int
        if (cin.fail() || int1 < 1 || int1 > 50) {
                
            cout <<"Error: Invalid input!\n";
            cin.clear();
            cin.ignore(100, '\n');
        }

   }
   while(int1 < 1 || int1 > 50);
    

    do{
//asks for second int
        cout <<"Enter another integer between 1 and 50\n**";
        cin >>int2;
        cout <<endl;
//checks second int
        if (cin.fail() || int2 < 1 || int2 > 50) {
                
            cout <<"Error: Invalid input!\n";
            cin.clear();
            cin.ignore(100, '\n');
        }

   }
   while(int2 < 1 || int2 > 50);


//asks for strings
    cout <<"Enter a string\n**";
    cin >>user1;
    cout <<endl;

    cout <<"Enter another string\n**";
    cin >>user2;
    cout <<endl;

//adds integers
    int added = add(int1,int2);

//adds strings
    string tog = add(user1,user2);

//multiplies integers
    int mult = multiply(int1,int2);

//multiplies strings
    string stringMult1 = multiply(user1,int1);    
    string stringMult2 = multiply(user2,int2);

//outputs vaulues    
    cout <<int1 <<" + " <<int2 <<" = " <<added
    <<endl <<user1 <<" + " <<user2 <<" = " <<tog
    <<endl <<int1 <<" * " <<int2 <<" = " <<mult
    <<endl <<user1 <<" * " <<int1 <<" = " <<stringMult1
    <<endl <<user2 <<" * " <<int2 <<" = " <<stringMult2;


return 0;

}
    

//5. adds 2 integers
int add(int num1, int num2){
    num2 += num1;
    return num2;
}

//6. combines user strings
string add(string str1, string str2){
    string combine = str1 + str2;
    return combine;
}

//7. multiplies integers
int multiply(int num1, int num2){
    int a = num1 * num2;
    return a;
}

//8. multiplies strings
string multiply(string str, int num){
    string mulstr = "";
    for (int i = 0; i < num; i++){
        mulstr = mulstr + str;
    }
    return mulstr;
}
