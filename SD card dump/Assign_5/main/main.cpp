// TODO: Your program header
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
	string names[MAX_ITEMS], paymentTypes[MAX_ITEMS], payments[MAX_ITEMS], invNames[INV_SIZE];

    // Open file passed as command line arg. You must define
    //  the behavior of this function in the function stub below
    openFile(iFile, argc, argv);

    // TODO 5.2: Call readPreviousTransactions()
    //            (defined in provided_functions.cpp)





    // TODO 5.2: Call readInventory()
    //            (defined in provided_functions.cpp)





    // TODO 5.2: Call calculateTotals()
    //            (defined in provided_functions.cpp)





    // TODO 5.2: Call printHeader()
    //            (defined in provided_functions.cpp)





    while (true) {
        // TODO 5.3: Call getMode() and save the
        //            returned value into registerMode





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





    // TODO 5.1: Open file name contained in argv/error/exit if invalid
    




}

// TODO 5.3: Define/write getMode()





// TODO 5.4: Define/write addTransaction()





// TODO 5.4.1: Define/write getQuantity()





// TODO 5.4.3: Define/write getPaymentType()





// TODO 5.4.4: Define/write getPayment()





// TODO 5.4.5: Define/write getPayment()




