# This is the Makefile of Building Simulation

CXX = g++

CXXFLAGS = -Wall -I. -std=c++11	

PROGRAM = building_sim

OBJS = building.o main.o  

$(PROGRAM): clean $(OBJS)
	$(CXX) $(OBJS) -o $(PROGRAM)

run: $(PROGRAM)							# Run with default arguments
	./$(PROGRAM) 100 32 48 15 20 55 3

clean: 
	rm -f $(PROGRAM) $(OBJS)