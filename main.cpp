#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include <chrono>
#include <stdio.h>
#include <time.h>
#define RESET   "\033[0m"
#define YELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define RED     "\033[1m\033[31m"      /* Bold Red */
#define GREEN   "\033[1m\033[32m"      /* Bold Green */
#define MAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define CYAN    "\033[1m\033[36m"      /* Bold Cyan */
#include "room.h"

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

int getAdjacentRoom(int roomNumber, int size);
int mazeRow(int roomNumber, int size);
int mazeColumn(int roomNumber, int size);
void openDoors(Room *room1, Room *room2, int size);
bool checkComplete(Room **maze, int size);
void updatePaths(Room **maze, int size, int oldPath, int newPath);
void showMaze(Room** maze, int size);
void DFS(Room **maze , int size);
std::list<Room>& nextPath(Room **maze, int size , std::pair<int,int> ,
		std::list<Room>& way , std::list<Room> &total );
bool isIn (Room *room, std::vector<Room>& vector);
bool isIn (Room *room, std::list<Room>& list);
void showDFS(Room **maze, int size, std::list<Room>& total );
void cleanVisited(Room** maze, int size);
void resetParent(Room** maze, int size);
void BFS(Room** maze, int size);
std::list<Room>& nextBreadth(Room** maze, int size, std::pair<int,int> ,
		std::list<Room>& queue);
void BFSPath(Room** maze, int size, std::list<Room>& path);
void showBFS(Room **maze, int size);
void showCleanedD(Room **maze, int size, std::list<Room>& way);
void showCleanedB(Room **maze, int size, std::list<Room>& path);

int main(){
	int size;
    srand((unsigned)time(0));
	std::cout<<MAGENTA;
	std::cout<<"Hey! This is a program that builds a square form maze and then solves it! \n";
	std::cout<< " in two method : Breadth First Search (BFS) and Depth First Search (DFS) \n";
	delay(50);
	std::cout<< "lets see how it is!\n You just need to press the size of side of the maze you want! (as intiger number)\n";
	std::cout << " or you can press -1 for random size : ";
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
	std::cout<<RESET;
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
	
	showMaze(maze , size);
	int w {};
	std::cout<<CYAN;
	std::cout<<"Which method you want to solve this maze?"<<std::endl;
	std::cout<<"press 1 for BFS method and 2 for DFS method"<<std::endl;
	std::cin>>w;
	while(w != 1 && w != 2){
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Invalid input! you should press 1 or 2 for this mean:\n";
		std::cout << " 1 -----> BFS \n 2 -----> DFS \n";
		std::cin >> size;
	}
	if(w == 1)
		BFS(maze, size);
	if(w == 2)
		DFS(maze , size);
	std::cout<<RESET;

	//maze destructor
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

void showMaze(Room** maze, int size)
{
	std::cout << "\nThe Maze you made:\n";
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
	std::cout<<RESET<<std::endl;
}

void DFS( Room** maze , int size )
{
	char a;
    std::list<Room> way;
	std::list<Room> total;
	resetParent(maze, size);
	cleanVisited(maze, size);
	way.push_back(maze[0][0]);
	total.push_back(maze[0][0]);
    way = nextPath( maze, size , {0 ,0} , way , total);
	showDFS(maze, size, total);
	showCleanedD(maze , size , way);
	std::cout<<CYAN<<"Do you want to see the solution in BFS method too?\n";
	std::cout<<"press y for yes and n for no\n";
	std::cin>> a;
	if(a=='y')
		BFS(maze, size);
}

std::list<Room>& nextPath(Room **maze , int size, std::pair<int,int> location ,
		 std::list<Room>& way , std::list<Room>& total )
{
    int x {} , y {}, xp {}, yp {};  
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
			maze[y-1][x].setParent(maze[y][x].getRoomNumber()); 
	        way.push_back(maze[y-1][x]);
			total.push_back(maze[y-1][x]);
	        way = nextPath(maze , size , {y-1 , x},way , total);
			if(way.back().getRoomNumber()==(size*size)-1)
				return way;
	    }

    	if( x!=size-1 && maze[y][x].getEast() && !maze[y][x+1].getVisited() )
    	{
			maze[y][x+1].setParent(maze[y][x].getRoomNumber());
        	way.push_back(maze[y][x+1]);
			total.push_back(maze[y][x+1]);
        	way = nextPath(maze, size , {y , x+1}, way , total );
			if(way.back().getRoomNumber()==(size*size)-1)
				return way;
    	}

    	if( y!=size-1 && maze[y][x].getSouth() && !maze[y+1][x].getVisited() )
    	{
			maze[y+1][x].setParent(maze[y][x].getRoomNumber());
        	way.push_back(maze[y+1][x]);
			total.push_back(maze[y+1][x]);
        	way = nextPath(maze, size , {y+1 , x}, way , total );
			if(way.back().getRoomNumber()==(size*size)-1)
				return way;
    	}
    

    	if( x!=0 && maze[y][x].getWest() && !maze[y][x-1].getVisited() )
    	{
			maze[y][x-1].setParent(maze[y][x].getRoomNumber());
        	way.push_back(maze[y][x-1]);
			total.push_back(maze[y][x-1]);
        	way = nextPath(maze, size , {y , x-1}, way ,total );
			if(way.back().getRoomNumber()==(size*size)-1)
				return way;
    	}
        way.pop_back();
		xp = mazeColumn(maze[y][x].getParent(), size);
		yp = mazeRow(maze[y][x].getParent(),size);
		total.push_back(maze[yp][xp]);
		return way;
	}
	return way;
}

