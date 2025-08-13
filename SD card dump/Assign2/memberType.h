/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1007 , ASSIGNMENT_#2
Description: Inputs and outputs data to and from files.
Input: file.
Output: file.
*/
#ifndef H_mrmberType
#define H_mrmberType

#include <iostream>
#include <string>
using namespace std;

/**
 * @brief
 *
 */
class memberType
{

private:
    string memberID;
    string firstName;
    string lastName;

    int booksPurchased;
    double amountSpent;
    double booksDiscount; //if books purchased>=4 set it to 4 
                        //else set the value to 0
    int lengthOfMembership; //int variable to store length of membership

public:
    memberType(); //Default constructor
    void setMemberInfo(string ID, string fName, string lName,
                       int bPurchased, double amount, double discount, int membership);
    void setMemberID(string);
    void setName(string, string);
    bool checkID(string);
    bool checkBookCount(int booksCount);
    bool checkAmountSpent(int booksCount, double amountSpent);
    bool checkMembership(int membership);
    bool checkDiscount(int discount);

    string getID() const; 
    string getFirstName() const;
    string getLastName() const;
    int getBookCount() const;
    double getPurchaseBill() const;
    int getLenghtOfMembership() const;
    double getDiscount() const;
    double getDiscountAmount() const;
    double getFinalPrice() const;

    
    ~memberType(); //Destructor
};

#endif // H_mrmberType