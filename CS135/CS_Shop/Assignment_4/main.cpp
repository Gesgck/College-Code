/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007, ASSIGNMENT_#4
Description: prints multiple receipts.
Input: csv files containing purchase info.
Output: receipts and summary.
*/

#include <iostream>
#include <iomanip>
#include <cmath>
// 3.1 TODO: Include <fstream>
#include <fstream>




using namespace std;

const double TAX_RATE = 0.0825;
const int MAX_ITEMS = 1000;
const int MAX_TRANSACTIONS = 100;

void printHeader();

/*
	main: Designated start of the program.
	parameters: argument count, array of command line args
	return value: Exit status
*/
int main(int argc, char const *argv[])
{
    string fname = "";
	string line, sub, card, cardNumber;
	char sum = ' ';
    int itemCnt = 0, start = 0, end = 0, currentId = 0, 
	transactionCnt = 0, lowId = 0, highId = 0;
	double pre_t = 0, post_t = 0, total_t = 0, avpre_t = 0,
		   avpost_t = 0, min = 0, max = 0;
	int ids[MAX_ITEMS], qtys[MAX_ITEMS];
	double costs[MAX_ITEMS], subtotals[MAX_TRANSACTIONS],
           taxes[MAX_TRANSACTIONS], totals[MAX_TRANSACTIONS];
	string names[MAX_ITEMS], paymentTypes[MAX_ITEMS], payments[MAX_ITEMS];
	ifstream iFile;
	ofstream oFile;
	

    // 4.1 TODO: - Open file name passed in argv
    //           - Error and exit if unable to open
    //           - Usage error if invalid argc

	if (argc != 2){
		cout <<"Usage: ./a.out <file name>";
		exit (0);
	}

	fname = argv[1];
	iFile.open(fname);

	if (!iFile.is_open()){
        cout << "Error: Invalid file name.";
		exit (0);
        }

	

    // 4.2 TODO: - Read from file into arrays using eof while loop:
    //             - first column:  ids
    //             - second column: names
    //             - third column:  costs
    //             - fourth column: qtys
    //             - fifth column:  paymentTypes
    //             - sixth column:  payments
	while (!iFile.eof())
	{
		getline(iFile, line);
		if (line.empty()){
			break;
		}
		//finds the id
		int commaLoc = line.find(',');
		sub = line.substr(0, commaLoc);
		ids[itemCnt] = stoi(sub);
		line = line.substr(commaLoc + 1, line.length());
		//finds the name
		commaLoc = line.find(',');
		sub = line.substr(0, commaLoc);
		names[itemCnt] = sub;
		line = line.substr(commaLoc + 1, line.length());
		//finds the cost
		commaLoc = line.find(',');
		sub = line.substr(0, commaLoc);
		costs[itemCnt] = stod(sub);
		line = line.substr(commaLoc + 1, line.length());
		//finds the qty
		commaLoc = line.find(',');
		sub = line.substr(0, commaLoc);
		qtys[itemCnt] = stoi(sub);
		line = line.substr(commaLoc + 1, line.length());
		//finds the payment type
		commaLoc = line.find(',');
		sub = line.substr(0, commaLoc);
		paymentTypes[itemCnt] = sub;
		line = line.substr(commaLoc + 1, line.length());
		//finds the cash or card #
		commaLoc = line.find(',');
		sub = line.substr(0, commaLoc);
		payments[itemCnt] = sub;
		line = line.substr(commaLoc + 1, line.length());
		itemCnt ++;
	}

	iFile.close();

    // 4.2 TODO: - Print amount of items read in

	cout <<"Number of rows read in: " <<itemCnt <<endl <<endl;




    printHeader();

    // 4.3 TODO: Code section 4.3 in this while loop
    while (end < itemCnt)
    {
		cout << "Printing Customer #" << ids[end] << "'s receipt.\n";
    	// 4.3 TODO: Get start and end point in parallel array

		start = end;

		currentId = ids[start];
		
		while (ids[end] == currentId){
			end++;	
		}
		
		


    	// 4.3 TODO: Calculate subtotal, tax, and total and store
    	//           the 3 calculations in their respective arrays.
		

		for (int i = start; i<end; i++){
			subtotals[transactionCnt] += costs[i] * qtys[i];
		}
		taxes[transactionCnt]=
		ceil(subtotals[transactionCnt] * TAX_RATE * 100.0)/100.0;
		totals[transactionCnt] = 
		subtotals[transactionCnt] + taxes[transactionCnt];
		


    	// 4.3 TODO: Print cash or card receipts to files.

		oFile.open("receipt_"+to_string(currentId)+".txt");

//top of the receipt
		oFile <<fixed <<setprecision(2) 
			<< "\n/\\/\\/\\/\\/\\/\\/\\/\\/\\"
			<<"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n"
				 << "|" << setw(40) << "|\n"
				 << "|             UNLV CS Shop             |\n"
				 << "|         4505 S Maryland Pkwy         |\n"
				 << "|          Las Vegas,NV 89154          |\n"
				 << "|            (702) 895-3011            |\n"
				 << "|" << setw(40) << "|\n";
//loops for each item
		for (int i=start; i < end; i++){
			oFile << "| " << left << setw(26) << names[i] << right 
				 << setw(6) << costs[i] << " x " << qtys[i] << " |\n";
		}

		oFile << "|" << setw(40) << "|\n";

			oFile << "| Subtotal " << setw(27) 
				 << subtotals[transactionCnt] << " |\n"
				 << "| Tax Rate " << setw(26) << TAX_RATE * 100 << "% |\n"
				 << "| Tax " << setw(32) << taxes[transactionCnt] << " |\n"
				 << "| Total " << setw(30) << totals[transactionCnt] << " |\n"
				 << "|" << setw(40) << "|\n";
//bottom of receipt if cash payment
		if (paymentTypes[start]=="cash"){
			oFile << "| Tendered " << setw(27) << stod(payments[start]) << " |\n"
				 << "| Change " << setw(29) 
				 <<stod(payments[start])-totals[transactionCnt] << " |\n";
		}
//bottom of receipt if card payment
		if (paymentTypes[start]=="card"){
			cardNumber = payments[start];
			oFile << "| " <<"Card Sale" << setw(30)  << "|\n" ;
			if (cardNumber[0] == 51){
				card = "Amex";
			}
			if (cardNumber[0] == 52){
				card = "Visa";
			}
			if (cardNumber[0] == 53){
				card = "Master";
			}
			if (cardNumber[0] == 54){
				card = "Discover";
			}
			oFile << "| " <<left << setw(28) << "Type" << right << setw(8) 
				 << card << " |\n"
		 		 << "| Card" << right << setw(32) 
				<< "XXXXXXXXXXXX" + cardNumber.substr(12) << " |\n";
		}
//rest of the receipt
		oFile << "|" << setw(40) << "|\n"
			 << "\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/"
			 << "\\/\\/\\/\\/\\/\\/\\/\\/\\/";


		transactionCnt++;
		oFile.close();
		
    }

    // 4.4 TODO: Prompt for summary/print summary if user wants summary.

	cout <<"Print sales report? (Y/y) for yes, any other key for no:";
	cin >> sum;
//switch statement for summary choice
	switch(sum){
		case 'y':
		case 'Y':
		//math for summary
		for (int i=0; i<itemCnt; i++){
			pre_t += costs[i] * qtys[i];
		}

		total_t = pre_t*TAX_RATE;
		post_t = pre_t + total_t;
		avpre_t = pre_t / transactionCnt;
		avpost_t = post_t / transactionCnt;

		//finds lowest and highest sale id
		min = subtotals[0];
		max = subtotals[0];
		for (int i=0; i<transactionCnt;i++){
			if(subtotals[i]>max){
				max = subtotals[i];
				highId = i;
			}
			if(subtotals[i]<min){
				min = subtotals[i];
				lowId = i;
				
			}
		}

		


		//outputs summary

			cout<<endl <<"Printing sales report to summary.txt...";

			oFile.open("summary.txt");
			oFile<<endl <<"+-------------------------"
				 <<"-------------------------------------+\n"
				 <<setfill('.') <<"| " <<setw(40) <<left <<"Total Transactions" 
				 <<setw(20) <<right <<transactionCnt <<" |\n"
				 <<setfill(' ') <<"| " <<setw(63) <<" |\n"
				 <<setfill('.') <<"| " <<setw(40) <<left <<"Total Pre-tax Sales" 
				 <<setw(20) <<right <<pre_t <<" |\n"
				 <<"| " <<setw(40) <<left <<"Total Taxes Charged" 
				 <<setw(20) <<right <<total_t <<" |\n"
				 <<"| " <<setw(40) <<left <<"Total Post-tax Sales" 
				 <<setw(20) <<right <<post_t <<" |\n"
				 <<setfill(' ') <<"| " <<setw(63) <<" |\n"
				 <<setfill('.') <<"| " <<setw(40) <<left <<"Average Pre-tax Sale" 
				 <<setw(20) <<right <<avpre_t <<" |\n"
				 <<"| " <<setw(40) <<left <<"Average Post-tax Sale" 
				 <<setw(20) <<right <<avpost_t <<" |\n"
				 <<setfill(' ') <<"| " <<setw(63) <<" |\n"
				 <<setfill('.') <<"| " <<setw(40) <<left <<"Lowest Sale ID" 
				 <<setw(20) <<right <<lowId <<" |\n"
				 <<"| " <<setw(40) <<left <<"Lowest Sale Subtotal" 
				 <<setw(20) <<right <<subtotals[lowId] <<" |\n"
				 <<"| " <<setw(40) <<left <<"Lowest Sale Tax" 
				 <<setw(20) <<right <<taxes[lowId] <<" |\n"
				 <<"| " <<setw(40) <<left <<"Lowest Sale Total" 
				 <<setw(20) <<right <<totals[lowId] <<" |\n"
				 <<setfill(' ') <<"| " <<setw(63) <<" |\n"
				 <<setfill('.') <<"| " <<setw(40) <<left <<"Highest Sale ID" 
				 <<setw(20) <<right <<highId <<" |\n"
				 <<"| " <<setw(40) <<left <<"Highest Sale Subtotal" 
				 <<setw(20) <<right <<subtotals[highId] <<" |\n"
				 <<"| " <<setw(40) <<left <<"Highest Sale Tax" 
				 <<setw(20) <<right <<taxes[highId] <<" |\n"
				 <<"| " <<setw(40) <<left <<"Highest Sale Total" 
				 <<setw(20) <<right <<totals[highId] <<" |\n"
				 <<"+---------------------------------"
				 <<"-----------------------------+";
				break;
		default:
		cout<<endl <<"exiting program without sales report...";
		exit (0);
	}

    oFile.close();

    return 0;
}

