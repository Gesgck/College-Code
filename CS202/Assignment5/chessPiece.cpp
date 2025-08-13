/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#5
Description: base class imp.
Input: color.
Output: piece.
*/
#include <iostream>
#include "chessPiece.h"

chessPiece::chessPiece(bool color):color(color){}
	
bool chessPiece::getPlayerType() const
{
	return color;
}

chessPiece::~chessPiece()
{
	std::cout <<"Piece removed from board.\n";
}
