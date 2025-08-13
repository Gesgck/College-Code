/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#1
Description: A shoddy SQL 
Input:search query
Output:Information retaining to search
*/
#include<iostream>
#include<string>
#include<fstream> // No additional includes or STL allowed!
using namespace std;

#define ARSIZE 5500  //for changing size on the go
#define COLMAX 37

struct Query{
    int colCount = 0;
    int whereCount = 0;
    string colList[COLMAX] = {"","","","","","","","","","",
                              "","","","","","","","","","",
                              "","","","","","","","","","",
                              "","","","","","",""};
    string whereLeft[5]  = {"","","","",""};
    string whereRight[5] = {"","","","",""};
    string logicList[5]  = {"","","","",""};
    string ANDORlist[4]      = {"", "", "", ""};
};

//reads in our data, data is separated by tabs and new lines
void readData(string rawData[ARSIZE][COLMAX]);
//go through each row's individual elements and add
//it to the array, use tab "/t" as the delimiter

//Opens file output.txt and writes output. 
void writeData(string rawData[ARSIZE][COLMAX]);

//lowercases a given string, useful for error checking
string lower(string str);

//Checks the syntax of the query, returns 1 if error, 0 if gucci
//has already been lower case so can check easier. will return
//as soon as error is detected.
bool checkSyntax(string q); //q for query so we keep lines short

//Fills struct in with all the query data, neatly organized.
//could have done this when checking syntax, but meh
void parseQuerytoStruct(Query&, string);

//makes our life easier
//int getColNum

string output[ARSIZE][COLMAX];
//Creates output with results
bool generateResults(Query&, string db[][COLMAX]);
//First we find the matching rows then we print out
//only the rows selected, unless colList is 0 then we print
//all of them out.
//Note if a col name doesn't match we just error out
//if your local output array segfaults, make it global like I put above

void runQuery(string &query, string db[][COLMAX]);
//See PDF for this function

void printer(Query&, string&, int&);
int sorter(string,int);
void opps(int a[4],int b[4],Query&,string db [ARSIZE][COLMAX]);

string rawData[ARSIZE][COLMAX]; //first row has col names

int main(){
    
    readData(rawData);
    writeData(rawData); //output.txt
    cout << "Welcome to the Satellite Database at home" << endl;
    string query = "";

    for(int i=0; i < ARSIZE; i++) //Clean up output global array
        for(int j=0; j< COLMAX; j++) output[i][j] = "";
    ofstream fout; fout.open("queryoutput.txt"); //Cleanup
    fout << "Queries:" << endl; fout.close(); //Cleanup output file

    //query="SELECT \"Users\" FROM DB;";   //Debug
    //runQuery(query, rawData); return 0;//Debug

    while(query != "q"){
        cout << "Please enter your query:" << endl;
        getline(cin, query);
        runQuery(query, rawData); //pass by ref
    }
    return 0;
}

//reads data to array
void readData(string rawData[ARSIZE][COLMAX]){
    ifstream data ("UCS-Satellite-Database-5-1-2022.txt");
    string items;
    int tabLoc = 0;

    //Putting values into the array
    for (int i = 0; i < ARSIZE; i++){
        getline(data,items);
        for (int j = 0; j <COLMAX; j++){
            tabLoc = items.find('\t');
            rawData[i][j] = items.substr(0,tabLoc);
            items = items.substr(tabLoc+1,items.length());
        }
    }

}

//writes data to file
void writeData(string rawData[ARSIZE][COLMAX]){
    ofstream output;
    output.open("output.txt");
    for (int i = 0; i < ARSIZE; i++){
        for (int j = 0; j < COLMAX; j++){
            output <<rawData[i][j];
            output <<"*Z*";
        }
        output <<"*N*";
    }
    output.close();
}

//turns query to lowercase
string lower(string str){
    for (int i; i < str.size(); i++){
    str[i] = tolower(str[i]);
    }
    return str;
}

