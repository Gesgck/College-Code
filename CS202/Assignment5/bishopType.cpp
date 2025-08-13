/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#5
Description: bishop imp.
Input: move.
Output: move.
*/
#include "bishopType.h"
#include <cmath>
#include <iostream>

bishopType::bishopType(bool color):chessPiece(color){}
	
bool bishopType::move(char startRow, int startCol, char endRow, 
	int endCol, chessPiece*** board)
{
	if(board[endRow-'A'][endCol] != nullptr&&
    board[endRow-'A'][endCol]->getPlayerType()
    == board[startRow-'A'][startCol]->getPlayerType()){
        std::cout <<"Invalid move!\n";
        return false;
    }

    //move checks
    bool move = false;
    if((endRow-'A' == (startRow-'A')+1) && endCol == startCol + 1){
        move = true;
    }
    if((endRow-'A' == (startRow-'A')+2) && endCol == startCol + 2){
        move = true;
    }
    if((endRow-'A' == (startRow-'A')+3) && endCol == startCol + 3){
        move = true;
    }
    if((endRow-'A' == (startRow-'A')+4) && endCol == startCol + 4){
        move = true;
    }
    if((endRow-'A' == (startRow-'A')+5) && endCol == startCol + 5){
        move = true;
    }
    if((endRow-'A' == (startRow-'A')+6) && endCol == startCol + 6){
        move = true;
    }
    if((endRow-'A' == (startRow-'A')+7) && endCol == startCol + 7){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') - 1) && endCol == startCol - 1){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') - 2) && endCol == startCol - 2){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') - 3) && endCol == startCol - 3){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') - 4) && endCol == startCol - 4){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') - 5) && endCol == startCol - 5){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') - 6) && endCol == startCol - 6){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') - 7) && endCol == startCol - 7){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') + 1) && endCol == startCol - 1){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') + 2) && endCol == startCol - 2){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') + 3) && endCol == startCol - 3){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') + 4) && endCol == startCol - 4){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') + 5) && endCol == startCol - 5){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') + 6) && endCol == startCol - 6){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') + 7) && endCol == startCol - 7){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') - 1) && endCol == startCol + 1){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') - 2) && endCol == startCol + 2){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') - 3) && endCol == startCol + 3){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') - 4) && endCol == startCol + 4){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') - 5) && endCol == startCol + 5){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') - 6) && endCol == startCol + 6){
        move = true;
    }
    if((endRow-'A' == (startRow-'A') - 7) && endCol == startCol + 7){
        move = true;
    }
    if(move != true){
        std::cout <<"Invalid move!\n";
        return false;
    }

    //checks for obstacles
    int col = startCol;
    int row = startRow - 'A';
    if(startRow-'A' > endRow-'A' && startCol > endCol){
        while(col>endCol){
            col--;
            row--;
            if(board[col][row]!=nullptr){
                std::cout <<"Invalid move!\n";
                return false;
            }
        }
    }
    if(startRow-'A' < endRow-'A' && startCol > endCol){
        while(col>endCol){
            col--;
            row++;
            if(board[col][row]!=nullptr){
                std::cout <<"Invalid move!\n";
                return false;
            }
        }
    }
    if(startRow-'A' > endRow-'A' && startCol < endCol){
        while(col<endCol){
            col++;
            row--;
            if(board[col][row]!=nullptr){
                std::cout <<"Invalid move!\n";
                return false;
            }
        }
    }
    if(startRow-'A' < endRow-'A' && startCol < endCol){
        while(col<endCol){
            col++;
            row++;
            if(board[col][row]!=nullptr){
                std::cout <<"Invalid move!\n";
                return false;
            }
        }

    }

    //moves the piece
    if(board[endRow-'A'][endCol] == nullptr){
        board[endRow-'A'][endCol] = board[startRow-'A'][startCol];
    }
    else{
        delete board[endRow-'A'][endCol];
        board[endRow-'A'][endCol] = nullptr;
        board[endRow-'A'][endCol] = board[startRow-'A'][startCol];
    }
    board[startRow-'A'][startCol] = nullptr;
    return true;
}


bishopType::~bishopType()
{
	std::cout <<"Bishop taken\n";
}
