# Make file.

OBJS	= main.o personTypeImp.o patientTypeImp.o doctorTypeImp.o dateTypeImp.o billTypeImp.o
CC		= g++
CCFLAGS	= -Wall -Wextra -pedantic -std=c++11 -g

DEPS	= personType.h patientType.h doctorType.h dateType.h billType.h     

all: main

main: $(OBJS)
	$(CC) $(CCFLAGS) -o main $(OBJS)

main.o:	main.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c main.cpp

personType.o: personTypeImp.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c personTypeImp.cpp

patientTypeImp.o: patientTypeImp.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c patientTypeImp.cpp

doctorTypeImp.o: doctorTypeImp.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c doctorTypeImp.cpp

dateTypeImp.o: dateTypeImp.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c dateTypeImp.cpp

billTypeImp.o: billTypeImp.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c billTypeImp.cpp
	

# -----
# clean by removing object files.

clean:
	rm $(OBJS) main
