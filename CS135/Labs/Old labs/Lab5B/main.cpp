/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_# 5B
Description: reads files and adds numbers.
Input: files.
Output: numbers in files added.
*/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{

    // stuff is delcared
    ifstream iFile;
    string file;
    int a = 0;
    int b = 0;
    // asks for file name
    do
    {
        cout << "Enter file name\n**";
        cin >> file;
        cout << endl;
        iFile.open(file);
        // checks if file name is real
        if (!iFile.is_open())
        {
            cout << "Error: Invalid file name\n";
        }
        else
        {
            a = 1;
        }
    } while (a == 0);

    // outputs the numbers
    int c1 = 0;
    int c2 = 0;
    while (!iFile.eof())
    {
        iFile >> c1 >> c2;

        if (iFile.fail())
        {
            iFile.clear();
            iFile.ignore(100, '\n');
            cout << "Error in line\n";
        }
        else
        {
            cout << c1 << " + " << c2 << " = " << c1 + c2 << endl;
            b += c1 + c2;
        }
    }
    // outputs running total and closes the file
    cout << endl
         << "Running total = " << b;
    iFile.close();

    return 0;
}
