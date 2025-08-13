# Make file.

OBJS	= main.o fileioImp.o memberTypeImp.o
CC		= g++
CCFLAGS	= -Wall -Wextra -pedantic -std=c++11 -g

DEPS	= fileio.h memberType.h

all: main

main: $(OBJS)
	$(CC) $(CCFLAGS) -o main $(OBJS)

main.o:	main.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c main.cpp

fileioImp.o: fileioImp.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c fileioImp.cpp

memberTypeImp.o: memberTypeImp.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c memberTypeImp.cpp

# -----
# clean by removing object files.

clean:
	rm $(OBJS) main
