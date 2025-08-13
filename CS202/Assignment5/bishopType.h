#include "chessPiece.h"

class bishopType : public chessPiece
{
public:
	bishopType(bool);
	bool move(char, int, char, int, chessPiece***);
	~bishopType();
};