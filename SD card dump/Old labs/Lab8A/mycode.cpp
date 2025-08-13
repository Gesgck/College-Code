/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_# 8B
Description: makes triangles using functions.
Input: number and a character.
Output: triangles.
*/
#include <iostream>

using namespace std;

//Headers
int getIntegerInput(string, int, int);
char getCharacterInput(string);
void writeUpsideDownTriangle(int, char);
void writeRightsideUpTriangle(int, char);


int main () {

    string prompt;
    int a = 0;
    int b = 0;
    int c = 0;
    char d;

    

    a = getIntegerInput(prompt,2,20);

    b = getCharacterInput(prompt);

    writeUpsideDownTriangle(a,b);

    writeRightsideUpTriangle(a,b);

return 0;

}

//Integer function
int getIntegerInput(string prompt, int min, int max){
   /*
   Not sure what it means to:
   "Use prompt as a prompt to the user"
   so im doing it my way
   */
  do{
   cout <<"Enter a count between 2 and 20\n**";
   cin >>prompt;


    if (cin.fail() || stoi(prompt) <= min || stoi(prompt) >= max) {
                
        cout <<"Error: Invalid entry, please retry\n";
        cin.clear();
        cin.ignore(100, '\n');
    }

   }
   while(stoi(prompt) <= 2 || stoi(prompt) >= 20);
   return stoi(prompt);

}

//Character Function
char getCharacterInput(string prompt){
    cout <<"Enter a character\n**";
    cin >> prompt;
    char a = prompt[0];
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
