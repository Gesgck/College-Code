/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_#2
Description: Inputs and outputs data to and from files.
Input: file.
Output: file.
*/
#include "fileio.h"
#include "memberType.h"

using namespace std;

/**
 * @brief
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv)
{
    memberType storeMembers[500];
    unsigned int totalEntry = 0;

    if (argc != 2)
    {
        cerr << "Usage: ./main membersData.txt " << endl;
        return -1;
    }

    FileClass fd(argv[1]);

    totalEntry = getMembersDataFromFile(fd.inFile, storeMembers);

    writeMembersDataToFile(fd.outFile, storeMembers, totalEntry);

    return 0;
}