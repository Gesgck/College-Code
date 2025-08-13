/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#5
Description: knight imp.
Input: move.
Output: move.
*/
#include "knightType.h"
#include <iostream>

knightType::knightType(bool color):chessPiece(color){}
	
bool knightType::move(char startRow, int startCol, char endRow,
 int endCol, chessPiece*** board)
{

	if(board[endRow-'A'][endCol] != nullptr&&board[endRow-'A'][endCol]->getPlayerType()
    == board[startRow-'A'][startCol]->getPlayerType()){
        std::cout <<"Invalid move!\n";
        return false;
    }

    bool move = false;
    if((endCol == startCol+1&&(endRow-'A') == (startRow-'A')+2)||
     (endCol == startCol+2&&(endRow-'A') == (startRow-'A')+1)||
     (endCol == startCol-1&&(endRow-'A') == (startRow-'A')+2)||
     (endCol == startCol-2&&(endRow-'A') == (startRow-'A')+1)||
     (endCol == startCol+1&&(endRow-'A') == (startRow-'A')-2)||
     (endCol == startCol+2&&(endRow-'A') == (startRow-'A')-1)||
     (endCol == startCol-1&&(endRow-'A') == (startRow-'A')-2)||
     (endCol == startCol-2&&(endRow-'A') == (startRow-'A')-1)
     ){
        move = true;
     }

     if (move!=true){
        std::cout <<"Invalid move!\n";
        return false;
     }

    if(board[endRow-'A'][endCol] == nullptr){
        board[endRow-'A'][endCol] = board[startRow-'A'][startCol];
    }
    else{
        delete board[endRow-'A'][endCol];
        board[endRow-'A'][endCol] = board[startRow-'A'][startCol];
    }
    board[startRow-'A'][startCol] = nullptr;
    return true;
}


knightType::~knightType()
{
	std::cout <<"Knight taken\n";
}
