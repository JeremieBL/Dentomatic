# Makefile for Dentomatic

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = dentomatic
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) patients.dat appointments.dat

run: $(TARGET)
	./$(TARGET)
