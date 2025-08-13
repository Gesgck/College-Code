#include<iostream>

int main(){

    int length = 0, width = 0;
    std::cout<<"Area and perimeter of a rectangle\nenter a length: ";
    std::cin>>length;
    std::cout<<"\nenter a width: ";
    std::cin>>width;
    std::cout<<std::endl;

    int area = length * width;
    int perimeter = (2*length) + (2*width);
    std::cout<<"Area = "<<area <<", Perimeter = " <<perimeter;

    return 0;
}