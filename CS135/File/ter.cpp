/*
    Example of a header/body/call to a function
*/
#include <iostream>
using namespace std;

// Header (prototype)
int abs(int);

// Main function
int main() {
const int neg_10 = -10;
    // Call the function/save value
    int abs_10 = abs(neg_10);
    cout << "|-10| = " << abs_10 << endl;
    return 0;
}
// Body of the function
int abs(int num) {
    if (num >= 0) {
        return num;
    } else {
        return num * -1;
    }
}