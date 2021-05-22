CXX = g++
CXXFLAGS = -std=c++20 -Wall -I h -c
LXXFLAGS = -std=c++20 -Ih -pthread
OBJECTS = ./obj/main.o  ./obj/Maze.o
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS)
./obj/main.o: ./cpp/main.cpp ./h/Maze.h
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
./obj/Maze.o: ./cpp/Maze.cpp
	$(CXX) $(CXXFLAGS) ./cpp/Maze.cpp -o ./obj/Maze.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
