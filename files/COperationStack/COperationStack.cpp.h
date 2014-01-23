/**
 * COperationStack.cpp.h Realization of operation stack class
 *
 * @author: SHUYUFANG
 */

#ifndef _COPERATION_STACK_CPP_H
#define _COPERATION_STACK_CPP_H

#include "COperationStack.h"

template <typename T>
COperationStack<T>::COperationStack(unsigned nSize)
{
    m_nSize = nSize == 0 ? 1 : nSize;
    m_nCurPos = -1;
}

template <typename T>
COperationStack<T>::COperationStack(const COperationStack<T>& oOperStack)
{
    m_nSize = oOperStack.m_nSize;
    CopyStack(oOperStack.m_oStack);
    m_nCurPos = oOperStack.m_nCurPos;
}

template <typename T>
COperationStack<T>::~COperationStack()
{
    ClearStack();
}

template <typename T>
void COperationStack<T>::ClearStack()
{
    for (unsigned i = 0; i < m_oStack.size(); ++i)
    {
        if (m_oStack[i])
        {
            delete m_oStack[i];
            m_oStack[i] = NULL;
        }
    }
    m_oStack.clear();
}

template <typename T>
void COperationStack<T>::CopyStack(std::deque<T*> oStack)
{
    ClearStack();

    for (unsigned i = 0; i < oStack.size(); ++i)
    {
        if (oStack[i])
        {
            m_oStack.push_back(new T(oStack[i]));
        }
    }
}

template <typename T>
T* COperationStack<T>::Do(T* pAction)
{
    if (!pAction)
    {
        return NULL;
    }

    if (m_nCurPos == m_nSize - 1)
    {
        if (m_oStack.front())
        {
            delete m_oStack.front();
            m_oStack.front() = NULL;

        }
        m_oStack.pop_front();
        --m_nCurPos;
    }
    else
    {
        while (m_oStack.size() > m_nCurPos + 1)
        {
            if (m_oStack.back())
            {
                delete m_oStack.back();
                m_oStack.back() = NULL;
            }
            m_oStack.pop_back();
        }
    }

    m_oStack.push_back(pAction);
    ++m_nCurPos;

    return pAction;
}

template <typename T>
T* COperationStack<T>::Undo()
{
    unsigned nStackSize = m_oStack.size();

    if (0 == nStackSize)
    {
        return NULL;
    }

    if (0 == m_nCurPos)
    {
        return m_oStack[0];
    }

    return m_oStack[--m_nCurPos];
}

template <typename T>
T* COperationStack<T>::Redo()
{
    unsigned nStackSize = m_oStack.size();

    if (0 == nStackSize)
    {
        return NULL;
    }

    if (m_nCurPos == nStackSize - 1)
    {
        return m_oStack[m_nCurPos];
    }

    return m_oStack[++m_nCurPos];
}

template <typename T>
T* COperationStack<T>::GetCurrentOperation()
{
    unsigned nStackSize = m_oStack.size();

    if (0 == nStackSize)
    {
        return NULL;
    }

    return m_oStack[m_nCurPos];
}

template <typename T>
COperationStack<T>& COperationStack<T>::operator=(const COperationStack<T>& oOperStack)
{
    m_nSize = oOperStack.m_nSize;
    CopyStack(oOperStack.m_oStack);
    m_nCurPos = oOperStack.m_nCurPos;

    return *this;
}

#endif
