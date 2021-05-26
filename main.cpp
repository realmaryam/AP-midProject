#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#define RESET   "\033[0m"
#define YELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define RED     "\033[1m\033[31m"      /* Bold Red */
#define GREEN   "\033[1m\033[32m"      /* Bold Green */
#include "room.h"


int getAdjacentRoom(int roomNumber, int size);
int mazeRow(int roomNumber, int size);
int mazeColumn(int roomNumber, int size);
void openDoors(Room *room1, Room *room2, int size);
bool checkComplete(Room **maze, int size);
void updatePaths(Room **maze, int size, int oldPath, int newPath);
void DFS(Room **maze , int size);
std::vector<Room>& nextPath(Room **maze, int size , std::pair<int,int> ,
	 std::vector<Room>& way , std::vector<Room> &total );
bool isIn (Room *room, std::vector<Room>& vector);
void showDFS(Room **maze, int size, std::vector<Room>& way, std::vector<Room>& total );
void showCleaned(Room **maze, int size, std::vector<Room>& way);

int main(){
	int size;
    //srand((unsigned)time(0));
	std::cout << "Input the desired side length for the maze (-1 for random): ";
	std::cin >> size;

	while(size <= 3 && size != -1){
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Invalid size. Size must be a positive integer greater";
		std::cout << " than 3: ";
		std::cin >> size;
	}
	if(size == -1){
		srand((unsigned)time(0));
		size = rand() % 20 + 4;
		std::cout << "Size randomly selected to be " << size << "\n";
	} 

	// create 2D array to be our maze
	Room** maze = new Room*[size];
	for(int i = 0; i < size; i++){
		maze[i] = new Room[size];
	}

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			maze[i][j].setRoomNumber((i * size) + j);
			maze[i][j].setPathNumber((i * size) + j);
		}
	}

	while(!checkComplete(maze, size))
	{
		int roomCount = size * size;
		int room = rand() % roomCount;
		int adjacentRoom = getAdjacentRoom(room, size);
		int row1 = mazeRow(room, size);
		int col1 = mazeColumn(room, size);
		int row2 = mazeRow(adjacentRoom, size);
		int col2 = mazeColumn(adjacentRoom, size);
		if(maze[row1][col1].getPathNumber()!= maze[row2][col2].getPathNumber())
		{
			openDoors(&maze[row1][col1], &maze[row2][col2], size);
			if(maze[row1][col1].getPathNumber() > maze[row2][col2].getPathNumber())
			{
				updatePaths(maze, size, maze[row1][col1].getPathNumber(),
				maze[row2][col2].getPathNumber());
			}
			else {
				updatePaths(maze, size, maze[row2][col2].getPathNumber(),
				maze[row1][col1].getPathNumber());
			}
		}
	} 
	// Open the north door of Room 0 and the South door of the last room
	maze[0][0].setNorth(1);
	maze[size - 1][size - 1].setSouth(1);
	
	std::cout << "\nCurrent Maze:\n";
	std::cout << GREEN;
	for(int i = 0; i < size; i++){
		if(maze[0][i].getNorth() == 0){
			std::cout << "+---";
		} else {
			std::cout << "+   ";
		}
	}
	std::cout << "+\n";
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(maze[i][j].getWest() == 0){
				std::cout << "|   ";	
			} else {
				std::cout << "    ";
			}
		}
		std::cout << "|\n";
		for(int j = 0; j < size; j++){
			if(maze[i][j].getSouth() == 0){
				std::cout << "+---";
			} else {
				std::cout << "+   ";
			}
		}
		std::cout << "+\n";
	}
	std::cout<<RESET;
	
	DFS(maze , size);

	for(int i = 0; i < size; i++){
		delete[] maze[i];
	}
	delete[] maze;
	
	return 0;
}

