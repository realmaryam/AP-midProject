#include"Maze.h"
#include <stdlib.h>
#include <time.h>

Maze::Vertex::Vertex( int fx , int fy )
    : final_x { fx }
    , final_y { fy }
{
}

Maze::Maze(size_t m , size_t n)
    : MazeWidth { m }
    , MazeHeight { n }
{
    Vertex( m*CellWidth , n*CellWidth);
    
}

void Maze::makeMaze ()
{
    
}