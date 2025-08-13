#include <iostream>
#include "polynomial.h"

int main()
{
	int p1[] = {-6, 2, 0, 0, 5};

	polynomial poly1(p1, 4);

	polynomial poly2;

	poly2 = poly1;

	std::cout << "poly2 = " << poly2 << "\n";

	return 0;
}

