#include<iostream>
#include<fstream>

template < class Type >
struct binTreeNode{
    Type item;
    binTreeNode <Type> *left;
    binTreeNode <Type> *right;
};

template <class Type>
void readLISP(binTreeNode<Type> *r, std::ifstream& infile){
    binTreeNode<int> *temp;
    char reading;
    int tmp = 0;

    //left node
    infile>>reading;
    
    if(reading == ')'){                             //if the node is empty
        r->left = nullptr;
    }
    else{
        while(reading != '('){
            if(reading == ' '){
                    infile>>reading;
                    
                    continue;
                }
            reading -= '0';                             //subtract ascii 0
            tmp += reading;                             //add it to tmp
            infile>>reading;
            
            if(reading >= '0' && reading <= '9')          //if the next character is a digit mul tmp by 10
                tmp = tmp*10;
        }
        r->left = new binTreeNode<int>;
        r->left->item = tmp;
        readLISP(r->left, infile);
    }


    //right node
    tmp = 0;
    infile>>reading;
    
    while(reading != '('){                          //read until the next parenthesis
        infile>>reading;
        
    }

    infile>>reading;
    if(reading == ')'){                             //if the node is empty
        r->right = nullptr;
    }
    else{
        while(reading != '('){
            if(reading == ' '){
                    infile>>reading;
                    continue;
                }
            reading -= '0';                             //subtract ascii 0
            tmp += reading;                             //add it to tmp
            infile>>reading;
            if(reading >= '0' && reading <= '9')          //if the next character is a digit mul tmp by 10
                tmp = tmp*10;
        }
        r->right = new binTreeNode<int>;
        r->right->item = tmp;
        readLISP(r->right, infile);
    }
    return;
}


template <class Type>
bool evaluate(binTreeNode<Type> *r, int runningSum, int targetSum, myStack<Type>& path){
    runningSum += r->item;
    if(r->left == nullptr && r->right == nullptr){                      //leaf compare
        if(runningSum == targetSum){
            path.push(r->item);
            return true;
        }
    }
    if(r->left != nullptr){                                          //if not a leaf evaluate left nodes
        if(evaluate(r->left, runningSum, targetSum, path)){
            path.push(r->item);
            return true;
        }
    }
    if(r->right != nullptr){
        if(evaluate(r->right, runningSum, targetSum, path)){           // if that doesnt find it then evaluate right nodes
        path.push(r->item);
        return true;
        }
    }
    return false;
}


template <class Type>
void destroyTree(binTreeNode<Type> *r){
    if(r->left != nullptr)                                              //post order deletion of nodes
        destroyTree(r->left);
    if(r->right != nullptr)
        destroyTree(r->right);
    delete r;
    return;
}