/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#5
Description: Main for chess.
Input: Moves.
Output: Chess board.
*/
#include <iostream>
#include "chessPiece.h"
#include "queenType.h"
#include "rookType.h"
#include "bishopType.h"
#include "knightType.h"
#include <string>

#define RESET "\033[0m"
#define RED "\033[31m"

void outputBoard(chessPiece***);
void clearBoard(chessPiece***);

int main()
{
	chessPiece *** board;

	board = new chessPiece**[8];

	for (int i = 0; i < 8; i++)
		board[i] = new chessPiece*[8];

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board[i][j] = nullptr;


	//place the black chess pieces onto
	//the board
	board[0][3] = new knightType(false);
	board[1][0] = new rookType(false);
	board[1][2] = new bishopType(false);
	board[1][3] = new queenType(false);
	board[1][4] = new bishopType(false);
	board[1][6] = new rookType(false);
	board[2][3] = new knightType(false);

	//place the red chess pieces onto
	//the board
	board[5][4] = new knightType(true);
	board[6][1] = new rookType(true);
	board[6][3] = new bishopType(true);
	board[6][4] = new queenType(true);
	board[6][5] = new bishopType(true);
	board[6][7] = new rookType(true);
	board[7][4] = new knightType(true);	

	outputBoard(board);

	char row1, row2;
	int col1, col2;

	int redPieces = 7;
	int blackPieces = 7;

	bool turn = true;
	bool checker = false;

	std::string temp, temp1;

	while (redPieces > 0 && blackPieces > 0)
	{
		//Red's turn
		if(turn == true){
		do{

			//Starting piece input
			std::cout<<"Enter starting coordinates (Red turn): ";
			std::getline(std::cin,temp);
			row1 = temp[0];
			temp1 = temp.substr(2,1);
			col1 = std::stoi(temp1);
			col1--;
			std::cout<<'\n';

			//check if piece is valid
			if(board[row1-'A'][col1] == nullptr){
				std::cout<<"Starting coordinates Empty!\n";
				continue;
			}
			//Check if piece is of the same team
			else if(board[row1-'A'][col1]->getPlayerType() == false){
				std::cout<<"Invalid piece selected.\n";
				continue;
			}

			//Ending position
			std::cout<<"Enter ending coordinates: ";
			std::getline(std::cin,temp);
			row2 = temp[0];
			temp1 = temp.substr(2,1);
			col2 = std::stoi(temp1);
			col2--;
			std::cout<<'\n';
			checker = board[row1-'A'][col1]->move(row1,col1,row2,col2,board);
			//Loops while move is not made
		}while(checker == false);
		checker = false;
		turn = false;
		outputBoard(board);
		//Finishes and outputs board
		}


		//Black's turn
		if(turn == false){
		do{
			//Starting piece
			std::cout<<"Enter starting coordinates (Black turn): ";
			std::getline(std::cin,temp);
			row1 = temp[0];
			temp1 = temp.substr(2,1);
			col1 = std::stoi(temp1);
			std::cout<<'\n';
			col1--;
			//check if piece is valid
			if(board[row1 - 'A'][col1] == nullptr){
				std::cout<<"Starting coordinates Empty!\n";
				continue;
			}
			//Checks piece team
			else if(board[row1-'A'][col1]->getPlayerType() == true){
				std::cout<<"Invalid piece selected.\n";
				continue;
			}

			std::cout<<"Enter ending coordinates: ";
			std::getline(std::cin,temp);
			row2 = temp[0];
			temp1 = temp.substr(2,1);
			col2 = std::stoi(temp1);
			std::cout<<'\n';
			col2--;
			checker = board[row1-'A'][col1]->move(row1,col1,row2,col2,board);
		}while(checker == false);
		checker = false;
		turn = true;
		outputBoard(board);
		}
	}

	clearBoard(board);

	return 0;
}

void outputBoard(chessPiece *** board)
{
	std::cout<<"   1  2  3  4  5  6  7  8\n";
	for(int i=0;i<8;i++){
		switch (i)
		{
		case 0:
			std::cout<<"A ";
			break;
		case 1:
			std::cout<<"B ";
			break;
		case 2:
			std::cout<<"C ";
			break;
		case 3:
			std::cout<<"D ";
			break;
		case 4:
			std::cout<<"E ";
			break;
		case 5:
			std::cout<<"F ";
			break;
		case 6:
			std::cout<<"G ";
			break;
		case 7:
			std::cout<<"H ";
			break;
		}
		for (int j = 0; j<8;j++){

			if(board[i][j] == nullptr)
				std::cout<<" - ";
			else if(board[i][j]->getPlayerType() == true){
				std::cout << RED;
				
				if (dynamic_cast<bishopType*>(board[i][j])){
					std::cout <<" B ";
				}
				
				if (dynamic_cast<queenType*>(board[i][j])){
					std::cout <<" Q ";
				}
				
				if (dynamic_cast<rookType*>(board[i][j])){
					std::cout <<" R ";
				}
				
				if (dynamic_cast<knightType*>(board[i][j])){
					std::cout <<" K ";
				}
				std::cout<<RESET;
			}	
			else if(board[i][j]->getPlayerType() == false){
				
				
				if (dynamic_cast<bishopType*>(board[i][j])){
					std::cout <<" B ";
				}
				
				if (dynamic_cast<queenType*>(board[i][j])){
					std::cout <<" Q ";
				}
				
				if (dynamic_cast<rookType*>(board[i][j])){
					std::cout <<" R ";
				}
				
				if (dynamic_cast<knightType*>(board[i][j])){
					std::cout <<" K ";
				}
			}
		}
		std::cout<<'\n';
	}
}


void clearBoard(chessPiece *** board)
{
	for(int i=0;i<7;i++){
		for (int j = 0; j<7;j++){
			if(board[i][j]!=nullptr){
			delete board[i][j];
			board[i][j] = nullptr;
			}
		}
	}
}