#include <iostream>

using namespace std;

bool isPalindrome(string str, int leftLetter, int rightLetter);

int main () {

    string in;
    
    cout <<"Enter a string: ";
    cin >>in;
    cout <<endl;
    for(int i = 0; i < in.size();i++)
        in[i] = tolower(in[i]);
    if(isPalindrome(in,0,in.size()-1))
        cout<<in <<" is a Palindrome";
    else
        cout<<in <<" is not a Palindrome";

return 0;

}

bool isPalindrome(string str, int leftLetter, int rightLetter){

    if (leftLetter == rightLetter)
        return true;
    if(str.substr(leftLetter,1) != str.substr(rightLetter,1))
        return false;
    else
        return(isPalindrome(str,++leftLetter,--rightLetter));
}
