/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, Worksheet_#5
Description: .
Input: .
Output: .
*/
#include <iostream>

using namespace std;

class Rectangle{
private:
	int length;
	int width;
    int *height;
public:
	Rectangle(){length=0; width=0; height = new int;}
	Rectangle(int length, int width, int h){this->length=length; this->width=width;height = new int;*(this->height)=h;}
	void printData(){cout<<"Length: "<<length<<", Width: "<<width<<", Height: "<<*height<<endl;}
    ~Rectangle(){cout <<"Destructor invoked\n";delete height;}


    //operator overloading
	Rectangle operator+(const Rectangle&);
    Rectangle operator*(Rectangle);
    bool operator==(const Rectangle);
    bool operator!=(const Rectangle);
    friend istream & operator>>(istream &,Rectangle);
    Rectangle operator++();
    Rectangle operator++(int);
};

Rectangle Rectangle::operator+(const Rectangle& te){
        Rectangle temp;
        temp.length = length + te.length;
        temp.width = width + te.width;
        temp.height = new int (*height + *(te.height));
        return temp;
    }
    Rectangle Rectangle::operator*(Rectangle te){
        Rectangle temp;
        temp.length = length * te.length;
        temp.width = width * te.width;
        temp.height = new int (*height * *(te.height));
        return temp;
    }
    bool Rectangle::operator==(const Rectangle te){
        return(length==te.length&&width==te.width&&*height==*(te.height));
    }
    bool Rectangle::operator!=(const Rectangle te){
        return(length!=te.length||width!=te.width||*height!=*(te.height));
    }
    istream & operator>>(istream &in,Rectangle te){
        cout <<"\nLength: ";
        in >>te.length;
        cout <<"\nWidth: ";
        in >>te.width;
        cout <<"\nHeight: ";
        in >>*(te.height);
        cout <<endl;
        return in;
    }
    Rectangle Rectangle::operator++(){
        Rectangle temp;
        temp.length = ++length;
        temp.width = ++width;
        *(temp.height) = ++*height;
        return temp;
    }
    Rectangle Rectangle::operator++(int){
        Rectangle temp;
        temp.length = length++;
        temp.width = width++;
        *(temp.height) = *height++;
        return temp;
    }

int main () {
    
    Rectangle r1(12,13,14);
    Rectangle r2(1,2,3);
    Rectangle r3;
    r3 = r1+r2;
    r3.printData();

    r3 = r1 * r2;
    r3.printData();

    if(r1 == r2){
        cout <<"Matches\n";
    }else if(r1 != r2){
        cout <<"Mismatch\n";
    }else{
        cout <<"N/A\n";
    }

    cin >>r1;
    r1.printData();

    r3.printData();
    r3++;
    r3.printData();
    ++r3;
    r3.printData();


    cout <<"Program Ends\n";

    return 0;

}
