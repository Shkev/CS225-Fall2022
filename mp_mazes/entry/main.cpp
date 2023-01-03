#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;
using namespace cs225;

int main()
{
    SquareMaze s;
    s.makeMaze(30, 30);
    PNG* unsolved = s.drawMaze();
    unsolved->writeToFile("../unsolved.png");
    delete unsolved;
    PNG* solved = s.drawMazeWithSolution();
    solved->writeToFile("../soln.png");
    delete solved;
    return 0;
}
