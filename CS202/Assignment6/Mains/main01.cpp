#include <iostream>
#include "polynomial.h"

int main()
{
	int p2[] = {-6, 2, 0, 0, 5};
	int p1[] = {-5, 2, 0, -2};

	polynomial poly1(p1, 3);
	polynomial poly2(p2, 4);
	polynomial result;

	result = poly1 * poly2;
	std::cout<<"degree in main: ";
	result.print();
	std::cout << "\nresult = " << result << "\n";


	return 0;
}