Title: 使用DLX算法解数独
Date: 2014-01-14 20:07
Category: C++
Tags: 数独, DLX
Slug: sudoku-dlx
Author: Onlyan


   
双向十字链表
============
   
链表是一种很常见的数据结构，大学的时候学过单向链表、双向链表、循环链表等。所谓双向十字链表，就是在水平与垂直方向上同时存在双向循环链表，其中每个结点至少包含上下左右四个指针，分别指向上下左右四个方向的邻接结点。双向十字链表还有一个比较有艺术气息的名称：Dancing links舞蹈链。
   
对于双向循环链表，如果有三个连续的结点A <--> B <--> C，它们之间的关系是：   
A->next == B   
B->prev == A   
B->next == C   
C->prev == B   
   
如果能获取到结点B，那么将结点B从链表中删除的操作非常简单：   
B->prev->next = B->next   
B->next->prev = B->prev   
   
将B重新放回原来的位置的操作也非常简单：   
B->prev->next = B   
B->next->prev = B    
   
之所以可以这么简单的将B放回原来的位置，是因为删除操作只是改变了B的前置结点与后置结点的指针，而自己的指针没有变化，因此只需要重新改变前置结点与后置结点的指针就可以了。   
   
我觉得这种删除操作可以称为“伪删除”，这种伪删除操作同样可以应用在双向十字链表中。   
   
从双向十字链表中删除结点B：   
B->left->right = B->right   
B->right->left = B->left   
B->up->down = B->down   
B->down->up = B->up   
   
将结点B放回原来的位置：   
B->left->right = B   
B->right->left = B   
B->up->down = B   
B->down->up = B   
   
   
      
精确覆盖问题
============
   
如果有这样一个01矩阵：   
0 1 0 1 0   
1 1 0 0 1   
1 0 0 1 0   
1 0 1 0 1   
1 0 0 0 0   
   
现在需要从矩阵中抽取出部分行，使这些行构成一个新的矩阵，新矩阵必须满足每一列仅有一个1。   
   
这个问题就是精确覆盖问题的一种表述，解决问题的方法应该不少，比如暴力搜索就可以解决，但是时间效率方面可能不太理想。   
   
Knuth针对这个问题提出了一种X算法，解决的过程可以参考一下这篇文章：[跳跃的舞者，舞蹈链（Dancing Links）算法——求解精确覆盖问题](http://www.cnblogs.com/grenet/p/3145800.html)   
   
我用C++对DLX算法作了封装，并且在此基础上写了个解数独的类，代码如下：   
 (1) [Node.h](./files/sudoku_dlx/Node.h)结点类声明   
 (2) [Node.cpp](./files/sudoku_dlx/Node.cpp) 结点类实现  
 (3) [DLXSolver.h](./files/sudoku_dlx/DLXSolver.h) 舞蹈链类声明  
 (4) [DLXSolver.cpp](./files/sudoku_dlx/DLXSolver.cpp) 舞蹈链类实现  
 (5) [SudokuSolver.h](./files/sudoku_dlx/SudokuSolver.h) 解数独类声明  
 (6) [SudokuSolver.cpp](./files/sudoku_dlx/SudokuSolver.cpp) 解数独类实现  
 (7) [main.cpp](./files/sudoku_dlx/main.cpp) 主测试函数  


