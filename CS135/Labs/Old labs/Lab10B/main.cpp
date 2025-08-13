/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_#10B
Description: finds average of a catalog.
Input: csv file.
Output: list and average.
*/
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
//the struct
struct purchaseType{
    string customerID;
    string productName;
    double price;
    int qtyPurchased;
    double taxRate;
};
//prototypes
void openFile(ifstream&, string);
void readFile(ifstream& iFile, purchaseType purchases[]);
void printPurchaseData(purchaseType purchases[], int size);

//tiny main that only has variables and function calls
int main () {
    //variables
    ifstream iFile;
    string prompt = "Enter file name\n**";
    purchaseType purchases[10];
    int size = 10;
    
    //function calls
    openFile(iFile,prompt);
    readFile(iFile,purchases);
    printPurchaseData(purchases,size);

return 0;

}

void openFile(ifstream& iFile, string prompt){
    string filename;
    do{
    cout <<prompt;
    cin >>filename;
    cout <<endl;
    iFile.open(filename);
    //error checking
    if(!iFile){
        cout <<"Error: Invalid File" <<endl;
    }
    else{

        break;
    }
    }while(true);

}

void readFile(ifstream& iFile, purchaseType purchases[]){
    string items;
    int commaLoc = 0;
//uses getline to get the entire line and runs over it
    for (int i = 0; i < 10; i++){
        
        getline(iFile,items);
        commaLoc = items.find(',');
        purchases[i].customerID = items.substr(0,commaLoc);
        items = items.substr(commaLoc+1,items.length());
        commaLoc = items.find(',');
        purchases[i].productName = items.substr(0,commaLoc);
        items = items.substr(commaLoc+1,items.length());
        commaLoc = items.find(',');
        purchases[i].price = stod(items.substr(0,commaLoc));
        items = items.substr(commaLoc+1,items.length());
        commaLoc = items.find(',');
        purchases[i].qtyPurchased = stoi(items.substr(0,commaLoc));
        items = items.substr(commaLoc+1,items.length());
        commaLoc = items.find(',');
        purchases[i].taxRate = stod(items.substr(0,commaLoc));
    }
}

void printPurchaseData(purchaseType purchases[], int size){
    //variables
    double total = 0;
    double tax = 0;
    double itemtotal;
    int users = 1;
    //printing the table
    cout<< "+-------------+--------------+-------"
    <<"+----------+----------+--------+\n"
    <<"| Customer ID | Product Name | Price | Quantity | Tax Rate | Total  |\n"
    << "+-------------+--------------+-------"
    <<"+----------+----------+--------+\n";
    for(int i = 0; i<size; i++){
        cout <<fixed <<setprecision(2)
        <<"|" <<setw(12) <<right <<purchases[i].customerID <<" |"
        <<setw(13) <<right <<purchases[i].productName <<" |"
        <<setw(6) <<right <<purchases[i].price <<" |"
        <<setw(9) <<right <<purchases[i].qtyPurchased <<" |"
        <<setw(9) <<right <<purchases[i].taxRate * 100 <<" |";
        //math for totals and taxes
        tax = (purchases[i].price * purchases[i].qtyPurchased) * (purchases[i].taxRate);
        itemtotal = ((purchases[i].price * purchases[i].qtyPurchased) + tax);
        total += itemtotal;
        cout <<setw(7) <<right <<itemtotal <<" |" <<endl;
        if (i > 0){
            if(purchases[i].customerID != purchases[i-1].customerID){
                users++;
            }
        }
    }
    cout << "+-------------+--------------+-------"
    <<"+----------+----------+--------+\n"
    <<"Unique users:  " <<users
    <<endl <<"Average total: $" <<total/10;
}