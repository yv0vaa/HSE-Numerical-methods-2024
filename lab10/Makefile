CXX=g++-12
CXXFLAGS=-std=c++20
GSLFLAGS=-lgsl -lgslcblas
HEADERS=$(shell ls include/*.hpp)
SOURCES=$(shell ls src/*.cpp)

all: analytical

# test: $(SOURCES) $(HEADERS) 
# 	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

analytical: $(SOURCES) $(HEADERS) solution_methods/analytical.cpp
	$(CXX) $(CXXFLAGS) -o $@ solution_methods/analytical.cpp $(SOURCES) $(GSLFLAGS)

clean:
	rm -f *.o test analytical