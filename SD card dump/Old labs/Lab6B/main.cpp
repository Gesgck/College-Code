/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_# 6B
Description: finds a kid from a list and lists stats.
Input: file.
Output: student information.
*/
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int main () {
//makes stuff for the program
    ifstream iFile;
    string file;
    string name;
    int a = 0;

//makes the array
    string names[100];
    double scores[100];

//asks for a file
    do{
        cout <<"Enter a file name\n**";
        cin >>file;
        cout <<endl;
        iFile.open(file);
//checks if file is valid
        if (!iFile.is_open())
        {
            cout << "Error: Invalid file name.\n";
        }
        else
        {
            a = 1;
        }
    } while( a == 0);

//asks for a name
    cout <<"Enter a name to search\n**";
    cin >>name;
    cout <<endl;

//puts values in the array
    a=0;
    while (!iFile.eof()){

            iFile >> names[a] >>scores[a];
//checks if newline at end            
               if (!iFile) {

                    iFile.clear();
                    iFile.ignore(100, '\n');
                    continue;
                }
            a++;
        }
//closes the file
    iFile.close();


//prints the names forward
    a -= 1;
    cout <<"Names Forward: ";
    for (int j = 0; j<=a; j++){
        if (j<a){
            cout <<names[j] <<", ";
        }
        if (j==a){
            cout <<names[j] <<endl;
        }
    }

//scores forward
    cout <<"Scores Forward: ";
    for (int l = 0; l<=a; l++){
        if (l<a){
            cout <<scores[l] <<", ";
        }
        if (l==a){
            cout <<scores[l] <<endl;
        }
    }
        
//names backwards
    cout <<"Names Reverse: ";
    for (int n = a; n>=0; n--){
        if(n>0){
            cout <<names[n] <<", ";
        }
        if (n == 0){
            cout <<names[n] <<endl;
        }
    }

//scores backwards
    cout <<"Scores Reverse: ";
    for (int b = a; b>=0; b--){
        if(b>0){
            cout <<scores[b] <<", ";
        }
        if (b == 0){
            cout <<scores[b] <<endl;
        }
    } 

//makes variables for score math
    int c = 0;
    int d = 0;
    double e = 0;
    double f = 0;
    double g = 0;
    double h = 0;



//finds the first score for the student
    for(int v = 0; v<=a; v++){
        c = name.compare(names[v]);\
        if (c==0){
        g = scores[v];
        f = scores[v];
        break;
        }
    }
    
//finds the student
//does the math for the student's scores
    for(int v = 0; v<=a; v++){
        c = name.compare(names[v]);
        if(c == 0){
            d = v;
            e++;
            h += scores[d];
            if (f < scores[d]){
                f = scores[d];
            }
            if (g > scores[d]){
                g = scores[d];

            }
        }

    }

//if student does not exist
    if(e == 0){
        cout <<"Error: " <<name <<" is not a student in the list";
    }

//displays all the stuff for student
    if(e != 0){
        cout <<e <<" results for " <<name <<endl;
        cout <<fixed <<setprecision(2) <<"Minimum: " <<g <<endl 
        <<"Maximum: " <<f <<endl
        <<"Sum:     " <<h <<endl
        <<"Average: " << h/(e);
    }

return 0;

}
