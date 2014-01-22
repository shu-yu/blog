#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include <string>

// Directions
#define LEFT    "left"
#define RIGHT   "right"
#define UP      "up"
#define DOWN    "down"
#define COL     "col"
#define ROW     "row"

const int MAX_SIZE = 1000;

// Node class
class Node
{
public:
    // Constructor
    Node(Node* pLeft, Node* pRight, Node* pUp, Node* pDown, \
        Node* pColHeader, Node* pRowHeader);

    // Destructor
    virtual ~Node();

    // Get nodes of specified direction (left, right, up, down)
    std::vector<Node*> GetAdjNodes(const std::string sDirection);

    // Get the node next to current one of specified direction 
    // (left, right, up, down, column header, row header)
    Node* GetNextNode(const std::string sDirection) const;

    // Set the next node of specified direction
    void SetNextNode(Node* pNode, const std::string sDirection);

protected:
    // Pointer to the left node
    Node* m_pLeft;

    // Pointer to the right node
    Node* m_pRight;

    // Pointer to the up node
    Node* m_pUp;

    // Pointer to the down node
    Node* m_pDown;

    // Pointer to the column header node
    Node* m_pColHeader;

    // Pointer to the row header node
    Node* m_pRowHeader;
};


class RowHeader;

// Column header class
class ColumnHeader : public Node
{
public:
    // Constructor
    ColumnHeader(Node* pLeft, Node* pRight, Node* pUp, Node* pDown, \
        ColumnHeader* pColHeader, RowHeader* pRowHeader);

    // Destructor
    ~ColumnHeader();

    // Get size of current column
    unsigned GetSize() const;

    // Increase size of current column by one
    void IncreaseSize();

    // Decrease size of current column by one
    void DecreaseSize();

private:
    // The size of current column
    unsigned m_nSize;
};

// Row header class
class RowHeader : public Node
{
public:
    // Constructor
    RowHeader(unsigned nRowNumber, Node* pLeft, Node* pRight, \
        Node* pUp, Node* pDown, ColumnHeader* pColHeader);

    // Destructor
    ~RowHeader();

    // Get the number of current row
    unsigned GetRowNumer() const;

private:
    // The number of current row
    unsigned m_nRowNumber;
};

#endif