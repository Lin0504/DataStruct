#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<stack>
#include<assert.h>
using namespace std;

struct Pos
{
           int _row;
           int _col;
};

inline bool CheckIsAccess(int * maze, int n, Pos pos)
{
           if (pos ._col < n && pos._row < n && maze[ pos._row * 10 + pos._col] == 0)
          {
                    return true ;
          }
           return false ;
}

void InitMaze(int * maze, size_t n )
{
           assert(maze );
           FILE* p = fopen("maze.txt" , "r");
           assert(p);
           for (int i = 0; i < n; ++i)
          {
                    for (int j = 0; j < n;)
                   {
                              char ch = fgetc(p);
                              if (ch == '0' || ch == '1')
                             {
                                       maze[i*n + j] = ch - '0';
                                      ++j;
                             }
                   }

          }
          fclose(p);
}

void PrintMaze(int *maze)
{
           for (int i = 0; i < 10; ++i)
          {
                    for (int j = 0; j < 10;)
                   {
                              if (maze [i * 10 + j] == 0 || maze[i * 10 + j] == 1||maze[i*10+j]==2)
                             {
                                      cout << maze[i * 10 + j] << " " ;
                             }
                             ++j;
                   }
                   cout << endl;
          }
}
bool Maze(int *maze, int n , Pos entry, stack<Pos >& path)
{
           assert(maze );
           path.push(entry );
    maze[ entry._row*n + entry._col] = 2;

           while (!path .empty())
          {
                    Pos cur = path .top();
                    Pos next = cur;
                   next._row--;
                    if (CheckIsAccess(maze ,n,next))
                   {
                              maze[next._row*n + next._col] = 2;
                              path.push(next);
                              continue;
                   }
                   next = cur;
                   next._row++;
                    if (CheckIsAccess(maze , n, next))
                   {
                              maze[next._row*n + next._col] = 2;
                              path.push(next);
                              continue;
                   }
                   next = cur;
                   next._col--;
                    if (CheckIsAccess(maze , n, next))
                   {
                              maze[next._row*n + next._col] = 2;
                              path.push(next);
                              continue;
                   }

                   next = cur;
                   next._col++;
                    if (CheckIsAccess(maze , n, next))
                   {

                              path.push(next);
                              maze[next._row*n + next._col] = 2;

                              continue;
                   }

                    path.pop();
          }
           return false ;

}

int main()
{
           int maze[10][10];
          InitMaze(( int*)maze, 10);
          PrintMaze(( int*)maze);
          cout <<endl;
           Pos pos = { 1, 0 };
           stack<Pos > path;
          Maze(( int*)maze, 10, pos, path);
          PrintMaze(( int*)maze);
          getchar();
           return 0;
}
