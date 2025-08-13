#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// Global constants
const double taxRate = 0.0825;

/*
*/
void readPreviousTransactions(ifstream &iFile,
              int &itemCnt,
              int ids[],
              string names[],
              double costs[],
              int qtys[],
              string paymentTypes[],
              string payments[])
{
    int commaLoc = 0;
	string line = "";

	while (!iFile.eof()) {
		// Get next line and skip if it is blank
		getline(iFile, line);
        if (!iFile) continue;

        // id
		commaLoc = line.find(',');
		ids[itemCnt] = stoi(line.substr(0, commaLoc));
		line = line.substr(commaLoc + 1);

		// name
		commaLoc = line.find(',');
		names[itemCnt] = line.substr(0, commaLoc);
		line = line.substr(commaLoc + 1);

		// cost
		commaLoc = line.find(',');
		costs[itemCnt] = stod(line.substr(0, commaLoc));
		line = line.substr(commaLoc + 1);

		// quantity
		commaLoc = line.find(',');
		qtys[itemCnt] = stoi(line.substr(0, commaLoc));
		line = line.substr(commaLoc + 1);
	
		//payment type
		commaLoc = line.find(',');
		paymentTypes[itemCnt] = line.substr(0, commaLoc);

		// payment
		payments[itemCnt] = line.substr(commaLoc + 1);

		itemCnt++;
	}

	iFile.close();
}

/*
*/
void readInventory(string names[], double costs[])
{
    ifstream iFile("data/inventory.csv");
    int commaLoc = 0, i = 0;
    string line = "";

    while (!iFile.eof()) {
		// Get next line and skip if it is blank
        getline(iFile, line);
        if (!iFile) continue;

        // name
        commaLoc = line.find(',');
        names[i] = line.substr(0, commaLoc);
        line = line.substr(commaLoc + 1);

        // cost
        costs[i] = stod(line);

        i++;
    }

    iFile.close();
}

/*
*/
double calculateTotal(double costs[], int qtys[], int start, int end)
{
	double total = 0.0;
	// iterate over each item in transaction
	for (int i = start; i < end; i++)
		// sum totals of costs for quantity
		total += costs[i] * qtys[i];
	return total;
}

/*
*/
double calculateTax(double cost)
{
	// Calculate rounded tax and return it
	return ceil(cost * taxRate * 100.0) / 100.0;
}

/*
*/
void calculateTotals(int itemCnt,
                     int& transactionCnt,
                     int ids[],
                     double costs[],
                     int qtys[],
                     double subtotals[],
                     double taxes[],
                     double totals[])
{
    int start = 0, end = 0, currentId = 0;
    while (end < itemCnt) {
    	// Find start/end/currentID
        start = end;
		currentId = ids[start];
		while(ids[end] == currentId) end++;

		// Calculate subtotal, tax, and total
        subtotals[transactionCnt] = calculateTotal(costs, qtys, start, end);
		taxes[transactionCnt] = calculateTax(subtotals[transactionCnt]);
		totals[transactionCnt] = subtotals[transactionCnt] + taxes[transactionCnt];
        transactionCnt++;
    }
}

