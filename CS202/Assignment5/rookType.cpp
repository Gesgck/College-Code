/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#5
Description: rook imp.
Input: move.
Output: move.
*/
#include "rookType.h"
#include <iostream>

rookType::rookType(bool color):chessPiece(color){}
	
bool rookType::move(char startRow, int startCol, char endRow, 
	int endCol, chessPiece*** board)
{
    if(board[endRow-'A'][endCol] != nullptr&&board[endRow-'A'][endCol]->getPlayerType()
    == board[startRow-'A'][startCol]->getPlayerType()){
        std::cout <<"Invalid move!\n";
        return false;
    }
    if(startRow!=endRow&&startCol!=endCol){
        std::cout<<"Invalid move!\n";
        return false;
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
    }
    //if end pos is empty
    if(board[endRow-'A'][endCol] == nullptr){
        board[endRow-'A'][endCol] = board[startRow-'A'][startCol];
    }
    //if it is not
    else{
        delete board[endRow-'A'][endCol];
        board[endRow-'A'][endCol] = board[startRow-'A'][startCol];
    }
    board[startRow-'A'][startCol] = nullptr;
    return true;
}


rookType::~rookType()
{
	std::cout <<"Rook taken\n";
}
