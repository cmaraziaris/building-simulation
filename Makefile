# This is the Makefile of Building Simulation

CXX = g++

CXXFLAGS = -Wall -I. -std=c++11	

PROGRAM = building_sim

OBJS = building.o main.o  

$(PROGRAM): clean $(OBJS)
	$(CXX) $(OBJS) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS)
