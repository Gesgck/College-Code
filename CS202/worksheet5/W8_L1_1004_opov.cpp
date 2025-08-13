#include<iostream>
using namespace std;

class Rectangle{
private:
	int length;
	int width;
public:
	Rectangle(){length=0; width=0;}
	Rectangle(int length, int width){this->length=length; this->width=width;}
	void printData(){cout<<"Length: "<<length<<", Width: "<<width<<endl;}
	void changetoNegative(){this->length=-length; this->width=-width;}


	//operator overloading
	void operator-(); //To negate the member variable of that object
	Rectangle operator-(Rectangle ); //For subtraction
	//Rectangle (Rectangle const &); //copy constructor
	Rectangle & operator=(const Rectangle &); // Assignment operator

	//friend functions
	friend ostream & operator<<(ostream &, const Rectangle &);
}; 
void Rectangle::operator-(){
	cout<<"Negate operator overloading"<<endl;
	this->length=-length; this->width=-width;}
Rectangle Rectangle::operator-(Rectangle obj){
	cout<<"Subtraction operation overloading"<<endl;
	Rectangle temp;
	temp.length=length-obj.length;
	temp.width=this->width-obj.width;

	cout<<"Length: "<<temp.length<<", Width: "<<temp.width<<endl;
	return temp;
}

Rectangle & Rectangle::operator=(const Rectangle &obj){
	cout<<"Assignment operator overloading"<<endl;
	if(this!= &obj){
		length=obj.length;
		width=obj.width;

	}
	return *this;
}
int main(){
	// int x=50;
	// int y=25;

	// int z =x+y;

	// cout<<z<<endl;
	// x=-x;
	// cout<<x<<endl;

	Rectangle robj1(10, 20); //int x

	// robj1.changetoNegative();
	// robj1.printData();


	Rectangle robj2(15, 25); // int y
	// -robj2;
	// robj2.printData();

	Rectangle robj3; // int z
	robj3=robj2-robj1; //z=x+y

	//Rectangle robj4=robj1; // invoking copy constructor

	Rectangle robj5;
	robj5=robj2; //invoke assignment operator
	robj5.printData();

	cout<<robj5;

	cout<<endl;
	return 0;

}