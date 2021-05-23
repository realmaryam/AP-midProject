#include"Maze.h"
#include <stdlib.h>
#include <time.h>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

Maze::Vertex::Vertex()
    : Vertex(0 , 0)
{
}

Maze::Vertex::Vertex( int x , int y )
{
    location.first = x;
    location.second = y;
}

// Maze::Vertex::Vertex( const Vertex& v1)
// {
//     for (size_t i {}; i < 4; i++)
//     {
//         dirs[i]= v1.dirs[i]
//     }
    
// }

Maze::Maze(int m , int n)
    : MazeWidth { m }
    , MazeHeight { n }
{
}

// int Maze::IsInBounds( int x, int y )
//     {
//         if (x < 0 || x >= MazeWidth)
//             return false;
//         if (y < 0 || y >= MazeHeight)
//             return false;
//         return true;
//     }

bool Maze::IsOutput( Vertex v )
{
    if( v.location.first == MazeWidth-1 && v.location.second == MazeHeight-1 )
        return true;
    return false;
}

void Maze::makeMainpath ()
{
    //size_t line { MazeWidth }
    // current.location.first = 0;
    // current.location.second = 0;
    //Vertex current { V[0] };

    while( !IsOutput(V[0]) )
    {
        
    }
    
}

void Maze::makeMaze ()
{

    for(int j{0}; j< MazeHeight ; j++)
        for(int i{0}; i< MazeWidth ; i++)
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