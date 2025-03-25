CXX = g++

CXXFLAGS = -std=c++20

PROG = CircuitSimulator
HDRS = src/parse.hpp src/solve.hpp src/stamp.hpp src/Elements/Element.hpp
SRCS = main.cpp src/parse.cpp src/solve.cpp src/stamp.cpp src/Elements/Element.cpp

$(PROG): $(OBJECTS) 
	$(CXX) -o $(PROG) $(SRCS) $(CXXFLAGS)
