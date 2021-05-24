#include"Maze.h"
#include <stdlib.h>
#include <time.h>

#define EAST 0
#define SOUTH 1

// Maze::Vertex::Vertex()
//     : Vertex(0 , 0)
// {
    
//     std::cout<<"vertex default constructor\n";
// }

Maze::Vertex::Vertex( int x , int y )
{
    std::cout<<"vertex  constructor\n";
    location.first = x;
    location.second = y;
    neighbour = 0;
    dirright =1;
    dirdown = 1;
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
    std::cout<<"maze constructor\n";
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

void Maze::visit( Vertex v )
{
    int r{};
    if(v.dirdown == 0)
        v.neighbour = EAST;
    if(v.dirright == 0)
        v.neighbour = SOUTH;
    if(v.dirdown == 0 && v.dirright == 0 )
        v.neighbour = 2 ;
    else
    {
        r = rand() %2;
        if(r == 0 )
            v.neighbour = EAST;
        if(r == 1 )
            v.neighbour = SOUTH;
    }
        
}

void Maze::makeMaze ()
{
    std::cout<<"here is Make maze\n";
    for(int j{0}; j< MazeHeight ; j++)
       { 
           V.push_back(std::vector<Vertex>());
           for(int i{0}; i< MazeWidth ; i++)
            {   
                //Vertex v {i , j };
                Vertex* p = new Vertex { i , j } ;
                std::cout<<"here is Make maze\n";
                V[j].push_back( *p );
                // if( v.location.second == 0)
                //    v.dirs[NORTH] = 0; 
                if( p->location.first == MazeWidth-1)
                   p->dirright = 0; 
                // if( v.location.first == 0)
                //    v.dirs[WEST] = 0; 
                if( p->location.second == MazeHeight-1)
                   p->dirdown = 0;     
            }
       }
    for(int j{0}; j< MazeHeight ; j++)
        for(int i{0}; i< MazeWidth ; i++)
        {
            visit( V[j][i]);
        }
    
}

void Maze::show()
{
    char grid [ MazeWidth * MazeHeight ];
    for (int i {}; i < MazeWidth * MazeHeight ; i++)
    {
        grid[i]= '#';
        
    }
      for (int i {}; i < MazeWidth * MazeHeight ; i++)
    {
       std::cout<<grid[i];
        
    }
    
    for(int j{0}; j< MazeHeight ; j++)
        for(int i{0}; i< MazeWidth ; i++)
        {
            if ( V[j][i].neighbour == EAST)
                grid[ j * MazeWidth +i ] = ' ';
        }
}