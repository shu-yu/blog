#include "Node.h"
#include <iostream>

Node::Node(Node* pLeft, Node* pRight, Node* pUp, Node* pDown, \
           Node* pColHeader, Node* pRowHeader)
{
    m_pLeft = pLeft ? pLeft : this;
    m_pRight = pRight ? pRight : this;
    m_pUp = pUp ? pUp : this;
    m_pDown = pDown ? pDown : this;
    m_pColHeader = pColHeader ? pColHeader : this;
    m_pRowHeader = pRowHeader ? pRowHeader : this;    
}

Node::~Node()
{
}

Node* Node::GetNextNode(const std::string sDirection) const
{
    if (0 == sDirection.compare(LEFT))
    {
        return m_pLeft;
    }
    else if (0 == sDirection.compare(RIGHT))
    {
        return m_pRight;
    }
    else if (0 == sDirection.compare(UP))
    {
        return m_pUp;
    }
    else if (0 == sDirection.compare(DOWN))
    {
        return m_pDown;
    }
    else if (0 == sDirection.compare(COL))
    {
        return m_pColHeader;
    }
    else if (0 == sDirection.compare(ROW))
    {
        return m_pRowHeader;
    }

    return NULL;
}

void Node::SetNextNode(Node* pNode, const std::string sDirection)
{
    if (0 == sDirection.compare(LEFT))
    {
        m_pLeft = pNode;
    }
    else if (0 == sDirection.compare(RIGHT))
    {
        m_pRight = pNode;
    }
    else if (0 == sDirection.compare(UP))
    {
        m_pUp = pNode;
    }
    else if (0 == sDirection.compare(DOWN))
    {
        m_pDown = pNode;
    }
    else if (0 == sDirection.compare(COL))
    {
        m_pColHeader = pNode;
    }
    else if (0 == sDirection.compare(ROW))
    {
        m_pRowHeader = pNode;
    }
}

std::vector<Node*> Node::GetAdjNodes(const std::string sDirection)
{
    std::vector<Node*> oNodeVec;

    Node* pCurNode = this;
    Node* pNextNode = pCurNode->GetNextNode(sDirection);
    while (pNextNode != pCurNode)
    {
        oNodeVec.push_back(pNextNode);
        pNextNode = pNextNode->GetNextNode(sDirection);
    }

    return oNodeVec;
}


ColumnHeader::ColumnHeader(Node* pLeft, Node* pRight, Node* pUp, \
    Node* pDown, ColumnHeader* pColHeader, RowHeader* pRowHeader) : \
    Node(pLeft, pRight, pUp, pDown, pColHeader, pRowHeader)
{
    m_nSize = 0;
}

ColumnHeader::~ColumnHeader()
{

}

unsigned ColumnHeader::GetSize() const
{
    return m_nSize;
}

void ColumnHeader::IncreaseSize()
{
    if (m_nSize < MAX_SIZE)
    {
        ++m_nSize;
    }
}

void ColumnHeader::DecreaseSize()
{
    if (m_nSize > 0)
    {
        --m_nSize;
    }    
}


RowHeader::RowHeader(unsigned nRowNumber, Node* pLeft, Node* pRight, \
    Node* pUp, Node* pDown, ColumnHeader* pColHeader) : \
    Node(pLeft, pRight, pUp, pDown, pColHeader, NULL)
{
    m_nRowNumber = nRowNumber;
    m_pRowHeader = this;
}

RowHeader::~RowHeader()
{

}

unsigned RowHeader::GetRowNumer() const
{
    return m_nRowNumber;
}