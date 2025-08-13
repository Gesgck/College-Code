/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#5
Description: queen imp.
Input: move.
Output: move.
*/
#include "queenType.h"
#include <iostream>

queenType::queenType(bool color):chessPiece(color){}
	
bool queenType::move(char startRow, int startCol, char endRow,
 int endCol, chessPiece*** board)
{

	if(board[endRow-'A'][endCol] != nullptr&&board[endRow-'A'][endCol]->getPlayerType()
    == board[startRow-'A'][startCol]->getPlayerType()){
        std::cout <<"Invalid move!\n";
    }

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

    //checks for other pieces in the way
    if(startRow==endRow){
        if(startCol < endCol){
            for(int i = startCol+1; i < endCol; i++){
                if(board[startRow-'A'][i]!=nullptr){
                    std::cout<<"Invalid move!\n";
                    return false;
                }
            }
        }
        if(startCol > endCol){
            for(int i = startCol-1; i > endCol; i--){
                if(board[startRow-'A'][i]!=nullptr){
                    std::cout<<"Invalid move!\n";
                    return false;
                }
            }
        }
        move = true;
    }
    //checks for other pieces in the way
    if(startCol==endCol){
        if(startRow-'A' > endRow-'A'){
            for(int i = (startRow-'A')+1; i < (endRow-'A'); i++){
                if(board[i][startCol]!=nullptr){
                    std::cout<<"Invalid move!\n";
                    return false;
                }
            }
        }
        if(startRow-'A' < endRow-'A'){
            for(int i = (startRow-'A')-1; i > (endRow-'A'); i--){
                if(board[i][startCol]!=nullptr){
                    std::cout<<"Invalid move!\n";
                    return false;
                }
            }
        }
        move = true;
    }

    if(move != true){
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

queenType::~queenType()
{
	std::cout <<"Queen taken\n";
}