/*
	printHeader: Prints program header.
	parameters: none
	return value: none
*/
void printHeader()
{
	cout << "+" << setfill('-') << setw(77) << '-' << "+ \n"
		 << "|    UU     UU  NNNN     NN  LL       VV      VV    "
		 << "     CCCCCC    SSSSSSSS   | \n"
		 << "|   /UU    /UU /NN/NN   /NN /LL      /VV     /VV    "
		 << "    CC////CC  SS//////    | \n"
		 << "|   /UU    /UU /NN//NN  /NN /LL      /VV     /VV    "
		 << "   CC    //  /SS          | \n"
		 << "|   /UU    /UU /NN //NN /NN /LL      //VV    VV     "
		 << "  /CC        /SSSSSSSSS   | \n"
		 << "|   /UU    /UU /NN  //NN/NN /LL       //VV  VV      "
		 << "  /CC        ////////SS   | \n"
		 << "|   /UU    /UU /NN   //NNNN /LL        //VVVV       "
		 << "  //CC    CC        /SS   | \n"
		 << "|   //UUUUUUU  /NN    //NNN /LLLLLLLL   //VV        "
		 << "   //CCCCCC   SSSSSSSS    | \n"
		 << "|    ///////   //      ///  ////////     //         "
		 << "    //////   ////////     | \n"
		 << "|" << setfill(' ') << setw(77) << ' ' << "| \n"
		 << "|                  SSSSSSSS  HH      HH    OOOOOOO  "
		 << "  PPPPPPP                 | \n"
		 << "|                 SS//////  /HH     /HH   OO/////OO "
		 << " /PP////PP                | \n"
		 << "|                /SS        /HH     /HH  OO     //OO"
		 << " /PP   /PP                | \n"
		 << "|                /SSSSSSSSS /HHHHHHHHHH /OO      /OO"
		 << " /PPPPPPP                 | \n"
		 << "|                ////////SS /HH//////HH /OO      /OO"
		 << " /PP////                  | \n"
		 << "|                       /SS /HH     /HH //OO     OO "
		 << " /PP                      | \n"
		 << "|                 SSSSSSSS  /HH     /HH  //OOOOOOO  "
		 << " /PP                      | \n"
		 << "|                ////////   //      //    ///////   "
		 << " //                       | \n"
		 << "+" << setfill('-') << setw(77) << '-' << "+ \n" << setfill(' ');
}
