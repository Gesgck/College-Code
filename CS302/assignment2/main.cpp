#include"myStack.h"
#include"binaryTree.h"

int main(){

    std::string fileName;
    std::ifstream infile;
    binTreeNode<int> *tree;
    myStack<int> stack;
    char reading;
    int target, sum, tmp = 0;

    do{
        std::cout<<"Enter LISP file ( All those parenthesis ...): ";    //ask for the file
        std::cin>>fileName;

        infile.open(fileName);                                          //check input
        if(!infile){
            std::cout<<"Error, File Not Found\n";
            continue;
        }
    }while(!infile);
    
    //loop for input file
    while(!infile.eof()){
        target = 0;
        //get the target number
        infile>>reading;
        if(infile.eof())                                    //when reaching eof, break loop
            break;

        while(reading < '0' || reading > '9'){              //extra eof check
            infile>>reading;
            if(infile.eof())
                return 0;
    
        }


        while(reading != '('){                              //get the target number
            reading -= '0';                                 //sub ascii 0 from reading
            target += reading;                              //add that into target
            infile>>reading;
    
            if(reading >= '0' && reading <= '9')              //if the next char is a digit mul reading by 10
                target = target*10;
        }


        //get the root
        tmp = 0;
        while(reading != '('){                              //read until reaching a number
            infile>>reading;
        }
        infile>>reading;
        if(reading == ')'){                                  //if the node is empty
            std::cout<<"No such path exists , LISP is a pain anyway\n";
            continue;
        }

        if(reading >= '0' || reading <= '9'){               //while still reading numbers
            tree = new binTreeNode<int>;
            while(reading != '('){
                if(reading == ' '){                         //ignore any spaces
                    infile>>reading;
                    continue;
                }
                reading -= '0';                             //subtract ascii 0
                tmp += reading;                             //add it to tmp
                infile>>reading;
        
                if(reading > '0' && reading < '9')          //if the next character is a digit mul tmp by 10
                    tmp = tmp*10;
            }
            tree->item = tmp;
            readLISP(tree, infile);
        }


        if(evaluate(tree, sum, target, stack)){             //evaluate the tree
            std::cout<<"\nPath in tree exists\n";
            while(!stack.isEmpty()){                        //read the entire stack
                std::cout<<stack.top();
                stack.pop();
                if(!stack.isEmpty())                        //put " + " until the last number
                    std::cout<<" + ";
            }
            std::cout<<" = " <<target <<"\n\n";
        }
        else
            std::cout<<"No such path exists , LISP is a pain anyway\n";

        destroyTree(tree);                                  //destroy the tree for the next tree
        tree = nullptr;

    }
    

    return 0;
}