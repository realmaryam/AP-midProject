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
    std::cout<<"here is Make maze\n";
    for(int j{0}; j< MazeHeight ; j++)
       { 
           V.push_back(std::vector<Vertex>());
           for(int i{0}; i< MazeWidth ; i++)
            {   
                Vertex* p  = (new Vertex {i ,j});
                std::cout<<"here is Make maze\n";
                V[j].push_back( *p );

                if( p->location.first == MazeWidth-1)
                   p->dirright = 0; 

                if( p->location.second == MazeHeight-1)
                   p->dirdown = 0;   
                std::cout<<p->dirdown<<p->dirright<<std::endl;  
            }
       }
    srand( time(0) );
    int r{};
    for(int j{0}; j< MazeHeight ; j++)
        for(int i{0}; i< MazeWidth ; i++)
        {
            std::cout<<V[j][i].dirdown<<V[j][i].dirright<<std::endl; 
            //V[j][i].status =1;
            if(V[j][i].dirdown == 0 )
                V[j][i].neighbour = EAST;
            if(V[j][i].dirright == 0)
                V[j][i].neighbour = SOUTH;
            if(V[j][i].dirdown == 0 && V[j][i].dirright == 0 )
                V[j][i].neighbour = NONE ;
            else
            {
                r = rand() %2;
                if(r == 0 )
                    V[j][i].neighbour = EAST;
                if(r == 1 )
                    V[j][i].neighbour = SOUTH;  
            }  
        }
    //std::cout<<V[MazeHeight-1][MazeWidth-1].neighbour<<std::endl;
    //show(V);
}


// void Maze::check( std::vector<std::vector<Vertex>> V , int x , int y)
// {
//     V[y][x].status = 1;
//     if ( V[y][x].neighbour == EAST && V[y][x].dirright && !V[y][x+1].status)
//                 {
//                     grid[ XYToIndex(x , y) ] = ' ';
//                     check ( V , x+1 , y );
//                 }
//     if ( V[y][x].neighbour == SOUTH && V[y][x].dirdown && !V[y+1][x].status)
//                 {
//                     grid[ XYToIndex(x , y) ] = ' ';
//                     check ( V , x , y+1 );
//                 }
// }

void Maze::show( std::vector<std::vector<Vertex>> V )
{
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