/*
*/
void printHeader()
{
	cout << "+-----------------------------------------------------------------------------+ \n"
		 << "|    UU     UU  NNNN     NN  LL       VV      VV         CCCCCC    SSSSSSSS   | \n"
		 << "|   /UU    /UU /NN/NN   /NN /LL      /VV     /VV        CC////CC  SS//////    | \n"
		 << "|   /UU    /UU /NN//NN  /NN /LL      /VV     /VV       CC    //  /SS          | \n"
		 << "|   /UU    /UU /NN //NN /NN /LL      //VV    VV       /CC        /SSSSSSSSS   | \n"
		 << "|   /UU    /UU /NN  //NN/NN /LL       //VV  VV        /CC        ////////SS   | \n"
		 << "|   /UU    /UU /NN   //NNNN /LL        //VVVV         //CC    CC        /SS   | \n"
		 << "|   //UUUUUUU  /NN    //NNN /LLLLLLLL   //VV           //CCCCCC   SSSSSSSS    | \n"
		 << "|    ///////   //      ///  ////////     //             //////   ////////     | \n"
		 << "|                                                                             | \n"
		 << "|                  SSSSSSSS  HH      HH    OOOOOOO    PPPPPPP                 | \n"
		 << "|                 SS//////  /HH     /HH   OO/////OO  /PP////PP                | \n"
		 << "|                /SS        /HH     /HH  OO     //OO /PP   /PP                | \n"
		 << "|                /SSSSSSSSS /HHHHHHHHHH /OO      /OO /PPPPPPP                 | \n"
		 << "|                ////////SS /HH//////HH /OO      /OO /PP////                  | \n"
		 << "|                       /SS /HH     /HH //OO     OO  /PP                      | \n"
		 << "|                 SSSSSSSS  /HH     /HH  //OOOOOOO   /PP                      | \n"
		 << "|                ////////   //      //    ///////    //                       | \n"
		 << "+-----------------------------------------------------------------------------+ \n";
}

/*
*/
void calculateSummary(int transactionCnt,
                      double &totalSubtotal,
                      double &totalTax,
                      double &totalTotal,
					  int &minIdx,
                      int&maxIdx,
                      double subtotals[],
                      double taxes[],
                      double totals[])
{
	// iterate over all the transactions
	for (int i = 0; i < transactionCnt; i++) {
		// sum subtotals, taxes, and totals
		totalSubtotal += subtotals[i];
		totalTax += taxes[i];
		totalTotal += totals[i];
		// test for new min
		if (totals[i] < totals[minIdx])
			minIdx = i;
		// test for new max
		if (totals[i] > totals[maxIdx])
			maxIdx = i;
	}
}

/*
*/
void printSummary(int transactionCnt,
                  double totalSubtotal,
                  double totalTax,
                  double totalTotal,
				  int minIdx,
                  int maxIdx,
                  double subtotals[],
                  double taxes[],
                  double totals[])
{
	// notify user summary is printing
    cout << "\nPrinting sales report to summary.txt...\n";
    // print summary
	ofstream oFile("summary.txt");
	oFile << setfill('.')
		  << "+--------------------------------------------------------------+\n"
		  << "| " << left << setw(40) << "Total Transactions" << right << setw(20) << transactionCnt << " |\n"
		  << "|                                                              |\n"
		  << "| " << left << setw(40) << "Total Pre-tax Sales" << right << setw(20) << totalSubtotal << " |\n"
		  << "| " << left << setw(40) << "Total Taxes Charged" << right << setw(20) << totalTax << " |\n"
		  << "| " << left << setw(40) << "Total Post-tax Sales" << right << setw(20) << totalTotal << " |\n"
		  << "|                                                              |\n"
		  << "| " << left << setw(40) << "Average Pre-tax Sale" << right << setw(20) << totalSubtotal / transactionCnt << " |\n"
		  << "| " << left << setw(40) << "Average Post-tax Sale" << right << setw(20) << totalTotal / transactionCnt << " |\n"
		  << "|                                                              |\n"
		  << "| " << left << setw(40) << "Lowest Sale ID" << right << setw(20) << minIdx << " |\n"
		  << "| " << left << setw(40) << "Lowest Sale Subtotal" << right << setw(20) << subtotals[minIdx] << " |\n"
		  << "| " << left << setw(40) << "Lowest Sale Tax" << right << setw(20) << taxes[minIdx] << " |\n"
		  << "| " << left << setw(40) << "Lowest Sale Total" << right << setw(20) << totals[minIdx] << " |\n"
		  << "|                                                              |\n"
		  << "| " << left << setw(40) << "Highest Sale ID" << right << setw(20) << maxIdx << " |\n"
		  << "| " << left << setw(40) << "Highest Sale Subtotal" << right << setw(20) << subtotals[maxIdx] << " |\n"
		  << "| " << left << setw(40) << "Highest Sale Tax" << right << setw(20) << taxes[maxIdx] << " |\n"
		  << "| " << left << setw(40) << "Highest Sale Total" << right << setw(20) << totals[maxIdx] << " |\n"
		  << "+--------------------------------------------------------------+\n";
	oFile.close();
}

