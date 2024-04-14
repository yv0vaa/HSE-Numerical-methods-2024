CXX=g++-12
CXXFLAGS=-std=c++20
GSLFLAGS=-lgsl -lgslcblas
HEADERS=$(shell ls include/*.hpp)
SOURCES=$(shell ls src/*.cpp)


ATM_HEADERS=$(shell ls ../lab06/include/*.hpp)
ATM_SOURCES=$(shell ls ../lab06/src/*.cpp)

all: test

test: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@
 
gsl: $(SOURCES) $(HEADERS) $(ATM_SOURCES) $(ATM_HEADERS)
	$(CXX) $(SOURCES) $(ATM_SOURCES) -o $@ $(CXXFLAGS) $(GSLFLAGS)

clean:
	rm -f *.o test a.out