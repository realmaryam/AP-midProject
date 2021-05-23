#ifndef MAZE_H
#define MAZE_H
#include<iostream>
#include<stack>
#include<vector>
#include <utility>


class Maze{
public:
    class Vertex
    {
    public:
        Vertex( int , int );
        std::pair<int, int> location;
        int dirs[4] { 1 , 1 , 1 , 1} ;
    private:
        size_t Visited;
        std::stack<std::pair<int, int>> stack;
        std::vector<int> neighbours{std::vector<int>(3,0)};
    };
    Maze(size_t Height , size_t Width);
    void makeMaze ();
    void makeMainpath();
    int IsInBounds( int x, int y );
    bool IsOutput(Vertex);
private:
    int init_x{} , init_y {},  final_x {} , final_y {};
    int XYToIndex( int x, int y ){return y * MazeHeight + x;}
    Vertex current ;
    size_t  MazeWidth;
	size_t  MazeHeight;
    size_t CellWidth { 2 };
    std::vector<Vertex> mainPath ;
    std::vector<Vertex> V ;
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