#ifndef LEAGUE_H
#define LEAGUE_H

#include "team.h"

//This is a definition to help with understanding the team array and is *optional* to use
//The teams array is a dynamic array of references to Team objects. So the two pointers in the League body
//refer to first the dynamic allocation and secondly to a reference to a team object. Another way this could be written
//with the def below is "TeamRef* teams", that is, a pointer to an array of Team references. Use TeamRef in place of
//Team* if the mix of two kinds of pointers is giving you trouble (See the accompanying video for an example)
#define TeamRef Team*

//Class representing a league with any number of Teams
class League {
	Team** teams; //Array of references to teams
	int count, size; //How many things are in the array and how big it is, respectively
	const int RESIZE_AMOUNT = 4; //Amount to resize the array by when it is resized

public:
	void printTeams();
	void printTeam(int t);//DELETE
	void addTeam(Team* new_team);

	League() { size = count = 0; teams = nullptr; }; //Default constructor
	League(int size) { this->size = size; count = 0; teams = new Team*[size]; } //Unused constructor, but nice to have
	~League();
};

#endif
