#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int TEAM_SIZE = 9; //Constant of how many players are on a team

//Enumeration class for position a Player plays. Make sure you are compiling with C++ 11 or higher for this to work
enum class Position
{ CATCHER, PITCHER, FIRST, SECOND, SHORT, THIRD, RIGHT, CENTER, LEFT };
const string positionNames[TEAM_SIZE] = {"C", "P", "1B", "2B", "SH", "3B", "RF", "CF", "LF"};

//Player class for an individual baseball player
class Player
{
	static int playerCount;

	string name; //Name of this player
	int number; //Player's number on their jersey
	Position position; //Position the Player plays, represented with Position enum

public:
	string toString();

	static string getPositionString(Position pos);
	static int getPlayerCount() { return playerCount; }

	Player() { playerCount++; }
	Player(string name, int number, Position position);
	//No need for a destructor, Player has no pointers to dynamically allocated memory
};

//You can use this optional "PlayerRef" definition in place of Player* if it makes the coding more comfortable.
//Note that the roster array below is an array of Player*s, or in other words, an array where the contents
//are references to Players (So if I wanted to change the declaration in the Team body:)
//Player* roster[TEAM_SIZE]
//   becomes
//PlayerRef roster[TEAM_SIZE]
//Whether you use this in the cpp and h file or not will not affect the CodeGrade compilation
#define PlayerRef Player*

//Team class for a team of Players. A single team will always have nine players
class Team
{
	static int teamCount; //Total number of teams made

	string teamName; //Name of the team
	Player* roster[TEAM_SIZE]; //Roster of 9 Players on the team

public:
	void printTeam();
	static int getTeamCount() { return teamCount; }

	Team() { teamCount++; } //Unused default constructor
	Team(ifstream& file);
	~Team();
};

#endif