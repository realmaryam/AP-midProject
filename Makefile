CXX = g++
CXXFLAGS = -std=c++20 -Wall -I h -c
LXXFLAGS = -std=c++20 -Ih -pthread
OBJECTS = ./obj/main.o 
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS)
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
