/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_# 5A
Description: takes a number and prints a triangle.
Input: number.
Output: triangles.
*/
#include <iostream>

using namespace std;

int main () {

    int a = 0;
    int b = 0;
    int c = 0;
    int amountOfStars = 0;
//asks for input
    do{

        cout <<"Enter a count between 2 and 20\n" <<"**";
        cin >> amountOfStars;
        cout <<endl;

            if (cin.fail() || amountOfStars < 2 || amountOfStars > 20) {
                
                cout <<"Error: Invalid entry, please retry\n";
                cin.clear();
                cin.ignore(100, '\n');
            }

    } while (amountOfStars < 2 || amountOfStars > 20);
// stores user input for upside down triangle
a = amountOfStars;
b = amountOfStars;
//prints the upside down triangle
    for(int i=0; i<a; i++){
        
        for(int j=0; j<b; j++){
            
            if (c == 0 || c == a-1){
            
              cout <<"*";

            }
         
        }
        cout <<endl;
        b--;
    }
//prints the triangle rightside up
    int d = 0;
    int e = 1;
    while(c < amountOfStars){

        while(d < e){

            cout <<"*";
            d++;

        }
//makes int d chase int e until it increments by int amountOfStars
    cout <<endl;
    d = 0;
    e++;
    c++;

    }   

return 0;

}
