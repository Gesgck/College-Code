/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007, ASSIGNMENT_#5
Description: register system with functions.
Input: purchases.
Output: receipts and summaries.
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include "provided_functions.cpp"

using namespace std;

const int MAX_ITEMS = 10000;
const int MAX_TRANSACTIONS = 1000;
const int INV_SIZE = 27;

// Function Prototypes
void openFile(ifstream&, const int, char const *[]);
// TODO 5.3/5.4: Add function prototypes
char getMode();
void addTransaction(int& itemCnt, int& transactionCnt, 
int ids[], string names[],
int qtys[],double costs[], string paymentTypes[],
string payments[],double subtotals[], double taxes[],
double totals[], string invNames[], double invCosts[]);
int getQuantity();
char getPaymentType();
string getPayment(double);
void addTransaction(int& itemCnt, int& transactionCnt, int ids[], 
string names[],int qtys[],double costs[], string paymentTypes[],
string payments[],double subtotals[], double taxes[],
double totals[], string invNames[], double invCosts[]);
void getPayment(string& cardNum, string& cardType);


/*
	main: Designated start of the program.
	parameters: argument count, array of command line args
	return value: Exit status
*/
int main(const int argc, char const *argv[])
{
    // Variables
    int itemCnt = 0, transactionCnt = 0, minIdx = 0, maxIdx = 0;
    double subtotalSum = 0.0, taxSum = 0.0, totalSum = 0.0;
    char registerMode = '\0';
    ifstream iFile;
    int ids[MAX_ITEMS], qtys[MAX_ITEMS];
	double costs[MAX_ITEMS], subtotals[MAX_TRANSACTIONS],
           taxes[MAX_TRANSACTIONS], totals[MAX_TRANSACTIONS], invCosts[INV_SIZE];
	string names[MAX_ITEMS], paymentTypes[MAX_ITEMS], 
    payments[MAX_ITEMS], invNames[INV_SIZE];

    // Open file passed as command line arg. You must define
    //  the behavior of this function in the function stub below
    openFile(iFile, argc, argv);

    // TODO 5.2: Call readPreviousTransactions()
    //            (defined in provided_functions.cpp)
    readPreviousTransactions(iFile,itemCnt,ids,names,costs,
    qtys,paymentTypes,payments);
    



    // 5.2: Call readInventory()
    //            (defined in provided_functions.cpp)
    readInventory(invNames, invCosts);




    // TODO 5.2: Call calculateTotals()
    //            (defined in provided_functions.cpp)
    calculateTotals(itemCnt,transactionCnt,ids,costs,
    qtys,subtotals,taxes,totals);




    // TODO 5.2: Call printHeader()
    //            (defined in provided_functions.cpp)
    printHeader();




    while (true) {
        // TODO 5.3: Call getMode() and save the
        //            returned value into registerMode
        registerMode = getMode();




        // If register mode is 's' then calculate/print summary
        if (registerMode == 's')
        {
            calculateSummary(transactionCnt, subtotalSum, taxSum, totalSum,
                             minIdx, maxIdx, subtotals, taxes, totals);
            printSummary(transactionCnt, subtotalSum, taxSum, totalSum,
                         minIdx, maxIdx, subtotals, taxes, totals);
        }
        // If register mode is 't' then add a transaction
        else
        {
        	// TODO 5.4: call addTransaction() (which you need to declare/define)
            addTransaction(itemCnt, transactionCnt, ids, names,
            qtys, costs, paymentTypes, payments, subtotals, 
            taxes, totals, invNames, invCosts);




        }
    }

    return 0;
}

/*
	openFile: Opens the file name passed in argv.
	parameters: file to open into, argument count, argument vector
	return value: input file (in iFile)
*/
void openFile(ifstream& iFile,
              const int argc,
              char const *argv[])
{
    // TODO 5.1: Usage error if invalid argument count
    if(argc != 2){
        cout <<"Usage: ./a.out <file name>";
        exit (0);
    }




    // TODO 5.1: Open file name contained in argv/error/exit if invalid
    iFile.open(argv[1]);
    if(!iFile){
        cout <<"Error: Invalid file name";
        exit(0);
    }




}

// TODO 5.3: Define/write getMode()
char getMode(){
    char selec = ' ';
    do{
    cout <<"OPTIONS\nS/s - Print Summary"
    << "\nT/t - Add Transaction\nE/e - Exit\nSelection: ";
    cin >> selec;
    if(selec=='S'||selec=='s'||selec=='E'||
    selec=='e'||selec=='T'||selec=='t'){
        break;
    }
    else{
        cout <<"Error: Invalid selection\n\n";
        cin.clear();
        cin.ignore(100,'\n');
    }
    }while(true);

    switch (selec){
        case 'S':
        case 's':
            return 's';
            break;
        case 'T':
        case 't':
            return 't';
            break;
        case 'E':
        case 'e':
        default:
            cout <<"Exiting...\n";
            exit (0);
    }
}




