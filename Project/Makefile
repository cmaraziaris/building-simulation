# This is the Makefile of Building Simulation

CXX = g++

CXXFLAGS = -g3 -Wall -I. -std=c++11	#TODO: Remove -g3 before finalisation :3

PROGRAM = building_sim

OBJS = building.o main.o  

$(PROGRAM): clean $(OBJS)
	$(CXX) $(OBJS) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS)
