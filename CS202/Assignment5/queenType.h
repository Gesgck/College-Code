#include "chessPiece.h"

class queenType : public chessPiece
{
public:
	queenType(bool);
	bool move(char, int, char, int, chessPiece***);
	~queenType();
};