CXX=g++-12
CXXFLAGS=-std=c++20
HEADERS=$(shell ls include/*.hpp)
SOURCES=$(shell ls src/*.cpp)

all: test

test: $(SOURCES) $(HEADERS) 
	$(CXX) $(CXXFLAGS) $(SOURCES)  -o $@

clean:
	rm -f *.o test a.out