#include"lander.h"
#include"priorityQueue.h"
#include<iostream>
#include<fstream>


int main(){
    std::string fileName;
    std::ifstream infile;

    do{
        std::cout<<"Enter input file: ";                                //ask for the input file
        std::cin>>fileName;

        infile.open(fileName);                                          //check input
        if(!infile){
            std::cout<<"Error, File Not Found\n";
            std::cin.clear();
            std::cin.ignore(1000,'\n');
        }
    }while(!infile);

    std::string readFile, sub1, sub2, sub3, sub4, sub5, sub6;
    lander *landitem;
    priorityQ<lander> queue;

    while(!infile.eof()){
        getline(infile,readFile);
        if(readFile.length() != 0){
            sub1 = readFile.substr(0,readFile.find(" "));                //get mass
            readFile = readFile.substr(readFile.find(" ")+1);
            sub2 = readFile.substr(0,readFile.find(" "));                //get max_thrust
            readFile = readFile.substr(readFile.find(" ")+1);
            sub3 = readFile.substr(0,readFile.find(" "));                //get max_fuel
            readFile = readFile.substr(readFile.find(" ")+1);
            sub4 = readFile.substr(0,readFile.find(" "));                //get alt
            readFile = readFile.substr(readFile.find(" ")+1);
            sub5 = readFile.substr(0,readFile.find(" "));                //get fuel
            sub6 = readFile.substr(readFile.find(" ")+1);                //get id
            landitem = new lander(std::stod(sub1),std::stod(sub2),std::stod(sub3),  //construct new lander object
            std::stod(sub4),std::stod(sub5),std::stoi(sub6));
            queue.insert(*landitem);
            delete landitem;
        }
    }
    infile.close();
    
    
    do{
        std::cout<<"\nEnter Simulation File:";                          //ask for the sim file
        std::cin>>fileName;

        infile.open(fileName);                                          //check input
        if(!infile){
            std::cout<<"Error, File Not Found\n";
            std::cin.clear();
            std::cin.ignore(1000,'\n');
        }
    }while(!infile);
    std::cout<<std::endl;

    while(!infile.eof()){
        if(queue.isEmpty()){
            break;
        }
        getline(infile,readFile);
        if(readFile.length() != 0){
            try{
                stod(readFile);                                         // check for valid input
            }
            catch(...){
                std::cout<<"Error, Invalid Input\n";
                continue;
            }

            std::cout<<"\nRocket "<<queue.getHighestPriority().get_id() <<std::endl             // print rocket status
            <<"Fuel: " <<queue.getHighestPriority().get_fuel_amount() <<std::endl
            <<"Altitude: " <<queue.getHighestPriority().get_altitude() <<std::endl
            <<"Velocity: " <<queue.getHighestPriority().get_velocity() <<std::endl;


            // queue.getHighestPriority().change_flow_rate(stod(readFile));                        // change flow rate
            // queue.getHighestPriority().simulate();                                              // simulate

            lander landManip = queue.getHighestPriority();
            landManip.change_flow_rate(stod(readFile));
            landManip.simulate();
            queue.deleteHighestPriority();

            if(queue.getHighestPriority().get_status() == 'c'){                                 // if it crashed
                std::cout<<"\nRocket ID: " <<queue.getHighestPriority().get_id()
                <<" has crashed :( At least nobody was on board\n";
            }
            else if(queue.getHighestPriority().get_status() == 'l'){                            // if it landed
                std::cout<<"\nRocket ID: " <<queue.getHighestPriority().get_id()
                <<" has landed\n";
            }
            else                                                                                // if its still airborn
                queue.insert(landManip);                                                         // bubble it down
        }
    }
    infile.close();

    if(!queue.isEmpty()){
        std::cout<<"\nThere are landers still trying to land...\n";
        while(!queue.isEmpty()){
            std::cout<<"Lander ID: " <<queue.getHighestPriority().get_id()
            <<" Altitude: " <<queue.getHighestPriority().get_altitude()
            <<" mission aborted\n";
            queue.deleteHighestPriority();
        }
    }

    return 0;
}