int getAdjacentRoom(int roomNumber, int size){
	int adj, maxNumber, delta, addSub;
	bool valid = 0;
	maxNumber = (size * size) - 1;

	while(valid == 0){
		valid = 1;
		delta = rand() % 2;
		addSub = rand() % 2;
		if (delta == 0){
			delta = size;
		}
		if(addSub == 1){
			adj = roomNumber + delta;
		} else {
			adj = roomNumber - delta;
		}
		// 4 special cases where it would not be adjacent
		if((adj - roomNumber == 1) && (adj % size == 0)){
			valid = 0;
		}
		if((roomNumber - adj == 1) && (roomNumber % size == 0)){
			valid = 0;
		}
		if((adj < 0) || (adj > maxNumber)){
			valid = 0;
		}
	}
	return adj;
}

int mazeRow(int roomNumber, int size){
	return roomNumber / size;
}

int mazeColumn(int roomNumber, int size){
	return roomNumber % size;
}

void openDoors(Room *room1, Room *room2, int size){
	if(room1->getRoomNumber() - room2->getRoomNumber() == 1){
		room1->setWest(1);
		room2->setEast(1);
	}
	if(room2->getRoomNumber() - room1->getRoomNumber() == 1){
		room2->setWest(1);
		room1->setEast(1);
	}
	if(room1->getRoomNumber() - room2->getRoomNumber() == size){
		room1->setNorth(1);
		room2->setSouth(1);
	}
	if(room2->getRoomNumber() - room1->getRoomNumber() == size){
		room2->setNorth(1);
		room1->setSouth(1);
	}
}

bool checkComplete(Room **maze, int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(maze[i][j].getPathNumber() != 0){
				return false;
			}
		}
	}
	return true;
}

void updatePaths(Room **maze, int size, int oldPath, int newPath){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(maze[i][j].getPathNumber() == oldPath){
				maze[i][j].setPathNumber(newPath);
			}
		}
	}
}

void DFS( Room** maze , int size )
{
    std::vector<Room> way;
	std::vector<Room> total;
	way.push_back(maze[0][0]);
	total.push_back(maze[0][0]);
    way = nextPath( maze, size , {0 ,0} , way , total);
	showCleaned(maze , size , way);
	showDFS(maze, size, way, total);
	
std::cout << RED << "hello world" << RESET << std::endl;

}

std::vector<Room>& nextPath(Room **maze , int size, std::pair<int,int> location ,
		 std::vector<Room>& way , std::vector<Room>& total )
{
    int x {} , y {};
    y = location.first;
    x = location.second;
	int final { way.back().getRoomNumber()};
    maze[y][x].setVisited(1);

	if(final ==(size*size)-1)
		return way;
		
	if(final !=(size*size)-1)
	{
	    if( y!=0 && maze[y][x].getNorth() && !maze[y-1][x].getVisited() )
	    {
	        maze[y-1][x].flag = 0;
	        way.push_back(maze[y-1][x]);
			total.push_back(maze[y-1][x]);
	        way = nextPath(maze , size , {y-1 , x},way , total);
			if(way.back().getRoomNumber()==(size*size)-1)
				return way;
	    }

    	if( x!=size-1 && maze[y][x].getEast() && !maze[y][x+1].getVisited() )
    	{
        	maze[y][x+1].flag = 1 ; 
        	way.push_back(maze[y][x+1]);
			total.push_back(maze[y][x+1]);
        	way = nextPath(maze, size , {y , x+1}, way , total );
			if(way.back().getRoomNumber()==(size*size)-1)
				return way;
    	}

    	if( y!=size-1 && maze[y][x].getSouth() && !maze[y+1][x].getVisited() )
    	{
        	maze[y+1][x].flag = 2 ; 
        	way.push_back(maze[y+1][x]);
			total.push_back(maze[y+1][x]);
        	way = nextPath(maze, size , {y+1 , x}, way , total );
			if(way.back().getRoomNumber()==(size*size)-1)
				return way;
    	}
    

    	if( x!=0 && maze[y][x].getWest() && !maze[y][x-1].getVisited() )
    	{
        	maze[y+1][x].flag = 3 ; 
        	way.push_back(maze[y][x-1]);
			total.push_back(maze[y][x-1]);
        	way = nextPath(maze, size , {y , x-1}, way ,total );
			if(way.back().getRoomNumber()==(size*size)-1)
				return way;
    	}
        		way.pop_back();
				return way;
	}
	return way;
}