/*
*/
int getSelectedItem(string invNames[], double invCosts[])
{
    int selection = 0;
    // output menu
    cout << setfill('-') << "\n+"
         << setw(34) << right << '+'
         << setw(33) << right << '+'
         << setw(31) << right << "+\n";
    cout << "| -1   End Transaction" << setfill(' ') << setw(13) << right << '|'
         << setw(33) << '|' << setw(31) << "|\n";
    for (int i = 0; i < 9; i++)
        cout << "| "
             << left << setw(5) << i
             << left << setw(19) << invNames[i]
             << right << setw(7) << invCosts[i]
             << " | "
             << left << setw(5) << i + 9
             << left << setw(18) << invNames[i + 9]
             << right << setw(7) << invCosts[i + 9]
             << " | "
             << left << setw(5) << i + 18
             << left << setw(15) << invNames[i + 18]
             << right << setw(7) << invCosts[i + 18]
             << " |"
             << endl;
    cout << setfill('-') << '+'
         << setw(34) << right << '+'
         << setw(33) << right << '+'
         << setw(31) << right << "+\n";
    // get selection
    while (true)
    {
    	// prompt/read in
        cout << "Selected Item: ";
        cin >> selection;
        // error checking
        if (!cin || selection < -1 || selection > 26)
        {
            cout << "Error: Invalid selection\n\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        return selection;
    }
}

/*
*/
string getCardType(string num)
{
    const int LENGTH = 16;
    string myType = "";

    // Check for invalid length
    if (num.length() != LENGTH) return myType;

    // Get card type
    switch (num[0]) {
		case '3':
			myType = "Amex";
            break;
		case '4':
			myType = "Visa";
            break;
		case '5':
			myType = "Master";
            break;
		case '6':
			myType = "Discover";
            break;
	}

	// Check for invalid digits
    for (int i = 1; i < LENGTH; i++)
        if (num[i] < 48 || num[i] > 57) myType = "";
    
    return myType;
}

/*
*/
void printReceiptTop(ofstream &oFile, int start, int end, string names[], double costs[],
					 int qtys[],double subtotal, double tax, double total)
{
	// Header
	oFile << fixed << setprecision(2)
		 << "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n"
		 << "|" << setw(40) << "|\n"
		 << "|             UNLV CS Shop             |\n"
		 << "|         4505 S Maryland Pkwy         |\n"
		 << "|          Las Vegas,NV 89154          |\n"
		 << "|            (702) 895-3011            |\n"
		 << "|" << setw(40) << "|\n";
	// Items
	for (int i = start; i < end; i++) {
		oFile << "| " << left << setw(26) << names[i]
			 << right << setw(6) << costs[i] << " x " << qtys[i] << " |\n";
	}
	// Subtotal, tax rate, tax, and total
	oFile << "|" << setw(40) << "|\n"
		 << "| Subtotal" << setw(28) << subtotal << " |\n"
		 << "| Tax Rate" << setw(27) << taxRate * 100 << "% |\n"
		 << "| Tax" << setw(33) << tax << " |\n"
		 << "| Total" << setw(31) << total << " |\n"
		 << "|" << setw(40) << "|\n";
}

/*
*/
void printReceiptBottom(ofstream &oFile, double tendered, double change)
{
	// Amount paid and change
	oFile << "| Tendered" << setw(28) << tendered << " |\n"
		  << "| Change" << setw(30) << change << " |\n"
		  << "|" << setw(40) << "|\n"
		  << "\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n";
}

/*
*/
void printReceiptBottom(ofstream &oFile, string cardNumber, string cardType)
{
	// Card type and last 4 of card number
	oFile << "| " << left << setw(37) << "Card Sale" << "|\n"
		  << "| Type" << right << setw(32) << cardType << " |\n"
		  << "| Card" << right << setw(32) << "XXXXXXXXXXXX" + cardNumber.substr(12) << " |\n"
		  << "|" << setw(40) << "|\n"
		  << "\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n";
}