void runQuery(string &query, string db[][COLMAX]){
    if(lower(query) == "q"){
        query = "q"; //lowercase it so while in main picks it up
        return;
    } //Exit command so we are done here.
    if(checkSyntax(lower(query))) {//lowercase version so it's ez
        cout << "Error: Invalid Query Syntax. "
        << "Get motivated. Try Again!" << endl;
        return; //if true there is syntax error
    }
    //ok now that we know query is ok we can parse and prepare
    Query q; //the struct with the data to query
    parseQuerytoStruct(q, query); //remember to handle separately *
    //now we can actually return the values for it.
    if(!generateResults(q, db))
        cout << "Error: Invalid Query Semantic. "
        << "Get motivated. Try Again!" << endl;
    }

//Checks if user messed up input
bool checkSyntax(string q){
    string temp;
    int a, b = 0;
    temp = q.substr(0,6);
    //checks if the first word is select
    if (temp != "select"){
        return true; 
    }
    //makes sure there is a "from db" somewhere
    a = q.find("from db");
    if (a <= 0){     
        return true;
    }
    //makes sure there is an even number of quotation marks
    for(int i = 0; i < q.length(); i++){
        if(q[i] == '\"'){
            a++;
        }
    }
    b = a/2;
    if ((b % 2) == 1){
        return true;
    }
    //if it passes everything then return false
    else{
        return false;
    }

}

void parseQuerytoStruct(Query& q, string query){
    int a, b, c= 0;
    string first, last, temp;
    //splits string down the "from db"
    a = query.find("from db");
    first = query.substr(7,a-1);
    last = query.substr(a+8,query.length());
    a = 0;
    //finds the number of columns asked
    for(int i = 0; i < first.length(); i++){
        if(first[i] == '\"'){
            a++;
        }
    }
    q.colCount = a/2;
    a = 0;
    //finds the number of "where" asks
    for(int i = 0; i < last.length(); i++){
        if(last[i] == '\"'){
            a++;
        }
    }
    q.whereCount = a/4;
    a = 0;
    temp = lower(first);
    //finds all the stuff in quotes for the first half
    do{
        a = temp.find('\"');
        temp = temp.substr(a+1,temp.length());
        a = temp.find('\"');
        q.colList[b] = temp.substr(0,a-1);
        temp = temp.substr(a+1,temp.length());
        b++;
    }while(b < q.colCount);
    //sees if there is a where and exits function if not
    if (last.find("where") == -1){
        return;
    }
    //finds all the stuff in quotes for the second half
    b = 0;
    temp = lower(last);
    do{
        a = temp.find('\"');
        temp = temp.substr(a+1,temp.length());
        a = temp.find('\"');
        q.whereLeft[b] = temp.substr(0,a-1);
        //left when stuff
        temp = temp.substr(a+1,temp.length());
        a = temp.find('\"');
        q.logicList[c] = temp.substr(0,a-1);
        //opperators
        temp = temp.substr(a+1,temp.length());
        a = temp.find('\"');
        q.whereRight[b] = temp.substr(0,a-1);
        //right when stuff
        temp = temp.substr(a+1,temp.length());
        //if there is space for an ANDOR, this gets it
        if(q.whereCount > 0){
            q.ANDORlist[c] = temp.substr(0,3);
        }
        b++;
        c++;
    }while(b < q.whereCount);

}

bool generateResults(Query& q, string db[][COLMAX]){
    int a[4];
    int b[4];
    ofstream oFile;
    oFile.open("queryoutput.txt",ios_base::app);
    //if its just "*" it prints the database
    if(q.colList[0] == "*" && q.whereCount == 0){
        for(int i = 0; i < ARSIZE; i++){
            for (int j = 0; j < COLMAX; j++){
                oFile <<db[i][j];
            }
        }
        return true;
    }
    oFile.close();
    //sees how many colcount there is
    //to see how many I needs to label
    switch(q.colCount){
    case 5:
    a[4] = sorter(q.colList[4],4);
    case 4:
    a[3] = sorter(q.colList[3],3);
    case 3:
    a[2] = sorter(q.colList[2],2);
    case 2:
    a[1] = sorter(q.colList[1],1);
    case 1:
    a[0] = sorter(q.colList[0],0);
    break;
    }
    
    switch(q.whereCount){
    case 5:
    b[4] = sorter(q.whereLeft[4],4);
    case 4:
    b[3] = sorter(q.whereLeft[3],3);
    case 3:
    b[2] = sorter(q.whereLeft[2],2);
    case 2:
    b[1] = sorter(q.whereLeft[1],1);
    case 1:
    b[0] = sorter(q.whereLeft[0],0);
    break;
    }

    //does the when opperations
    opps(b,a,q,db);

    return true;

}

