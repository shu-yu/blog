#include "SudokuSolver.h"
#include <iostream>

SudokuSolver::SudokuSolver(unsigned oMatrix[][9])
{
    unsigned nValue;
    unsigned nMatrixBox;
    unsigned nMatrixRow;
    unsigned nMatrixCol;
    unsigned nMatrixPalace;
    std::vector<unsigned> oMatrixRow(324);
    for (unsigned nRow = 0; nRow < 9; ++nRow)
    {
        for (unsigned nCol = 0; nCol < 9; ++nCol)
        {
            nValue = oMatrix[nRow][nCol];

            // the column number of the matrix representing current box
            nMatrixBox = nRow * 9 + nCol + BOX_OFFSET;
            // the column number of the matrix representing current row
            nMatrixRow = nRow * 9 + ROW_OFFSET;
            // the column number of the matrix representing current column
            nMatrixCol = nCol * 9 + COL_OFFSET;
            // the column number of the matrix representing current palace
            nMatrixPalace = (nRow / 3 * 3 + nCol / 3) * 9 + PALACE_OFFSET;

            // the box is empty
            if (0 == nValue)
            {
                // insert nine rows into the matrix representing nine possibilities
                for (unsigned nNum = 0; nNum < 9; ++nNum)
                {
                    Set(oMatrixRow, nMatrixBox, nMatrixRow + nNum, 
                        nMatrixCol + nNum, nMatrixPalace + nNum);
                    m_oMatrix.push_back(oMatrixRow);
                }
            }
            // the box is not empty
            else
            {
                // insert one row into the matrix
                --nValue;
                Set(oMatrixRow, nMatrixBox, nMatrixRow + nValue,
                    nMatrixCol + nValue, nMatrixPalace + nValue);
                m_oMatrix.push_back(oMatrixRow);
            }
        }
    }
}

SudokuSolver::~SudokuSolver()
{

}

void SudokuSolver::Solve()
{
    DLXSolver* pDLXSolver = new DLXSolver();
    std::vector<unsigned> oAnsVec = pDLXSolver->Solve(m_oMatrix, 324);
    
    if (oAnsVec.empty())
    {
        std::cout << "cannot find the solution of the problem" << std::endl;
        return;
    }

    unsigned nMatrixBox;
    unsigned nMatrixRow;
    unsigned nMatrixCol;
    unsigned nRow;
    unsigned nCol;
    unsigned nValue;

    // insert nine lines to the answer matrix
    for (unsigned nNum = 0; nNum < 9; ++nNum)
    {
        std::vector<unsigned> oTmpVec(9);
        m_oAnsMatrix.push_back(oTmpVec);
    }

    for (unsigned nNum = 0; nNum < oAnsVec.size(); ++nNum)
    {
        nMatrixBox = m_oMatrix[oAnsVec[nNum]][0];
        nMatrixRow = m_oMatrix[oAnsVec[nNum]][1];
        nMatrixCol = m_oMatrix[oAnsVec[nNum]][2];

        // mathematical way to calculate the column, the row and the value
        nCol = (nMatrixCol - nMatrixRow + nMatrixBox - 81) / 10;
        nRow = (nMatrixBox - nCol) / 9;
        nValue = nMatrixRow- nMatrixBox + nCol - 81;

        // update the answer
        m_oAnsMatrix[nRow][nCol] = nValue + 1;
    }

    // print the completed sudoku
    for (unsigned nRowNum = 0; nRowNum < 9; ++nRowNum)
    {
        for (unsigned nColNum = 0; nColNum < 9; ++nColNum)
        {
            std::cout << m_oAnsMatrix[nRowNum][nColNum] << " ";
            if (2 == nColNum || 5 == nColNum)
            {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;
    }
}

void SudokuSolver::Set(std::vector<unsigned>& oRowVec, unsigned nMatrixBox,
    unsigned nMatrixRow, unsigned nMatrixCol, unsigned nMatrixPalace)
{
    oRowVec.clear();

    oRowVec.push_back(nMatrixBox);
    oRowVec.push_back(nMatrixRow);
    oRowVec.push_back(nMatrixCol);
    oRowVec.push_back(nMatrixPalace);
}