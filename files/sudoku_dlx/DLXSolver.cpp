#include "DLXSolver.h"
#include <algorithm>
#include <iostream>

DLXSolver::DLXSolver()
{
    m_pRoot = NULL;
    m_nAns = 0;
}

std::vector<unsigned> DLXSolver::Solve( \
    std::vector<std::vector<unsigned> > oMatrix, unsigned nColCount)
{
    // construct the matrix
    ConstructMatrix(oMatrix, nColCount);

    // search for the solution
    if (Search(0))
    {
        m_oAnsVec.resize(m_nAns);
    }
    else
    {
        m_oAnsVec.clear();
    }
    
    return m_oAnsVec;
}

void DLXSolver::ConstructMatrix( \
    std::vector<std::vector<unsigned> > oMatrix, unsigned nColCount)
{
    // initialize the root
    m_pRoot = new Node(NULL, NULL, NULL, NULL, NULL, NULL);
    
    // initialize header of columns
    for (unsigned nColNum = 0; nColNum < nColCount; ++nColNum)
    {
        ColumnHeader* pNewColHeader = \
            new ColumnHeader(m_pRoot->GetNextNode(LEFT), m_pRoot, \
            NULL, NULL, NULL, NULL);
        m_pRoot->GetNextNode(LEFT)->SetNextNode(pNewColHeader, RIGHT);
        m_pRoot->SetNextNode(pNewColHeader, LEFT);
        m_oColHeaderVec.push_back(pNewColHeader);
    }

    // initialize header of rows and other nodes
    for (unsigned nRow = 0; nRow < oMatrix.size(); ++nRow)
    {
        if (oMatrix[nRow].empty())
        {
            continue;
        }

        std::vector<unsigned> oTmpVec(oMatrix[nRow]);
        std::sort(oTmpVec.begin(), oTmpVec.end());

        ColumnHeader* pTmpColHeader = m_oColHeaderVec[oTmpVec[0]];
        pTmpColHeader->IncreaseSize();

        RowHeader* pTmpRowHeader = \
            new RowHeader(nRow, NULL, NULL, pTmpColHeader->GetNextNode(UP), \
            pTmpColHeader, pTmpColHeader);
        pTmpColHeader->GetNextNode(UP)->SetNextNode(pTmpRowHeader, DOWN);
        pTmpColHeader->SetNextNode(pTmpRowHeader, UP);
        oTmpVec.erase(oTmpVec.begin());

        for (unsigned nNum = 0; nNum < oTmpVec.size(); ++nNum)
        {
            pTmpColHeader = m_oColHeaderVec[oTmpVec[nNum]];
            pTmpColHeader->IncreaseSize();

            Node* pTmpNode = \
                new Node(pTmpRowHeader->GetNextNode(LEFT), pTmpRowHeader, \
                pTmpColHeader->GetNextNode(UP), pTmpColHeader, pTmpColHeader, \
                pTmpRowHeader);
            pTmpColHeader->GetNextNode(UP)->SetNextNode(pTmpNode, DOWN);
            pTmpColHeader->SetNextNode(pTmpNode, UP);
            pTmpRowHeader->GetNextNode(LEFT)->SetNextNode(pTmpNode, RIGHT);
            pTmpRowHeader->SetNextNode(pTmpNode, LEFT);
        }
    }
}

void DLXSolver::Cover(ColumnHeader* pColHeader)
{
    // delete the header from horizontal direction
    Node* pLeft = pColHeader->GetNextNode(LEFT);
    Node* pRight = pColHeader->GetNextNode(RIGHT);
    pLeft->SetNextNode(pRight, RIGHT);
    pRight->SetNextNode(pLeft, LEFT);

    std::vector<Node*> oDownNodeVec = pColHeader->GetAdjNodes(DOWN);
    for (unsigned nDownNum = 0; nDownNum < oDownNodeVec.size(); ++nDownNum)
    {
        std::vector<Node*> oRightNodeVec = \
            oDownNodeVec[nDownNum]->GetAdjNodes(RIGHT);
        for (unsigned nRightNum = 0; nRightNum < oRightNodeVec.size(); \
            ++nRightNum)
        {
            Node* pNode = oRightNodeVec[nRightNum];
            ColumnHeader* pTmpColHeader = \
                dynamic_cast<ColumnHeader*>(pNode->GetNextNode(COL));
            pTmpColHeader->DecreaseSize();

            // delete nodes of the column from vertical direction
            Node* pUp = pNode->GetNextNode(UP);
            Node* pDown = pNode->GetNextNode(DOWN);
            pUp->SetNextNode(pDown, DOWN);
            pDown->SetNextNode(pUp, UP);
        }
    }
}

