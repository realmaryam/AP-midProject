CXX = g++
CXXFLAGS = -std=c++20 -Wall  -c
LXXFLAGS = -std=c++20 
OBJECTS = main.o  Maze.o
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS)
main.o: main.cpp 
	$(CXX) $(CXXFLAGS) main.cpp  
Maze.o: Maze.cpp
	$(CXX) $(CXXFLAGS) Maze.cpp  
clean:
	rm -f $(TARGET) $(OBJECTS)
