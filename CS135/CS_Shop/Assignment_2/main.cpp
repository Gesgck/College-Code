/*   
Name:Alec Zheng,NSHE_#2001982564,SECTION 1007,ASSIGNMENT_#csshop2
Description: CS_shop system.
Input: information about items and payment.
Output: recipt with info.
*/
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double TAX_RATE = 0.0825;

void printHeader();

/*
	main: Designated start of the program.
	parameters: argument count, array of command line args
	return value: Exit status
*/
int main(int argc, char const *argv[]) {
	// Variables declarations
	int qty = 0;
	double cost = 0.0, subtotal = 0.0, tax = 0.0,
		   total = 0.0, tendered = 0.0, change = 0.0;
	string name = "";

	printHeader();

	// Get name, cost, and quantity
	cout << "Item Name: ";
	getline(cin, name);
	// 2.1 TODO: Quit program if name length < 1 or name length > 25
	
	int nmelng = name.size();

	if (nmelng < 1 || nmelng > 25 ){
		cout << "Error: Invalid name.";
		exit(0);
	}



	cout << "Item Cost: ";
	cin >> cost;
	// 2.1 TODO: Quit program if cost < 0 or cost >= 1000
	// 2.2 TODO: Quit program if input failure

	if (cost < 0 || cost >= 1000 || cin.fail()){
		cout << "Error: Invalid cost.";
		exit (0);
	}



	cout << "Quantity:  ";
	cin >> qty;
	// 2.1 TODO: Quit program if qty < 1 or qty > 9
	// 2.2 TODO: Quit program if input failure

	if (qty < 1 || qty >9 || cin.fail()){
		cout << "Error: Invalid quantity.";
		exit (0);
	}



	// Calculate the subtotal, tax, and total
	subtotal = cost * qty;
	tax = ceil(subtotal * TAX_RATE * 100.0) / 100.0;
	total = subtotal + tax;

	cout << fixed << setprecision(2)
		 << "\nSubtotal:  " << subtotal << endl
		 << "Tax:       " << tax << endl
		 << "Total:     " << total << endl << endl;

	// 2.3 TODO: Get cash/card selection

	char selection = ' ';

	cout <<"(C/c) - Cash\n(D/d) - Card\nSelection:";
	cin >>selection;

	string cardNumber = "";

	switch (selection){
		case 'c':
		case 'C':
			// Get amount tendered and calculate change
			cout << "\nAmount tendered from customer: ";
			cin >> tendered;
			// 2.1 TODO: Quit program if tendered < total
			// 2.2 TODO: Quit program if input failure

			if (tendered < total || cin.fail()){
				cout <<"Error: Invalid amount tendered.";
				exit (0);
			}

			change = tendered - total;
			cout << "\nChange Due: " << change << endl;
				// Print the receipt
				cout << "\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/"
	     		<< "\\/\\\n"
		 		<< "|                                      |\n"
		 		<< "|             UNLV CS Shop             |\n"
		 		<< "|         4505 S Maryland Pkwy         |\n"
		 		<< "|          Las Vegas,NV 89154          |\n"
		 		<< "|            (702) 895-3011            |\n"
		 		<< "|                                      |\n";
				cout <<fixed <<setprecision(2) <<setfill(' ')
    			<<"| "<<setw(20) <<left << name <<setw(12) 
				<<right <<cost <<" x " <<qty  <<" |\n"
				<<"|                                      |\n"
				<<"| "<<setw(10) <<left << "Subtotal" <<setw(26) 
				<<right <<subtotal <<" |\n"
				<<"| "<<setw(10) <<left << "Tax Rate" <<setw(26) 
				<<right <<"8.25%" <<" |\n"
				<<"| "<<setw(10) <<left << "Tax" <<setw(26) <<right <<tax <<" |\n"
				<<"| "<<setw(10) <<left << "Total" <<setw(26) 
				<<right <<total <<" |\n"
				<<"|                                      |\n"
				<<"| "<<setw(10) <<left << "Tendered" <<setw(26) 
				<<right <<tendered <<" |\n"
				<<"| "<<setw(10) <<left << "Change" <<setw(26) 
				<<right <<change <<" |\n";
				cout << "|                                      |\n"
		 		<< "\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/"
				<< "\\/\\/";
			break;
		case 'd':
		case 'D':
			cout <<endl <<"Card number:";
			cin >>cardNumber;
			//checks if number is 16 digits
				if (cardNumber.length() != 16){
					cout << " Error: Invalid card number.";
					exit (0);
				}
			// Print the receipt
			cout << "\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/"
	     	<< "\\/\\\n"
		 	<< "|                                      |\n"
			<< "|             UNLV CS Shop             |\n"
	 		<< "|         4505 S Maryland Pkwy         |\n"
	 		<< "|          Las Vegas,NV 89154          |\n"
			<< "|            (702) 895-3011            |\n"
	 		<< "|                                      |\n";
			cout <<fixed <<setprecision(2) <<setfill(' ')
    		<<"| "<<setw(20) <<left << name <<setw(12) 
			<<right <<cost <<" x " <<qty  <<" |\n"
			<<"|                                      |\n"
			<<"| "<<setw(10) <<left << "Subtotal" <<setw(26) 
			<<right <<subtotal <<" |\n"
			<<"| "<<setw(10) <<left << "Tax Rate" <<setw(26) 
			<<right <<"8.25%" <<" |\n"
			<<"| "<<setw(10) <<left << "Tax" <<setw(26) <<right <<tax <<" |\n"
			<<"| "<<setw(10) <<left << "Total" <<setw(26) 
			<<right <<total <<" |\n"
			<< "|                                      |\n"
			<< "| Card Sale                            |\n"
			<<"| "<<setw(6) <<left << "Card" <<setw(26) 
			<<right <<"xxxxxxxxxxxx" <<cardNumber[12]
			<<cardNumber[13] <<cardNumber[14] <<cardNumber[15] <<" |\n"
			<< "|                                      |\n"
			<< "\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/"
			<< "\\/\\/";
			break;
		default:
			cout<< " Error: Invalid selection.";
			exit (0);
	}



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
		 << "+" << setfill('-') << setw(77) << '-' << "+ \n";
}

// Copyright 2022 Alex St. Aubin. All Rights Reserved.