#include "chessPiece.h"

class rookType : public chessPiece
{
public:
	rookType(bool);
	bool move(char, int, char, int, chessPiece***);
	~rookType();
};