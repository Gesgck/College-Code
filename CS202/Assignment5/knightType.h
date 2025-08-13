#include "chessPiece.h"

class knightType : public chessPiece
{
public:
	knightType(bool);
	bool move(char, int, char, int, chessPiece***);
	~knightType();
};