bool isIn (Room *room, std::vector<Room>& vector)
{
	for( size_t i{}; i<vector.size(); i++)
	{
		if(*room == vector[i])
			return true;
	}
	return false;
}

void showDFS(Room **maze, int size, std::vector<Room>& way, std::vector<Room>& total )
{

	std::cout << "\nDFS method solved Maze:\n"<<GREEN<<std::endl;

	int check {};
	for(int i = 0; i < size; i++){
		if(maze[0][i].getNorth() == 0){
			std::cout<< "+---";
			
		} 
		else 
		{
			std::cout<< "+ "<< YELLOW <<"* "<<GREEN;
		}
	}
	std::cout<< GREEN << "+\n";
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++)
		{	
			check =0;
			if( isIn(&maze[i][j], way))
			{
				check =1;
				if(maze[i][j].getWest() == 0)
					{
						std::cout<<GREEN<< "| "<<YELLOW<<"* "<<GREEN ;	
					} 
					else {
						std::cout<<YELLOW<< "  * "<<GREEN;
					}
			}
			else if(isIn(&maze[i][j], total))
			{
				check =1;
				if(maze[i][j].getWest() == 0)
					{
						std::cout<<GREEN<< "| "<<RED<<"* "<<GREEN ;	
					} 
					else {
						std::cout<<RED<< "  * "<<GREEN;
					}
			}

			if(!check)
			{
				if(maze[i][j].getWest() == 0)
				{

					std::cout<<GREEN << "|   ";	
				} 
				else {
					std::cout << "    ";
				}
			}
		}
		
		std::cout << "|\n";
		for(int j = 0; j < size; j++)
		{
			 check=0;
				if(maze[i][j].getSouth() == 0)
				{
					std::cout <<GREEN<< "+---";
				}
				else {
					if(i == (size-1) && j==(size-1))
						std::cout << "+ "<<YELLOW<<"* "<<GREEN;
					else
						std::cout << "+   ";
				}
		}
		std::cout << "+\n"<<RESET;
	}
}

void showCleaned(Room **maze, int size , std::vector<Room>& way)
{
	std::cout << "\nDFS method solved Maze:\n"<<GREEN<<std::endl;

	int check {};
	for(int i = 0; i < size; i++){
		if(maze[0][i].getNorth() == 0){
			std::cout<< "+---";
			
		} 
		else 
		{
			std::cout<< "+ "<< YELLOW <<"* "<<GREEN;
		}
	}
	std::cout<< GREEN << "+\n";
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++)
		{	
			check =0;
			if( isIn(&maze[i][j], way))
			{
				check =1;
				if(maze[i][j].getWest() == 0)
					{
						std::cout<<GREEN<< "| "<<YELLOW<<"* "<<GREEN ;	
					} 
					else {
						std::cout<<YELLOW<< "  * "<<GREEN;
					}
			}

			if(!check)
			{
				if(maze[i][j].getWest() == 0)
				{

					std::cout<<GREEN << "|   ";	
				} 
				else {
					std::cout << "    ";
				}
			}
		}
		
		std::cout << "|\n";
		for(int j = 0; j < size; j++)
		{
			 check=0;
				if(maze[i][j].getSouth() == 0)
				{
					std::cout <<GREEN<< "+---";
				}
				else {
					if(i == (size-1) && j==(size-1))
						std::cout << "+ "<<YELLOW<<"* "<<GREEN;
					else
						std::cout << "+   ";
				}
		}
		std::cout << "+\n"<<RESET;
	}
}