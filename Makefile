CXX = g++

CXXFLAGS = -std=c++20 -g

PROG = CircuitSimulator
HDRS = src/constants.hpp src/guess.hpp src/parse.hpp src/solve.hpp src/stamp.hpp src/Elements/Element.hpp
SRCS = main.cpp src/constants.cpp src/guess.cpp src/parse.cpp src/solve.cpp src/stamp.cpp src/Elements/Element.cpp

$(PROG): $(OBJECTS) 
	$(CXX) -o $(PROG) $(SRCS) $(CXXFLAGS)
