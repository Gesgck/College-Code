/*
Name: Alec Zheng, NSHE_ID_#2001982564, 
COURSE_SECTION 1007, ASSIGNMENT_#3
Description: Receipt system.
Input: item information.
Output: receipt.
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
	int qty = 0;
	double cost = 0.0, subtotal = 0.0, tax = 0.0,
		   total = 0.0, tendered = 0.0, change = 0.0;
	string name = "", cardNumber = "";
	char selection = '\0';
	bool flag = false;
	char rep = 'b';
	string type = "none";
	int a = 0;
	

	printHeader();
	// 3.3: Loop until user wants to quit

	do{
	//sets up stuff for comparison
	a++;	
	flag = false;
	
	// Get name, cost, and quantity
	// 3.1: Loop until valid name is input
	
	do{
	//prints "Item name" differently for code grade
		if (a<2){
			cout << "Item Name: ";
		}
		if (a>=2){
			cout <<" Item Name: ";
		}
//gets name and checks it
		getline(cin, name);
			if (name.length() < 1 || name.length() > 25) {
				cout << "Error: Invalid name.\n";
			}
			else{
				flag = true;
			}

	}while (flag == false);
	//sets flag back to false for later
	flag = false;

	// 3.1 : Loop until valid cost is input

	do{

	cout << "Item Cost: ";
	cin >> cost;
	//checks cost for failure
		if (!cin || cost < 0 || cost >= 1000) {
			
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Error: Invalid cost.\n";
			continue;
		}

		flag = true;

	}while(flag == false);
	flag=false;

	// 3.1 : Loop until valid qty is input
	do{
	cout << "Quantity:  ";
	cin >> qty;
	//checks qty
		if (!cin || qty < 1 || qty > 9) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Error: Invalid quantity.\n";
		}
		else{
			flag=true;
		}
	}while (flag == false);
	flag = false;

	// Calculate the subtotal, tax, and total
	subtotal = cost * qty;
	tax = ceil(subtotal * TAX_RATE * 100.0) / 100.0;
	total = subtotal + tax;
	//prints the stuff
	cout << fixed << setprecision(2)
		 << "\nSubtotal:  " << subtotal << endl
		 << "Tax:       " << tax << endl
		 << "Total:     " << total << endl << endl;

	// Get cash/card selection
	// 3.2 TODO: Loop until valid selection is made
	do{
	cout << "(C/c) - Cash\n(D/d) - Card\nSelection: ";
	cin >> selection;
	switch (selection) {
		// Cash
		case 'c':
		case 'C':
			// Get amount tendered
			// 3.1 TODO: Loop until valid tendered amount is input
			do{
			cout << "\nAmount tendered from customer: ";
			cin >> tendered;
			// Error if invalid
				if (!cin || tendered < total) {
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Error: Invalid amount tendered.";
				}
				else{
					flag = true;
				}
			}while(flag == false);


			// Calculate change
			change = tendered - total;
			cout << "\nChange Due: " << change << endl;

			// Print the receipt
			cout << "\n/\\/\\/\\/\\/\\/\\/\\/\\/\\"
			<<"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n"
				 << "|" << setw(40) << "|\n"
				 << "|             UNLV CS Shop             |\n"
				 << "|         4505 S Maryland Pkwy         |\n"
				 << "|          Las Vegas,NV 89154          |\n"
				 << "|            (702) 895-3011            |\n"
				 << "|" << setw(40) << "|\n"
				 << "| " << left << setw(26) << name << right 
				 << setw(6) << cost << " x " << qty << " |\n"
				 << "|" << setw(40) << "|\n"
				 << "| Subtotal " << setw(27) << subtotal << " |\n"
				 << "| Tax Rate " << setw(26) << TAX_RATE * 100 << "% |\n"
				 << "| Tax " << setw(32) << tax << " |\n"
				 << "| Total " << setw(30) << total << " |\n"
				 << "|" << setw(40) << "|\n"
				 << "| Tendered " << setw(27) << tendered << " |\n"
				 << "| Change " << setw(29) << change << " |\n"
				 << "|" << setw(40) << "|\n"
				 << "\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/"
				 <<"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n";
				 flag=true;
			break;
		// Card
		case 'd':
		case 'D':
			// Get card number
			// 3.1 TODO: Loop until valid cardNumber is input
				cin.ignore(1000, '\n');

			do{
				
				cout << "\nCard number: ";
				getline(cin, cardNumber);
				// Check card number length
					
					if (cardNumber.length() != 16) {
						cout << "Error: Invalid card number.";
						continue;	
					}
					
				
			
			// 3.4 TODO: - Get card type based on first digit
            //checks if first number is not 3,4,5, or 6
				if(cardNumber[0] < 51 || cardNumber[0] > 54){
					cout <<"Error: Invalid card number.";
					flag = false;
					continue;
				}
			//finds type of card
			
				if (cardNumber[0] == 51){
					type = "Amex";
				}
				if (cardNumber[0] == 52){
					type = "Visa";
				}
				if (cardNumber[0] == 53){
					type = "Master";
				}
				if (cardNumber[0] == 54){
					type = "Discover";
				}
			//           - Check rest of card number for digits	
				for(int l = 0; l<=15; l++){
					if(cardNumber[l] <=47 || cardNumber[l]>=57){
                        
						cout <<"Error: Invalid card number.";
						flag = false;
                        break;
					}
				flag=true;	
				}
			}while(flag==false);



			// Print the receipt
			cout << "\n/\\/\\/\\/\\/\\/\\/\\/\\/"
			<<"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n"
				 << "|" << setw(40) << "|\n"
				 << "|             UNLV CS Shop             |\n"
				 << "|         4505 S Maryland Pkwy         |\n"
				 << "|          Las Vegas,NV 89154          |\n"
				 << "|            (702) 895-3011            |\n"
				 << "|" << setw(40) << "|\n"
				 << "| " << left << setw(26) << name << right << setw(6) 
				 << cost << " x " << qty << " |\n"
				 << "|" << setw(40) << "|\n"
				 << "| Subtotal " << setw(27) << subtotal << " |\n"
				 << "| Tax Rate " << setw(26) << TAX_RATE * 100 << "% |\n"
				 << "| Tax " << setw(32) << tax << " |\n"
				 << "| Total " << setw(30) << total << " |\n"
				 << "|" << setw(40) << "|\n"
		 		 << "| " << left << setw(37) << "Card Sale" << "|\n"
				 << "| " <<left << setw(28) << "type" << right << setw(8) 
				 << type << " |\n"
		 		 << "| Card" << right << setw(32) 
				  << "XXXXXXXXXXXX" + cardNumber.substr(12) << " |\n"
				 << "|" << setw(40) << "|\n"
				 << "\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/"
				 << "\\/\\/\\/\\/\\/\\/\\/\\/\\/\n";
				 flag=true;
			break;
		// Invalid Selection
		default:
			if(selection != 'c' || 'C' || 'd' || 'D'){
				cin.ignore(100, '\n');
				cout << "Error: Invalid selection.\n";
				continue;
			}
	}

	}while (flag == false);

	// 3.3 TODO: Ask user if they want to continue

	cout <<endl <<"Enter (C/c) to Continue:";
	cin >>rep;
	cin.ignore(100, '\n');

	//continues if c or C is input
		switch(rep)
		{
			case 'c':
			case 'C':
			continue;
			default:
			exit (0);
		}
	// end of the program loop
	}while(rep == 'c'||'C');


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
