#include "SudokuSolver.h"
#include <iostream>

int main(int argc, char** argv)
{
    unsigned oSudokuArr[9][9] = 
    {
        {0, 0, 0,  0, 1, 3,  4, 0, 0},
        {0, 8, 0,  0, 0, 6,  9, 5, 0},
        {6, 5, 0,  0, 0, 0,  0, 0, 0},

        {9, 6, 0,  2, 0, 1,  0, 0, 0},
        {1, 0, 0,  0, 7, 0,  0, 0, 2},
        {0, 0, 0,  3, 0, 4,  0, 1, 6},
        
        {0, 0, 0,  0, 0, 0,  0, 7, 9},
        {0, 2, 5,  8, 0, 0,  0, 4, 0},
        {0, 0, 9,  7, 6, 0,  0, 0, 0}
    };

    SudokuSolver* pSudokuSolver = new SudokuSolver(oSudokuArr);
    pSudokuSolver->Solve();

    return 0;
}
