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
        int dirs[2] { 1 , 1 } ;
        int dirright {} , dirleft {} ;
        
    private:
        size_t Visited;
        std::stack<std::pair<int, int>> stack;
        std::vector<int> neighbours{std::vector<int>(3,0)};
    };
    Maze(int Height , int Width);
    void makeMaze ();
    void makeMainpath();
    int IsInBounds( int x, int y );
    bool IsOutput(Vertex);
private:
    int init_x{} , init_y {},  final_x {} , final_y {};
    int XYToIndex( int x, int y ){return y * MazeHeight + x;}
 //   std::unique_ptr<Vertex> current ;
    int  MazeWidth;
	int  MazeHeight;
    size_t CellWidth { 2 };
    std::vector<Vertex> mainPath ;
    std::vector<std::vector<Vertex>> V ;
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