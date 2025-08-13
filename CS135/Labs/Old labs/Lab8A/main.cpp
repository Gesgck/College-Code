/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_# 8B
Description: makes triangles using functions.
Input: number and a character.
Output: triangles.
*/
#include <iostream>

using namespace std;

// Function prototypes
// YOUR CODE HERE
int getIntegerInput(string, int, int);
char getCharacterInput(string);
void writeUpsideDownTriangle(int, char);
void writeRightsideUpTriangle(int, char);


int main() {
	// Minimums/maximums
	const int MIN = 2;
	const int MAX = 20;
	// Prompt for integer input
	string prompt1 = "Enter a count between " +
		to_string(MIN) + " and " +
		to_string(MAX) + "\n**";
	// Prompt for character input
	string prompt2 = "\nEnter a character\n**";
	
	// Get size of triangle
	int size = getIntegerInput(prompt1, MIN, MAX);
	// Get character to use when printing triangle
	char character = getCharacterInput(prompt2);
	
	// Write both triangles
	writeUpsideDownTriangle(size, character);
	writeRightsideUpTriangle(size, character);
	cout << endl;
	
	// Terminate the program
	return 0;
}

// Function definitions
// YOUR CODE HERE


int getIntegerInput(string prompt, int min, int max){
   int a = 0;
  do{
   cout <<prompt;
   cin >>a;
   cout <<endl;


    if (cin.fail() || a < min || a > max) {
                
        cout <<"Error: Error: Invalid input!\n";
        cin.clear();
        cin.ignore(100, '\n');
    }

   }
   while(a < 2 || a > 20);
   return a;

}

//Character Function
char getCharacterInput(string prompt){
	char a;
    cout <<prompt;
	cin >>a;
	cout <<endl;
    return a;
}

//Upside Down Triangle function
void writeUpsideDownTriangle(int size, char character){
    int outputcount = size;
    do{
        for (int i = outputcount; i > 0; i--){
        cout <<character;
        }
        if (outputcount == 0){
            break;
        }
        cout <<endl;
        outputcount --;
    }while (outputcount >= 0);
    
}

//Right side Up Triangle function
void writeRightsideUpTriangle(int size, char character){
    int outputcount = 1;
    do{
    for (int i = 0; i < outputcount; i++){
        cout <<character;
    }
    cout <<endl;
    outputcount++;
    }while(outputcount <= size);
}

