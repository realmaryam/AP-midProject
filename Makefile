CXX = g++
CXXFLAGS = -std=c++20 -Wall  -c
LXXFLAGS = -std=c++20 
OBJECTS = main.o  room.o
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS)
main.o: main.cpp  room.h
	$(CXX) $(CXXFLAGS) main.cpp  
room.o: room.cpp
	$(CXX) $(CXXFLAGS) room.cpp  
clean:
	rm -f $(TARGET) $(OBJECTS)
