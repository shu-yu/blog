/**
 * COperationStack.h definition of operation stack class
 *
 * @author: SHUYUFANG
 */

#ifndef _COPEATIONS_STACK_H
#define _COPEATIONS_STACK_H

#include <deque>

/**
 * operation stack class
 */
template <typename T>
class COperationStack
{
public:
    /**
     * constructor
     * @param: the maximum size of the operation stack
     */
    COperationStack(unsigned);

    /**
     * copy constructor
     * @param: the existed operation stack object
     */
    COperationStack(const COperationStack<T>&);

    /**
     * destructor
     */
    ~COperationStack();

    /**
     * assignment operator
     * @param: the existed operation stack object
     * @return: current object
     */
    COperationStack& operator=(const COperationStack<T>&);

    /**
     * perform a new operation
     * @param: the new operation
     * @return: the new operation
     */
    T* Do(T*);

    /**
     * undo last operation
     * @return: last operation
     */
    T* Undo();

    /**
     * redo next operation
     * @return: next operation
     */
    T* Redo();

    /**
     * get current operation
     * @return: current operation
     */
    T* GetCurrentOperation();

private:
    /**
     * clear the stack
     */
    void ClearStack();

    /**
     * copy the existed stack
     * @param: the existed stack
     */
    void CopyStack(std::deque<T*>);

private:
    /**
     * the maximum size of the stack
     */
    unsigned m_nSize;

    /**
     * the stack
     */
    std::deque<T*> m_oStack;

    /**
     * position of current operation in the stack
     */
    unsigned m_nCurPos;
};

#endif
