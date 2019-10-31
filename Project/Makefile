# This is the Makefile of Building Simulation

CFLAGS= -g3 -Wall. #TODO: Remove -g3 from before finalisation :3
CC = g++

PROGRAM = building_sim

OBJS = building.o main.o  

$(PROGRAM): clean $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS)
