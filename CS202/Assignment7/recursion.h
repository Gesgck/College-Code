/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#7
Description: recursive functions.
Input: stuff.
Output: different stuff.
*/
#ifndef RECURSION_H
#define RECURSION_H

#include <iostream>
#include <string>

using namespace std;

const int WIDTH = 4;
const int HEIGHT = 5;

//Doll class for the findCenter function. This represents a Matryoshka doll with another Doll inside it
//A doll containing no other Dolls will have an innerDoll of nullptr
class Doll
{
	string name;
	unsigned int id;
	static unsigned int count;
	Doll* innerDoll;
public:
	Doll* getInnerDoll() const { return innerDoll; }
	void printDoll() { cout << "Doll: " << id << " " << name << endl; }

	Doll(string name, Doll* inside) { this->name = name; innerDoll = inside; id = count; count++; }
};

//---------------------------- Recursive function implementations ----------------------------

/* Description */
int power(const int& base, int pow)
{
	if(pow == 0)
		return 1;//x^0 = 1
	static int ans = base;//static int to keep value after recursion
	while(pow > 1){
		ans = ans * base;
		return power(base,--pow);
	}
	return ans;//when pow = 1 return ans

}

/* Description */
int findBiggestNumber(int arr[], int index)
{
	if(index == 0)
		return arr[0];//if index is only 1 term then return it
	for(int i = 0; i < index-1; i++)
		if(arr[i]>arr[index]){
			return findBiggestNumber(arr,index-1);
		}
	return arr[index];//if there are no bigger numbers left of index
}

/* Description */
void findTheX(char grid[HEIGHT][WIDTH], const int& x, const int& y)
{
	if(grid[x][y] == 'X')
		cout<<"Found the X at (" <<y <<", " <<x <<")\n";
	grid[x][y] = 'O';//makes current square 'O'
	if(grid[x+1][y] != 'O' && x+1 <= HEIGHT)//move down
		return findTheX(grid,x+1,y);
	if(grid[x-1][y] != 'O' && x-1 >= 0)//move up
		return findTheX(grid,x-1,y);
	if(grid[x][y-1] != 'O' && y-1 >= 0)//move left
		return findTheX(grid,x,y-1);
	if(grid[x][y+1] != 'O' && y+1 <= WIDTH)//move right
		return findTheX(grid,x,y+1);
}

/* Description */
void findCenter(Doll* doll)
{
	doll->printDoll();
	if(doll->getInnerDoll() == nullptr)//base case if on final doll
		return;
	return findCenter(doll->getInnerDoll());//next doll

}

#endif