bool isIn (Room *room, std::list<Room>& list)
{
	std::list<Room>::iterator it;
	for (it = list.begin(); it != list.end(); ++it)
	{
    	if(*room == *it)
			return true;
	}
	return false;
}

void showDFS(Room **maze, int size, std::list<Room>& total )
{

	
	int check {} , check2 {};
	while(total.size())
	{
		std::cout << "\033[2J\033[1;1H";
		delay (300);
		std::cout << "\nDFS method solving Maze:\n"<<GREEN<<std::endl;
		for(int i = 0; i < size; i++){
		if(maze[0][i].getNorth() == 0){
			std::cout<< "+---";
			
		} 
		else 
		{
			std::cout<<GREEN<< "+   "<<GREEN;
		}
		}
		std::cout<< GREEN << "+\n";
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++)
			{	
				check =0;
				if( maze[i][j]==total.front() && !check2)
				{
					check =1;
					check2 =1;
					total.pop_front();
					if(maze[i][j].getWest() == 0)
						{
							std::cout<<GREEN<< "| "<<YELLOW<<"@ "<<GREEN ;	
						} 
						else {
							std::cout<<YELLOW<< "  @ "<<GREEN;
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
							std::cout << "+   ";
					}
			}
			std::cout << "+\n"<<RESET;
		}
	check2 =0;
	}
	std::cout<<std::endl;
}

void showCleanedD(Room **maze, int size , std::list<Room>& way)
{
	std::cout <<"\n the path you have been through @DFS method:\n"<<GREEN<<std::endl;
	int check {};
		for(int i = 0; i < size; i++){
		if(maze[0][i].getNorth() == 0){
			std::cout<< "+---";
			
		} 
		else 
		{
			std::cout<< "+ "<< RED <<"* "<<GREEN;
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
							std::cout << "+ "<<RED<<"* "<<GREEN;
						else
							std::cout << "+   ";
					}
			}
			std::cout << "+\n"<<RESET;
		}
	std::cout<<std::endl;
}

void cleanVisited(Room** maze, int size)
{
	for (int i {}; i < size; i++)
		for (int j {}; j < size; j++)
			maze[i][j].setVisited(0);
	
}

void resetParent(Room** maze, int size)
{
	for (int i {}; i < size; i++)
		for (int j {}; j < size; j++)
			maze[i][j].setParent(0);
}

void BFS (Room** maze, int size)
{
	std::list<Room> queue;
	maze[0][0].setLevel(0);
	resetParent(maze, size);
	cleanVisited(maze, size);
	queue.push_back(maze[0][0]);
	queue = nextBreadth(maze, size, {0, 0}, queue);
	std::list<Room> path;
	path.push_back(maze[size-1][size-1]);
	BFSPath(maze, size, path);
	showBFS(maze, size);
	showCleanedB(maze, size, path);
}

