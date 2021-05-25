#ifndef MAZE_H
#define MAZE_H
#include<iostream>
#include<stack>
#include<vector>
#include <utility>
#include <memory>


class Maze{
public:
    class Vertex
    {
    public:
        Vertex();
        Vertex( int , int );
        std::pair<int, int> location;
        int neighbour {};
        int dirright { 1 } , dirdown { 1 } ;
        int status { };
       // std::vector<std::pair<int,int>> adjacent;
        
    private:
        //size_t Visited;
        //std::stack<std::pair<int, int>> stack;
        
    };
    Maze(int Height , int Width);
    void makeMaze ();
    void visit( Vertex &);
    void makeMainpath();
    int IsInBounds( int x, int y );
    bool IsOutput( Vertex );
    void show ( std::vector<std::vector<Vertex>> V );
    void check ( std::vector<std::vector<Vertex>> V , int , int );
private:
    int init_x{} , init_y {},  final_x {} , final_y {};
    int XYToIndex( int x, int y ){return y * MazeHeight + x;}
    int nextLine( int i ){return i + MazeWidth;}
 //   std::unique_ptr<Vertex> current ;
    int  MazeWidth;
	int  MazeHeight;
    std::vector<std::vector<char>> grid ;
    size_t CellWidth { 2 };
    std::vector<Vertex> mainPath ;
    std::vector<std::vector<Vertex>> V ;
    //std::shared_ptr<Vertex> p ;
    Vertex* p;
	//int* MazeSize;
    /*
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|        |           |                          |
+  +--+  +  +--+  +  +  +--+--+--+--+--+  +--+--+
|     |  |  |  |  |  |     |           |        |
+--+  +  +  +  +  +--+--+  +--+--+--+  +--+--+  +
|     |  |     |        |        |     |        |
+  +--+  +--+--+  +--+  +--+--+  +  +--+  +--+  +
|     |        |     |        |  |  |     |  |  |
+--+--+--+--+  +  +--+--+  +  +  +  +  +--+  +  +
|        |     |  |     |  |        |  |  |     |
+  +--+  +  +--+  +  +  +--+--+--+--+  +  +  +--+
|  |     |  |     |  |        |        |  |  |  |
+  +  +--+  +--+--+  +--+--+  +  +--+--+  +  +  +
|  |     |     |     |     |     |        |  |  |
+  +--+  +--+  +  +--+  +--+--+--+  +--+--+  +  +
|     |           |                             |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+ */

};

#endif