#include<fstream>
#include<iostream>
#include<iomanip>
#include<unordered_map>
#include<vector>

int main(){

    std::string fileName;
    std::ifstream infile;

    do{
        std::cout<<"Enter students file: ";                             //ask for the names file
        std::cin>>fileName;

        infile.open(fileName);                                          //check input
        if(!infile){
            std::cout<<"Error, File Not Found\n";
            continue;
        }
    }while(!infile);

    std::cout<<std::endl;

    std::vector<std::string> names;                                     //student names vector
    std::string readFile;

    while(!infile.eof()){                                               //read names into vector
        getline(infile, readFile);
        if(readFile.length() != 0){
            names.push_back(readFile);
        }
    }
    infile.close();
    
    std::unordered_map<std::string,int> students;
    
    for (auto it = names.begin(); it != names.end(); ++it)
        students[*it] = 0;                                              //initialize each student to 0 assignments
    


    do{
        std::cout<<"Enter assignments file: ";                          //ask for the assignment file
        std::cin>>fileName;

        infile.open(fileName);                                          //check input
        if(!infile){
            std::cout<<"Error, File Not Found\n";
            continue;
        }
    }while(!infile);

    std::cout<<std::endl;

    std::unordered_map<std::string,int> assignments;
    int x = 0;
    std::string name;
    int stringFind;

    while(!infile.eof()){                                               //read assignments into hash table
        getline(infile, readFile);
        if(readFile.length() != 0){                                     
            if(assignments.count(readFile) == 0){                       //if the assignment does not already exist in the hash table
                assignments[readFile];                                  //put the assingment into the hastable
                stringFind = readFile.find("_");                        //find the name of owner of the assignment
                readFile = readFile.substr(0,stringFind);               //crop out everything else
                x = students[readFile];                                 //find how many assignments they have now
                x++;                                                    //iterate the number of assignments the owner has
                students[readFile] = x;
            }
        }
    }
    infile.close();




    std::cout<<"\nNAME              MISSING ASSIGNMENTS\n";               //print header

    for (auto it = names.begin(); it != names.end(); ++it){             //print missing assignments
        x = students[*it];
        x = 9 - x;                                                      //find # of missing assignments
        std::cout<<std::setw(12) <<std::left <<*it 
        <<"      " <<x <<std::endl;
    }


    return 0;
}