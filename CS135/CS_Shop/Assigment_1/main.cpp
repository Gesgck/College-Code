/*   
Name:Alec Zheng,NSHE_#2001982564,SECTION 1007,ASSIGNMENT_#csshop
Description: Takes items and cash to give receipt.
Input: Items bought by the customer.
Output: A receipt for the purchase.
*/
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double TAX_RATE = 0.0825;

/*
	main: Designated start of the program.
	parameters: argument count, array of command line args
	return value: Exit status
*/
int main(int argc, char const *argv[]) {
	// Variables declarations
	string name;
	double cost = 0.0, subtotal = 0.0, tax = 0.0,
		   total = 0.0, tendered = 0.0, change = 0.0;
	int qty = 0;

	// Program header output
	// The output looks strange because the line length has been limited
	// It will output to the terminal OK
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

	// 1.1 Get name, cost, and quantity

    cout <<"Item Name: ";
    getline (cin,name);
    cout <<"Item Cost: ";
    cin >>cost;
    cout << "Quantity: ";
    cin >>qty;
    cout <<endl;



	// 1.2 Calculate the subtotal, tax, and total

    subtotal= cost*qty;
    tax= subtotal*TAX_RATE;
    tax = ceil(tax * 100.0)/100.0;
    total = subtotal + tax;

    cout <<setfill(' ') <<fixed <<setprecision(2)
	<<setw(11) <<left <<"Subtotal:" <<right <<subtotal <<endl 
	<<setw(11) <<left <<"Tax:" <<right <<tax <<endl 
	<<setw(11) <<left <<"Total:" <<right <<total <<endl <<endl;

	// 1.3 Get amount tendered and calculate change
    

    cout <<"Amount tendered from customer: ";
    cin >>tendered;
    cout <<endl;
    change = tendered - total;
    cout <<"Change Due: " <<change <<endl;




	// Print the receipt top
	cout << "\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/"
	     << "\\/\\\n"
		 << "|                                      |\n"
		 << "|             UNLV CS Shop             |\n"
		 << "|         4505 S Maryland Pkwy         |\n"
		 << "|          Las Vegas,NV 89154          |\n"
		 << "|            (702) 895-3011            |\n"
		 << "|                                      |\n";

	// 1.4 Print the input/calculated information
	cout <<fixed <<setprecision(2) <<setfill(' ')
    <<"| "<<setw(20) <<left << name <<setw(12) 
		<<right <<cost <<" x " <<qty  <<" |"<<endl
	<<"|                                      |\n"
	<<"| "<<setw(10) <<left << "Subtotal" <<setw(26) 
		<<right <<subtotal <<" |"<<endl
	<<"| "<<setw(10) <<left << "Tax Rate" <<setw(26) 
		<<right <<"8.25%" <<" |"<<endl
	<<"| "<<setw(10) <<left << "Tax" <<setw(26) <<right <<tax <<" |"<<endl
	<<"| "<<setw(10) <<left << "Total" <<setw(26) 
		<<right <<total <<" |"<<endl
	<<"|                                      |\n"
	<<"| "<<setw(10) <<left << "Tendered" <<setw(26) 
		<<right <<tendered <<" |"<<endl
	<<"| "<<setw(10) <<left << "Change" <<setw(26) 
		<<right <<change <<" |"<<endl;



	// Print the receipt bottom
	cout << "|                                      |\n"
		 << "\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/"
		 << "\\/\\/";

	return 0;
}

// Copyright 2022 Alex St. Aubin. All Rights Reserved.