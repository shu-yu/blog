#ifndef _SUDOKUSOLVER_H_
#define _SUDOKUSOLVER_H_

#include "DLXSolver.h"

// offset
#define BOX_OFFSET      0
#define ROW_OFFSET      81
#define COL_OFFSET      162
#define PALACE_OFFSET   243

// Sudoku solver class
class SudokuSolver
{
public:
    // Constructor
    SudokuSolver(unsigned oMatrix[][9]);

    // Destructor
    ~SudokuSolver();

    // Solve the sudoku problem
    void Solve();

private:
    // Construct a row of the matrix
    void Set(std::vector<unsigned>& oRow, unsigned nMatrixBox,
        unsigned nMatrixRow, unsigned nMatrixCol, unsigned nMatrixPalace);

private:
    // The matrix used in DLXSolver
    std::vector<std::vector<unsigned> > m_oMatrix;

    // The DLXSolver pointer
    DLXSolver* pDLXSolver;

    // The answer of the sudoku problem
    std::vector<std::vector<unsigned> > m_oAnsMatrix;
};

#endif