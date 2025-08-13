/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#4
Description: imp file for teams.h.
Input: team data.
Output: team data.
*/
#include "team.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//Static intializers for counts (done outside class bodies)
int Player::playerCount = 0;
int Team::teamCount = 0;

/*----------------- Player function implementations -----------------*/

/* Returns all of the Player's variable members in a formatted string for displaying */
string Player::toString()
{
	return getPositionString(position) + 
		(position == Position::PITCHER || position == Position::CATCHER ? "  " : " ") +
		to_string(number) + (number < 10 ? " " : "") + " : " + name;
}

/* Returns the string corresponding to the given postion */
string Player::getPositionString(Position pos)
{
	return positionNames[(int)pos];
}

/**/
Player::Player(string name, int number, Position position)
{
	this->name = name;
	this->number = number;
	this->position = position;
	playerCount++;
	//Set the Player's member variables to the corresponding parameters.
}


/*----------------- Team function implementations -----------------*/
/* Prints the team's name and then all of the Players */
void Team::printTeam()
{
	//First print the team's name and then all of the players
	cout << "---------- " << teamName << " ----------" << endl;
	//Print all of the players on the team's roster to cout by getting each Player as a string
	for (int i = 0; i < TEAM_SIZE; i++)
		cout << roster[i]->toString() << endl;
	cout << endl;
}

/**/
Team::Team(ifstream& file)
{
	//Reads a team from a given file. The file will always be formatted such that 
	//the first line contains the team name. The next nine lines will contain the nine players, with the number first
	//Followed by their name. The order of players in files is always:
	//Catcher, Pitcher, First, Second, Shortstop, Third, Right Field, Center Field, Left Field

	//HINT: When reading and creating the players, you can either make nine Player objects in order with the
	//positions listed above, or use a for loop and cast the enumeration type.

	//Start by reading the name, then read each player by using the given variables and then constructing a new
	//Player object to be added to the roster array. The first Player is given for you as an example

	//Finally increment the count of teams

	string name;
	int number;
	//Read team name first (Remember, the name can have spaces. Try to avoid using >>)
	
	//TODO

	//Get the catcher (You can replace this if you know how to do the for loop method)
	//You can also change this to a separate function if you prefer to encourage code re-use

	//TODO
	getline(file,teamName);
	teamCount++;

	file >> number; //Read the players's number
	getline(file, name); //Read the players's name
	//Set the person on the roster to be the player with the info we read
	roster[0] = new Player(name, number,Position::CATCHER);
	file >> number; //Read the players's number
	getline(file, name); //Read the players's name
	roster[1] = new Player(name, number,Position::PITCHER);
	file >> number; //Read the players's number
	getline(file, name); //Read the players's name
	roster[2] = new Player(name, number,Position::FIRST);
	file >> number; //Read the players's number
	getline(file, name); //Read the players's name
	roster[3] = new Player(name, number,Position::SECOND);
	file >> number; //Read the players's number
	getline(file, name); //Read the players's name
	roster[4] = new Player(name, number,Position::SHORT);
	file >> number; //Read the players's number
	getline(file, name); //Read the players's name
	roster[5] = new Player(name, number,Position::THIRD);
	file >> number; //Read the players's number
	getline(file, name); //Read the players's name
	roster[6] = new Player(name, number,Position::RIGHT);
	file >> number; //Read the players's number
	getline(file, name); //Read the players's name
	roster[7] = new Player(name, number,Position::CENTER);
	file >> number; //Read the players's number
	getline(file, name); //Read the players's name
	roster[8] = new Player(name, number,Position::LEFT);
	
	
	
}

/**/
Team::~Team()
{
	//Go through and deallocate all of the Players on the Team
	//Since the roster array itself is static, there is no need to delete the array, just the stuff in it
	//This should be about 2 lines of code
	for(int i=0; i<9;i++){
		delete roster[i];
	}
}