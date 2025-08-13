/*
Name: Alec Zheng, NSHE_ID_#2001982564, COURSE_SECTION 1004, ASSIGNMENT_#
Description: imp file for league.h.
Input: league data.
Output: league data.
*/
#include "league.h"

/*DESCRIPTION*/
void League::printTeams()
{
	//Go through all of the Teams in the teams array and print each one using their
	//print function

	//TODO
	for(int i = 0; i < Team::getTeamCount(); i++){
		teams[i]->printTeam();
	}
}


/**/
void League::addTeam(Team* new_team)
{
	//This should add the passed new_team to the end of the list of Teams
	//Remember to set the size if you make the array bigger and to update the count
	//variable for each Team added.

	//TODO
	
	if(size == 0){
		size = 4;
		teams = new Team*[4];
		teams[0] = new_team;
		count++;
	}
	else if(count <= size){
		teams[count] = new_team;
		count++;
	}
	else if(count > size){
		Team **nTeam;
		nTeam = new Team*[size += 4];
		for(int i = 0; i < size; i++){
			nTeam[i] = teams[i];
			delete teams[i];
		}
		teams = nTeam;
		size += 4;
		count++;
	}

	//If the array is unallocated, allocate it
	//If the array is out of space, make a bigger array and deep copy over all of the old Team*s

	//Regardless of if a resize was needed, add the new_team to the next open space and update the count
}

/**/
League::~League()
{
	//TODO
	for(int i = 0; i < count; i++){
		delete teams[i];
	}
	delete [] teams;
	//Start by deleting all of the teams in the array (similar to how the Team destructor deleted all its Players)

	//After the contents of the array are done being deallocated, delete the array that was storing all the Teams
	//Delete the teams array the standard way you deallocate arrays (HINT: How does delete work on arrays?)

	//This should be about 3 lines of code
}