void printer (int col, string db[ARSIZE][COLMAX],int a[4],Query& q){
    int temp = 0;
    ofstream oFile;
    oFile.open("queryoutput.txt",ios_base::app);
    for (int i = 0; i < col; i++){
        for(int j = 0; j < q.colCount; j++){
            temp = a[j];
            oFile << db[col][temp];
        }
        
    }
    oFile.close();

}


void opps(int a[4], int b[4], Query& q, string db[ARSIZE][COLMAX]){
    
    int temp = 0;
    
    for (int i = 0; i < q.whereCount; i++){
        temp = b[i];
        if(q.logicList[i] == "=="){
            for (int j = 0; j < ARSIZE; j++){
                if(db[j][temp] == q.whereRight[i]){
                    printer(j,db,b,q);
                }
            }
        }
        if(q.logicList[i] == "!="){
            for (int j = 0; j < ARSIZE; j++){
                if(db[j][temp] != q.whereRight[i]){
                    printer(j,db,b,q);
                }
        }
        }
        if(q.logicList[i] == "<="){
            
            for (int j = 0; j < ARSIZE; j++){
                if(stoi(db[j][temp]) == stoi(q.whereRight[i])){
                    printer(j,db,b,q);
                }
            }
        
        }
        if(q.logicList[i] == ">="){
           
            for (int j = 0; j < ARSIZE; j++){
                if(stoi(db[j][temp]) == stoi(q.whereRight[i])){
                    printer(j,db,b,q);
                }
            }
        
        }
        if(q.logicList[i] == "<"){
            
            for (int j = 0; j < ARSIZE; j++){
                if(stoi(db[j][temp]) == stoi(q.whereRight[i])){
                    printer(j,db,b,q);
                }
            }
        
        }
        if(q.logicList[i] == ">"){
           
            for (int j = 0; j < ARSIZE; j++){
                if(stoi(db[j][temp]) == stoi(q.whereRight[i])){
                    printer(j,db,b,q);
                }
            }
        
        }
    }

}


//gets the column number from string
//if there is a shorter way of doing this I don't know it
int sorter(string q, int a){
    if(q == "Name of Satellite, Alternate Names"){
        return 0;
    }else if(q == "Current Official Name of Satellite"){
        return 1;
    }else if(q == "Country/Org of UN Registry"){
        return 2;
    }else if(q == "Country of Operator/Owner"){
        return 3;
    }else if(q == "Operator/Owner"){
        return 4;
    }else if(q == "Users"){
        return 5;
    }else if(q == "Purpose"){
        return 6;
    }else if(q == "Detailed Purpose"){
        return 7;
    }else if(q == "Class of Orbit"){
        return 8;
    }else if(q == "Type of Orbit"){
        return 9;
    }else if(q == "Longitude of GEO (degrees)"){
        return 10;
    }else if(q == "Perigee (km)"){
        return 11;
    }else if(q == "Apogee (km)"){
        return 12;
    }else if(q == "Eccentricity"){
        return 13;
    }else if(q == "Inclination (degrees)"){
        return 14;
    }else if(q == "Period (minutes)"){
        return 15;
    }else if(q == "Launch Mass (kg.)"){
        return 16;
    }else if(q == " Dry Mass (kg.) "){
        return 17;
    }else if(q == "Power (watts)"){
        return 18;
    }else if(q == "Date of Launch"){
        return 19;
    }else if(q == "Expected Lifetime (yrs.)"){
        return 20;
    }else if(q == "Contractor"){
        return 21;
    }else if(q == "Country of Contractor"){
        return 22;
    }else if(q == "Launch Site"){
        return 23;
    }else if(q == "Launch Vehicle"){
        return 24;
    }else if(q == "COSPAR Number"){
        return 25;
    }else if(q == "NORAD Number"){
        return 26;
    }else{
        return -1;
    }
}


//With documentation expect code to be ~400 lines give or take 100