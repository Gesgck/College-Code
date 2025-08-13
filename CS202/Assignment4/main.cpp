#include "team.h"
#include "league.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

//Function prototypes
void openFile(ifstream& infile, string filename);
void printInfo();

int main()
{
	//Print the prompt for tests
	int choice;
	cout << "Which test should be done?" << endl;
	cout << "(1) Test one team" << endl;
	cout << "(2) Test four teams" << endl;
	cout << "(3) Test five teams [league dynamically resizes]" << endl;

	//Read the choice from the user
	cin >> choice;
	while (choice < 1 || choice > 3)
	{
		cout << "Please pick a number between 1 and 3 inclusive" << endl;
		cin >> choice;
	}

	//Handle the choice
	League league;
	Team* team;
	ifstream infile;
	openFile(infile, "americans.txt");

	switch (choice)
	{
		case 1:
			team = new Team(infile); //Read the default team
			team->printTeam(); //Print it
			delete team; //Delete it
			break;
		case 2:
			league.addTeam(new Team(infile));
			infile.close();
			openFile(infile, "serpents.txt");
			league.addTeam(new Team(infile));
			infile.close();
			openFile(infile, "jaguars.txt");
			league.addTeam(new Team(infile));
			infile.close();
			openFile(infile, "dragons.txt");
			league.addTeam(new Team(infile));
			infile.close();
			league.printTeams();
			printInfo();
			break;
		case 3:
			league.addTeam(new Team(infile));
			infile.close();
			openFile(infile, "serpents.txt");
			league.addTeam(new Team(infile));
			infile.close();
			openFile(infile, "jaguars.txt");
			league.addTeam(new Team(infile));
			infile.close();
			openFile(infile, "dragons.txt");
			league.addTeam(new Team(infile));
			infile.close();
			openFile(infile, "americans.txt");
			league.addTeam(new Team(infile));
			infile.close();
			league.printTeams();
			printInfo();
			break;
		default:
			cout << "Invalid choice. Terminating program" << endl;
			return 1;
	}

	return 0; //Program ends; league gets deleted right after when it goes out of scope
}

void openFile(ifstream& infile, string filename)
{
	infile.open(filename);
	if (infile.good()) return;
	
	//If the file did not open correctly, kill the program with an error message
	cout << "Could not open " << filename << endl << "Is it in the same directory as this program?" << endl;
	exit(1);
}

void printInfo()
{
	cout << "There were a total of " << Team::getTeamCount() << " teams and " << 
	Player::getPlayerCount() << " players" << endl;

}