void DLXSolver::UnCover(ColumnHeader* pColHeader)
{
    std::vector<Node*> oUpNodeVec = pColHeader->GetAdjNodes(UP);
    for (unsigned nUpNum = 0; nUpNum < oUpNodeVec.size(); ++nUpNum)
    {
        std::vector<Node*> oLeftNodeVec = \
            oUpNodeVec[nUpNum]->GetAdjNodes(LEFT);
        for (unsigned nLeftNum = 0; nLeftNum < oLeftNodeVec.size(); \
            ++nLeftNum)
        {
            Node* pNode = oLeftNodeVec[nLeftNum];
            ColumnHeader* pTmpColHeader = \
                dynamic_cast<ColumnHeader*>(pNode->GetNextNode(COL));
            pTmpColHeader->IncreaseSize();

            // insert nodes of the column to the vertical direction
            Node* pUp = pNode->GetNextNode(UP);
            Node* pDown = pNode->GetNextNode(DOWN);
            pUp->SetNextNode(pNode, DOWN);
            pDown->SetNextNode(pNode, UP);
        }
    }

    // insert the header back to the horizontal direction
    Node* pLeft = pColHeader->GetNextNode(LEFT);
    Node* pRight = pColHeader->GetNextNode(RIGHT);
    pLeft->SetNextNode(pColHeader, RIGHT);
    pRight->SetNextNode(pColHeader, LEFT);
}

bool DLXSolver::Search(unsigned nDeep)
{
    // if there's no header, the solution is found
    if (m_pRoot->GetNextNode(RIGHT) == m_pRoot)
    {
        m_nAns = nDeep;
        return true;
    }

    std::vector<Node*> oTmpColHeaderVec = m_pRoot->GetAdjNodes(RIGHT);
    ColumnHeader* pTmpMinHeader = NULL;
    unsigned nMinSize = MAX_SIZE + 1;

    // get the column of minimum size
    for (unsigned nPos = 0; nPos < oTmpColHeaderVec.size(); ++nPos)
    {
        ColumnHeader* pTmpColHeader = \
            dynamic_cast<ColumnHeader*>(oTmpColHeaderVec[nPos]);
        if (pTmpColHeader->GetSize() < nMinSize)
        {
            nMinSize = pTmpColHeader->GetSize();
            pTmpMinHeader = pTmpColHeader;
        }
    }

    // cover the chosen column
    Cover(pTmpMinHeader);

    std::vector<Node*> oTmpDownNodeVec = pTmpMinHeader->GetAdjNodes(DOWN);
    for (unsigned nDownNum = 0; nDownNum < oTmpDownNodeVec.size(); ++nDownNum)
    {
        Node* pTmpNode = oTmpDownNodeVec[nDownNum];
        m_oAnsVec.resize(nDeep + 1);
        RowHeader* pTmpRowHeader = \
            dynamic_cast<RowHeader*>(pTmpNode->GetNextNode(ROW));
        m_oAnsVec[nDeep] = pTmpRowHeader->GetRowNumer();

        // cover related column
        std::vector<Node*> oTmpRightNodeVec = pTmpNode->GetAdjNodes(RIGHT);
        for (unsigned nRightNum = 0; nRightNum < oTmpRightNodeVec.size(); \
            ++nRightNum)
        {
            ColumnHeader* pTmpColHeader = \
                dynamic_cast<ColumnHeader*>( \
                oTmpRightNodeVec[nRightNum]->GetNextNode(COL));
            Cover(pTmpColHeader);
        }

        // search recursively
        if (Search(nDeep + 1))
        {
            return true;
        }

        // uncover related columns
        std::vector<Node*> oTmpLeftNodeVec = pTmpNode->GetAdjNodes(LEFT);
        for (unsigned nLeftNum = 0; nLeftNum < oTmpRightNodeVec.size(); \
            ++nLeftNum)
        {
            ColumnHeader* pTmpColHeader = \
                dynamic_cast<ColumnHeader*>( \
                oTmpLeftNodeVec[nLeftNum]->GetNextNode(COL));
            UnCover(pTmpColHeader);
        }
    }

    // uncover the chosen column
    UnCover(pTmpMinHeader);
    return false;
}