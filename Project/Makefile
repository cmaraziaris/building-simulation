# This is the Makefile of Building Simulation

CFLAGS= -g3 -Wall.
CC = g++

PROGRAM = building_sim

OBJS = building.o main.o  

$(PROGRAM): clean $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS)