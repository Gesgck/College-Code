# Make file for pointers assignment

OBJS	= main.o team.o league.o
CC		= g++
CCFLAGS	= -Wall -Wextra -pedantic -std=c++11 -g
MAIN_DEPS	= team.h league.h
LEAGUE_DEPS = team.h

all: main

main: $(OBJS)
	@echo "Linking Objects..."
	$(CC) $(CCFLAGS) -o baseball $(OBJS)
	@echo "Done! Finished building baseball program"

main.o:	main.cpp $(MAIN_DEPS)
	@echo "Compiling Main..."
	$(CC) $(CCFLAGS) -c main.cpp
team.o: team.cpp $(COMPLEX_DEPS)
	@echo "Compiling Team and Player..."
	$(CC) $(CCFLAGS) -c team.cpp
league.o: league.cpp $(TREASURE_DEPS)
	@echo "Compiling League..."
	$(CC) $(CCFLAGS) -c league.cpp


# -----
# clean by removing object files.

clean:
	rm $(OBJS) baseball
