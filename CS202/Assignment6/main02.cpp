#include <iostream>
#include "polynomial.h"

int main()
{
	int p1[] = {-6, 2, 0, 0, 5};
	int p2[] = {-5, -2, 4, 1, -2, 19};

	polynomial poly1(p1, 4);
	polynomial poly2(p2, 5);
	polynomial result;

	result = poly1 + poly2;
	// std::cout<<"degree in main: ";
	// result.print();
	// std::cout<<"\n";
	std::cout << "result in main = " << result << "\n";

	return 0;
}