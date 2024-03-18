CXX=g++-12
CXXFLAGS=-std=c++20
HEADERS=include/CD.hpp include/Pressure.hpp
SOURCES=src/CD.cpp src/test.cpp src/Pressure.cpp

all: clean test

test: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

clean:
	rm -f *.o test a.out