// TODO 5.4: Define/write addTransaction()
void addTransaction(int& itemCnt, int& transactionCnt, 
int ids[], string names[],
int qtys[],double costs[], string paymentTypes[],
string payments[],double subtotals[], double taxes[],
double totals[], string invNames[], double invCosts[]){
    //my own variables
    int item = 0;
    char paymentType = ' ';
    string payment;
    int start = itemCnt;
    //loops till valid input
    while(true){
        item = getSelectedItem(invNames,invCosts);
        if(item == -1){
            break;
        }
        qtys[itemCnt] = getQuantity();
        ids[itemCnt] = transactionCnt+1;
        names[itemCnt] = invNames[item];
        costs[itemCnt] = invCosts[item];
        subtotals[transactionCnt] += (qtys[itemCnt]*costs[itemCnt]); 
        itemCnt++;
    }
    //!!check this!!
    taxes[transactionCnt] = 
    ceil(subtotals[transactionCnt] * taxRate * 100.0)/100.0;
    totals[transactionCnt] = taxes[transactionCnt] + subtotals[transactionCnt];
    paymentType = getPaymentType();
    if(paymentType == 'c'){
        payment = getPayment(totals[transactionCnt]);
        for(int i = start; i <= itemCnt; i++){
            paymentTypes[i] = "cash";
            payments[i] = payment;
        }
        ofstream receiptFile;
        //transaction count starts at 50 for some reason
        receiptFile.open("receipt_" + to_string(transactionCnt-49) + ".txt");
        printReceiptTop(receiptFile,start,itemCnt,names,costs,qtys,
        subtotals[transactionCnt],taxes[transactionCnt],totals[transactionCnt]);
        //a is tendered
        double a = stod(payment);
        double change = a - totals[transactionCnt];
        printReceiptBottom(receiptFile, a, change);
    }
    if(paymentType == 'd'){
        string cardType;
        getPayment(payment,cardType);
        for(int i = start; i <= itemCnt; i++){
            paymentTypes[i] = "card";
            payments[i] = payment;
        }
        ofstream receiptFile;
        //transaction count starts at 50 for some reason
        receiptFile.open("receipt_" + to_string(transactionCnt-49) + ".txt");
        printReceiptTop(receiptFile,start,itemCnt,names,costs,qtys,
        subtotals[transactionCnt],taxes[transactionCnt],totals[transactionCnt]);
        printReceiptBottom(receiptFile, payment, cardType);
    }
    transactionCnt++;
    
}




// TODO 5.4.1: Define/write getQuantity()
int getQuantity(){
    int a = 0;
    int quant = 0;
    //loops till valid input
    do{
    int quantity = 0;
    cout <<"Quantity: ";
    cin >>quantity;
    if(cin.fail()||quantity < 1 ||quantity > 9){
        cout <<"Error: Quantity must be in range: 0 < qty < 10\n\n";
        cin.clear();
        cin.ignore(100,'\n');
    }
    else{
        quant = quantity;
        a = 1;
    }
    }while(a==0);
    return quant;
}




// TODO 5.4.3: Define/write getPaymentType()
char getPaymentType(){
    char sel = ' ';
    //loops till valid input
    do{
    cout <<"\nPayment Type\nC/c - Cash\nD/d - Card\nSelection:";
    
    cin >>sel;
    if(sel == 'C'||sel == 'c'||sel == 'D'||sel == 'd'){
        break;
    }
    /*
    else if(cin.fail()){
        cout <<"Error: Invalid selection\n";
    }
    */
    else{
        cin.clear();
        cin.ignore(100,'\n');
        cout <<"Error: Invalid selection\n";
    }
    }while (true);
    cout <<endl;
    if(sel == 'C'||sel == 'c'){
        return 'c';
    }
    else{
        return 'd';
    }
    
}




// TODO 5.4.4: Define/write getPayment()
string getPayment(double total){
    double tendered = 0;
    cout <<"Total: $" <<total <<endl <<endl;
    //loops till valid input
    do{
    cout <<"Tendered: ";
    cin >>tendered;
    if(cin.fail()||tendered < total){
        cout <<"Error: must receive at least $"<<total <<endl <<endl;
        cin.clear();
        cin.ignore(100,'\n');
    }
    else{
        break;
    }
    }while(true);
    cout <<endl;
    cout <<"Change: $" <<fixed <<setprecision(2) <<tendered-total <<endl;
    string tend = to_string(tendered);
    string tender = tend.substr(0,tend.find('.')+3);
    return tender;
}




// TODO 5.4.5: Define/write getPayment()
void getPayment(string& cardNum, string& cardType){
    //loops till valid input
    do{
        cout <<"Card Number: ";
        cin >>cardNum;
        cardType = getCardType(cardNum);
        if(cardType.empty()){
            cout <<"Error: Invalid card number\n\n";
        }
        else{ 
            break;
        }
    }while(true);
    cout <<endl;
}



