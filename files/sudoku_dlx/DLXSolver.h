#ifndef _DLXSOLVER_H_
#define _DLXSOLVER_H_

#include "Node.h"

// Dancing Links X solver class
class DLXSolver
{
public:
    // Constructor
    DLXSolver();

    // Destructor
    ~DLXSolver();

    // Solve the problem
    std::vector<unsigned> Solve( \
        std::vector<std::vector<unsigned> > oMatrix, unsigned nColCount);

private:
    // Construct the matrix used in the process of solving the problem
    void ConstructMatrix(std::vector<std::vector<unsigned> > oMatrix, \
        unsigned nColCount);

    // The process of covering a column
    void Cover(ColumnHeader* pColHeader);

    // THe process of uncovering a column
    void UnCover(ColumnHeader* pColHeader);

    // Search for solution
    bool Search(unsigned nDeep);

private:
    // The number of chosen rows
    unsigned m_nAns;

    // The array of chosen row number
    std::vector<unsigned> m_oAnsVec;
    
    // The root of dancing links
    Node* m_pRoot;

    // The array of headers of dancing links
    std::vector<ColumnHeader*> m_oColHeaderVec;
};

#endif