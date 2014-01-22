---
layout: post
title: 使用DLX算法解数独
datetime: 2014-01-22 13:47
tags: cpp, algorithm
---
   
{{ page.title }}
================

<h5>双向十字链表</h5>
   
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
   
 
<h5>精确覆盖问题</h5>
   


4、若剩下的矩阵只有一行，且元素全部是1，则选择该行加入解集中，当前解集中的行数就是所求的一个解。否则回溯到上一个矩阵，选择其他的行，继续求解过程。   

5、如果回溯完所有的行之后仍无法找到解，说明该问题无解。   

如果把上述的矩阵看成一个双向十字链表，每一个元素代表一个结点，那么上述过程的行和列的删除和恢复都会变成非常简单。对于删除行或列的操作，我们都可以利用“伪删除”。对于回溯，我们只需要把结点放回原来的位置即可。

详细过程可以参考一下这篇文章：[跳跃的舞者，舞蹈链（Dancing Links）算法——求解精确覆盖问题](http://www.cnblogs.com/grenet/p/3145800.html)   


<h5>代码</h5>   

我用C++对DLX算法作了封装，并且在此基础上写了个解数独的类，代码如下：   
+ [Node.h](http://www.onlyan.org/files/sudoku_dlx/Node.h)结点类声明   
+ [Node.cpp](http://www.onlyan.org/files/sudoku_dlx/Node.cpp) 结点类实现   
+ [DLXSolver.h](http://www.onlyan.org/files/sudoku_dlx/DLXSolver.h) 舞蹈链类声明   
+ [DLXSolver.cpp](http://www.onlyan.org/files/sudoku_dlx/DLXSolver.cpp) 舞蹈链类实现   
+ [SudokuSolver.h](http://www.onlyan.org/files/sudoku_dlx/SudokuSolver.h) 解数独类声明   
+ [SudokuSolver.cpp](http://www.onlyan.org/files/sudoku_dlx/SudokuSolver.cpp) 解数独类实现   
+ [main.cpp](http://www.onlyan.org/files/sudoku_dlx/main.cpp) 主测试函数   


