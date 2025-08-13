#pragma once

class chessPiece
{
public:
	chessPiece(bool);
	virtual bool move(char, int, char, int, chessPiece***) = 0;
	bool getPlayerType() const;
	virtual ~chessPiece();
private:
	bool color;
};