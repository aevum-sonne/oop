CXX=clang++ -arch x86_64
CXXFLAGS=-std=c++17
SOURCES=main.cpp Matrix3x3/Matrix3x3.cpp Multiplier/Multiplier.cpp
OBJECTS=$(SOURCES:.cpp=.out)
EXECUTABLE=main.out
TEST_FILE="input.txt"

.PHONY: all run test

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(SOURCES) 
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

run:
	./main.out "Tests/Input/matrix11.txt" "Tests/Input/matrix12.txt"

clean:
	rm -f *.out