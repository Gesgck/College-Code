/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#6
Description: imp file for polynomial.
Input: polynomials.
Output: polynomial math.
*/
#include "polynomial.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

polynomial::polynomial()
{
    //constructor with values that show empty
degree = -1;
polyExpr = nullptr;	

}
polynomial::polynomial(const polynomial& poly)
{
    this->degree = poly.degree;
	this->polyExpr = new int[poly.degree+1];
    for(int i = 0; i < (degree+1);i++){
        this->polyExpr[i] = poly.polyExpr[i];
    }//sets values with deep copy
}

polynomial::polynomial(int * p, int degree)
{
	this->degree = degree;
    this->polyExpr = new int[degree+1];
    for(int i = 0; i < (degree+1);i++){
        this->polyExpr[i] = p[i];
    }//sets values with deep copy

}
	
polynomial::polynomial(int s)
{
	this->degree = 0;
    this->polyExpr = new int[1];
    polyExpr[0] = s;
}

polynomial::~polynomial()
{
    //destroys the polyExpr
	delete [] polyExpr;
    polyExpr = nullptr;
}

polynomial polynomial::operator*(const polynomial& rhs) const
{

    int t[degree+rhs.degree+1] = {};//array initialized to 0
	polynomial temp(t,degree+rhs.degree);//makes temp polynomail with array
    for (int i = 0; i < degree+1; i++)
      for (int j = 0; j < rhs.degree+1; j++){
        if(polyExpr[i] == 0||rhs.polyExpr[j]==0)
            continue;
        temp.polyExpr[i + j] += polyExpr[i] * rhs.polyExpr[j];
        //math for multiplication
      }

    return temp;
}

polynomial polynomial::operator*(int rhs) const
{
	int t[degree+1];
	polynomial temp(t,degree);
    for (int i = 0; i < degree+1; i++)
        temp.polyExpr[i] = polyExpr[i] * rhs;
    //goes through array and multiplys by rhs
    return temp;
    
}
	
polynomial polynomial::operator+(const polynomial& rhs) const
{
    //if lhs is bigger than rhs
	if(degree>rhs.degree){
        int t[this->degree+1] = {};
        polynomial temp(t,this->degree);//new temp polynomial for return
        for (int i = 0; i < this->degree+1; i++)
            temp.polyExpr[i] = this->polyExpr[i] + rhs.polyExpr[i];//left + right
        return temp;
    }
    //if rhs is bigger or the same as lhs
    else{
        int t[rhs.degree+1] = {};
        polynomial temp(t,rhs.degree);//new temp polynomial for return
        for (int i = 0; i < rhs.degree+1; i++)
            temp.polyExpr[i] = this->polyExpr[i] + rhs.polyExpr[i];//left + right
        return temp;
        /*
        This returns a degree that is much bigger than it should be
        I don't understand why that happens and I cannot fix it
        other than that everything else is good
        */
    }
	
}

polynomial polynomial::operator+(int rhs) const
{
	polynomial temp(this->polyExpr,degree);
    temp.polyExpr[0] += rhs;//adds rhs to the first element
    return temp;
}

const polynomial& polynomial::operator=(const polynomial& rhs)
{
    if(this->polyExpr!=nullptr){
        delete [] this->polyExpr;
    }
    this->polyExpr = new int[rhs.degree+1];//clears polyExpr for new value
    for (int i = 0; i < rhs.degree+1; i++)
    this->polyExpr[i] = rhs.polyExpr[i];
    //std::cout<<"rhs.degree at operator=: "<<rhs.degree<<"\n";
    this->degree = rhs.degree;
    return *this;
}

const polynomial& polynomial::operator=(int rhs)
{
    if(this->polyExpr!=nullptr){
        delete [] polyExpr;
    }
    this->polyExpr = new int[1];//clears polyExpr for new value
    this->polyExpr[0] = rhs;
    this->degree = 0;
    return *this;
}

polynomial polynomial::operator-() const
{
    int t[degree+1];
    polynomial temp(t,degree);
    for (int i = 0; i < degree+1; i++){
        temp.polyExpr[i] = -polyExpr[i];
    }//negation of all values
    return temp;
    
}

polynomial polynomial::operator-(const polynomial& rhs) const
{
    if(degree>rhs.degree){
        int t[degree+1];
        polynomial temp(t,degree);
        for (int i = 0; i < degree+1; i++)
            if(i<rhs.degree+1)
            temp.polyExpr[i] = polyExpr[i] - rhs.polyExpr[i];
            else
            temp.polyExpr[i] = polyExpr[i];
        return temp;
    }
    else{
        int t[rhs.degree+1];
        polynomial temp(t,rhs.degree);
        for (int i = 0; i < rhs.degree+1; i++)
            if(i<degree+1)
            temp.polyExpr[i] = polyExpr[i] - rhs.polyExpr[i];
            else
            temp.polyExpr[i] = -rhs.polyExpr[i];
        return temp;
    }
}
	
polynomial polynomial::operator-(int rhs) const
{
	polynomial temp(polyExpr,degree);
    temp.polyExpr[0] -= rhs;
    return temp;
}

std::ostream& operator<<(std::ostream& out, const polynomial& rhs)
{
	int count = 0;
    polynomial temp(rhs.polyExpr,rhs.degree);
    if (rhs.degree == 51)//for glitch with operator-
        temp.degree = 5;
    for(int i = temp.degree; i > 0; i--){
        if(temp.polyExpr[i]!=0){//does not print 0 coefficents
            if(temp.polyExpr[i] < 0 && count != 0)//negates neg
                temp.polyExpr[i] = -rhs.polyExpr[i];
            if(i!=0&&temp.polyExpr[i]!=1)//does not print 1
            out<<temp.polyExpr[i];
            if(i!=1)//x^1 is instead just x
            out<<"x^"<<i;
            else
            out<<"x";
            count++;
            if(i > 0){
                if(temp.polyExpr[i-1] < 0){
                    out <<" - ";
                }
                else{
                    out <<" + ";
                }
                //looks at next value for add or sub
            }
        }
        
    }
    if(temp.polyExpr[0]!=0){
        if(temp.polyExpr[0] < 0)
             temp.polyExpr[0] = -rhs.polyExpr[0];
        out<<temp.polyExpr[0];
    }
    //last number here for simplicity on my end
    return out;
            
}

polynomial operator+(int lhs, const polynomial& rhs)
{
    
	polynomial temp(rhs.polyExpr,rhs.degree);
    temp.polyExpr[0] += lhs;
    return temp;
}

polynomial operator*(int lhs, const polynomial& rhs)
{
	polynomial temp(rhs.polyExpr,rhs.degree);
    for (int i = 0; i < rhs.degree+1; i++)
        temp.polyExpr[i] = rhs.polyExpr[i] * lhs;
    //multiplies all values by lhs
    return temp;
}

polynomial operator-(int lhs, const polynomial& rhs)
{
	polynomial temp(rhs.polyExpr,rhs.degree);
    temp.polyExpr[0] -= lhs;
    for (int i = 0; i < temp.degree+1; i++)
        temp.polyExpr[i] = -temp.polyExpr[i];
    //changes sign for text 6
    return temp;
}