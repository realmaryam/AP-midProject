#include"Maze.h"
#include <stdlib.h>
#include <time.h>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

Maze::Vertex::Vertex( int x , int y )
{
    location.first = x;
    location.second = y;
}

Maze::Maze(size_t m , size_t n)
    : MazeWidth { m }
    , MazeHeight { n }
{
    Vertex( m*CellWidth , n*CellWidth);

}

int Maze::IsInBounds( int x, int y )
    {
        if (x < 0 || x >= MazeWidth)
            return false;
        if (y < 0 || y >= MazeHeight)
            return false;
        return true;
    }

bool Maze::IsOutput(Vertex)

void Maze::makeMainpath ()
{
    //size_t line { MazeWidth }
    // current.location.first = 0;
    // current.location.second = 0;
    current = V[0];

    while(  )
    {
        while(V[i].location.first>)
    }
    
}

void Maze::makeMaze ()
{

    for(size_t j{0}; j< MazeHeight ; j++)
        for(size_t i{0}; i< MazeWidth ; i++)
            {
                Vertex v (i , j);
                V.push_back( v );
                if( v.location.second == 0)
                   v.dirs[NORTH] = 0; 
                if( v.location.first == MazeWidth-1)
                   v.dirs[EAST] = 0; 
                if( v.location.first == 0)
                   v.dirs[WEST] = 0; 
                if( v.location.second == MazeHeight-1)
                   v.dirs[SOUTH] = 0;     
            }
    makeMainpath();
}