std::list<Room>& nextBreadth (Room** maze, int size, std::pair<int,int> location
		, std::list<Room>& queue)
{
	int y {location.first};
	int x {location.second};
	maze[y][x].setVisited(1);
	Room final { queue.back()};
	
	if( final.getRoomNumber()== (size*size)-1 )
	{
		return queue;
	}
	if( final.getRoomNumber()!= (size*size)-1 )
	{
	
		if( y!=0 && maze[y][x].getNorth() && !maze[y-1][x].getVisited() )
		{
			maze[y-1][x].setLevel(maze[y][x].getLevel()+1);
			queue.push_back(maze[y-1][x]);
			maze[y-1][x].setParent(maze[y][x].getRoomNumber());
		}
		if( x!=size-1 && maze[y][x].getEast() && !maze[y][x+1].getVisited() )
		{
			maze[y][x+1].setLevel(maze[y][x].getLevel()+1);
			queue.push_back(maze[y][x+1]);
			maze[y][x+1].setParent(maze[y][x].getRoomNumber());
		}
		if( y!=size-1 && maze[y][x].getSouth() && !maze[y+1][x].getVisited() )
		{
			maze[y+1][x].setLevel(maze[y][x].getLevel()+1);
			queue.push_back(maze[y+1][x]);
			maze[y+1][x].setParent(maze[y][x].getRoomNumber());
		}
		if( x!=0 && maze[y][x].getWest() && !maze[y][x-1].getVisited() )
		{
			maze[y][x-1].setLevel(maze[y][x].getLevel()+1);
			queue.push_back(maze[y][x-1]);
			maze[y][x-1].setParent(maze[y][x].getRoomNumber());
		}
	}
	queue.pop_front();
	int n {queue.front().getRoomNumber()};
	int ny { mazeRow(n, size)} , nx { mazeColumn(n, size)};
	queue = nextBreadth(maze, size, {ny, nx}, queue);
	return queue;

}

void BFSPath(Room** maze, int size, std::list<Room>& path)
{
	int next { path.back().getParent()};
	int ny {mazeRow(next, size)} , nx {mazeColumn(next, size)};
	while(path.back().getRoomNumber() != 0)
	{
	 	path.push_back(maze[ny][nx]);
		next = path.back().getParent();
		ny = mazeRow(next, size);
		nx = mazeColumn(next, size);
	}
}

void showBFS(Room **maze, int size )
{
	std::cout << "\nBFS method solving Maze:\n"<<GREEN<<std::endl;
	int check {} ;
	int L { maze[size-1][size-1].getLevel() +1 };
	int level {};
	while(L)
	{ 
		L--;
		std::cout << "\033[2J\033[1;1H";
		delay (500);
		for(int i = 0; i < size; i++){
		if(maze[0][i].getNorth() == 0){
			std::cout<< "+---";
			
		} 
		else 
		{
			std::cout<<GREEN<< "+   "<<GREEN;
		}
		}
		std::cout<< GREEN << "+\n";
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++)
			{	
				check =0;
				if( maze[i][j].getLevel()==level )
				{
					check =1;
					if(maze[i][j].getWest() == 0)
						{
							std::cout<<GREEN<< "| "<<YELLOW<<"@ "<<GREEN ;	
						} 
						else {
							std::cout<<YELLOW<< "  @ "<<GREEN;
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
							std::cout << "+   ";
					}
			}
			std::cout << "+\n"<<RESET;
		}
	level++;
	std::cout<< " current level: "<< level-1 <<std::endl;
	}
	std::cout<<std::endl;
}

void showCleanedB(Room **maze, int size, std::list<Room>& path)
{
	std::cout<<"the path you have been through @BFS method:"<<std::endl;
	int check {};
	for(int i = 0; i < size; i++){
		if(maze[0][i].getNorth() == 0){
			std::cout<<GREEN<< "+---";
			
		} 
		else 
		{
			std::cout<<GREEN<< "+ "<< RED <<"* "<<GREEN;
		}
	}
	std::cout<< GREEN << "+\n";
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++)
		{	
			check =0;
			if( isIn(&maze[i][j], path))
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
						std::cout << "+ "<<RED<<"* "<<GREEN;
					else
						std::cout << "+   ";
				}
		}
		std::cout << "+\n"<<RESET;
	}
	std::cout<<std::endl;
}