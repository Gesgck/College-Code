/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_#10A
Description: groups a student's data via struct.
Input: student info.
Output: student info.
*/
#include <iostream>
#include <iomanip>

using namespace std;

//student struct
struct studentType{
    string firstName;
    string lastName;
    int grade;
    char letterGrade;
};

//prototypes
void getStudentData(studentType& student);
void getLetterGrade(studentType&);
void printStudentData(studentType);

int main () {
//variables
    studentType student;

//function calls
    getStudentData(student);
    getLetterGrade(student);
    printStudentData(student);

return 0;

}
//asks for student data
void getStudentData(studentType& student){
    cout <<"Enter a first name\n**";
    cin >>student.firstName;
    cout <<endl <<"Enter a last name\n**";
    cin >>student.lastName;
    int a = 0;
    do{
        cout <<endl <<"Enter a grade\n**";
        cin >>student.grade;
        cout <<endl;
        if(cin.fail()||student.grade < 0||student.grade > 4){
            cout <<"Error: Invalid grade";
            cin.clear();
            cin.ignore(100,'\n');
        }
        else{
            a = 1;
        }
    }while(a == 0);
}
//gets the letter grade
void getLetterGrade(studentType& student){
    if(student.grade == 4){
        student.letterGrade = 'A';
    }
    else if(student.grade == 3){
        student.letterGrade = 'B';
    }
    else if(student.grade == 2){
        student.letterGrade = 'C';
    }
    else if(student.grade == 1){
        student.letterGrade = 'D';
    }
    else if(student.grade == 0){
        student.letterGrade = 'F';
    }
}
//prints all the stuff
void printStudentData(studentType student){
    cout <<"Data Entered\n  " <<setw(20) <<left
    <<"student.firstName" <<"= "<<student.firstName
    <<endl <<"  " <<setw(20) <<left <<"student.lastName" <<"= "
    <<student.lastName <<endl <<"  " <<setw(20) <<left
    <<"student.grade" <<"= " <<student.grade <<endl <<"  " 
    <<setw(20) <<left <<"student.letterGrade" <<"= "
    <<student.letterGrade;

}