CXX=g++-12
CXXFLAGS=-std=c++20
GSLFLAGS=-lgsl -lgslcblas
HEADERS=$(shell ls include/*.hpp)
SOURCES_GSL=src/Observer.cpp src/GSLIntegrator.cpp src/RHS.cpp

SOURCES_TEST = src/Observer.cpp src/OurIntegrator.cpp src/RHS.cpp
ATM_HEADERS=$(shell ls ../lab06/include/*.hpp)
ATM_SOURCES=$(shell ls ../lab06/src/*.cpp)

all: test

test: $(SOURCES_TEST) $(HEADERS) $(ATM_HEADERS) $(ATM_SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES_TEST) $(ATM_SOURCES) -o $@
 
gsl: $(SOURCES_GSL) $(HEADERS) $(ATM_SOURCES) $(ATM_HEADERS)
	$(CXX) $(SOURCES_GSL) $(ATM_SOURCES) -o $@ $(CXXFLAGS) $(GSLFLAGS)

clean:
	rm -f *.o test a.out