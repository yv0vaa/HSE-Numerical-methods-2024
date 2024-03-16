# Define the compiler
CXX = g++-12

# Define the compiler flags
CXXFLAGS = -std=c++20

# Define the source files
SRCS = src/test.cpp src/AAD22.cpp include/Differentiator.hpp

# Define the output file
OUTPUT = test

# Default target
all: $(OUTPUT)

# Linking rule
$(OUTPUT): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Phony target for cleaning up
clean:
	rm -f $(OUTPUT)

# Declare phony targets
.PHONY: all clean