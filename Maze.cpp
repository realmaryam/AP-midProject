#include"Maze.h"
#include <stdlib.h>
#include <time.h>

#define EAST 0
#define SOUTH 1
#define NONE 2

// Maze::Vertex::Vertex()
//     : Vertex(0 , 0)
// {
    
//     std::cout<<"vertex default constructor\n";
// }

Maze::Vertex::Vertex( int x , int y )
{
    location.first = x;
    location.second = y;
    neighbour = 0;
    dirright =1;
    dirdown = 1;
}

Maze::Maze(int m , int n)
    : MazeWidth { m }
    , MazeHeight { n }
{
}


bool Maze::IsOutput( Vertex v )
{
    if( v.location.first == MazeWidth-1 && v.location.second == MazeHeight-1 )
        return true;
    return false;
}

void Maze::visit( Vertex& v )
{
     std::cout<<v.dirdown<<v.dirright<<std::endl; 
    v.status =1;
    int r{};
    if(v.dirdown == 0 )
        v.neighbour = EAST;
    if(v.dirright == 0)
        v.neighbour = SOUTH;
    if(v.dirdown == 0 && v.dirright == 0 )
        v.neighbour = NONE ;
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
    for(int j{0}; j< MazeHeight ; j++)
       { 
           V.push_back(std::vector<Vertex>());
           for(int i{0}; i< MazeWidth ; i++)
            {   
                Vertex* p  = (new Vertex {i ,j});
                V[j].push_back( *p );
            }
       }
    for(int j{0}; j< MazeHeight ; j++)
        for(int i{0}; i< MazeWidth ; i++)
        {
            if( V[j][i].location.first == MazeWidth-1)
                    V[j][i].dirright = 0;
            if( V[j][i].location.second == MazeHeight-1)
                    V[j][i].dirdown = 0;
        }

    srand( time(0) );
    int r{};
    for(int j{0}; j< MazeHeight ; j++)
        for(int i{0}; i< MazeWidth ; i++)
        {
            if(V[j][i].dirdown == 0 )
            {
                V[j][i].neighbour = EAST;
            }
            if(V[j][i].dirright == 0)
            {
                V[j][i].neighbour = SOUTH;
            }
            if(V[j][i].dirdown == 0 && V[j][i].dirright == 0 )
            {
                V[j][i].neighbour = NONE ;
            }
            else if (V[j][i].dirdown == 1 && V[j][i].dirright == 1 )
            {
                r = rand() %2;
                if(r == 0 )
                    V[j][i].neighbour = EAST;
                if(r == 1 )
                    V[j][i].neighbour = SOUTH;  
            }  
        }

    show(V);
}


void Maze::show( std::vector<std::vector<Vertex>> V )
{
    for (int i { } ; i < 2 * MazeWidth + 1 ; i++)
    {
        std::cout<<"#";
    }
    std::cout<<std::endl;

    for(int j{}; j< 2 * MazeHeight ; j++)
    {
        grid.push_back(std::vector<char>());
        for(int i{}; i< 2 * MazeWidth ; i++)
        {
            grid[j].push_back('#');
        }
    }
    for(int j{}; j< MazeHeight ; j++)
    {
        for(int i{}; i<  MazeWidth ; i++)
        {
            grid[2*j][2*i] = ' ';
            if( V[j][i].neighbour == EAST )
            { 
                grid[2*j][2*i+1] = ' ';
            }
            if( V[j][i].neighbour == SOUTH )
            {
                grid[2*j+1][2*i] = ' ';
            }
        }
    }
    grid[0][0] = ' ';
    grid[MazeHeight][MazeWidth] = ' ';
    for(int j{}; j< 2* MazeHeight ; j++)
    {
        std::cout<<"#";
        for(int i{}; i< 2* MazeWidth ; i++)
        {
            std::cout<<grid[j][i];
        }
        std::cout<<std::endl;
    }
}