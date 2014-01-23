#include <iostream>
#include "COperationStack.cpp.h"
using namespace std;

int main()
{
    COperationStack<int> oOperStack(3);
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    int f = 6;
    cout << *oOperStack.Do(&a) << endl;
    cout << *oOperStack.GetCurrentOperation() << endl;
    cout << *oOperStack.Do(&b) << endl;
    cout << *oOperStack.GetCurrentOperation() << endl;
    cout << *oOperStack.Do(&c) << endl;
    cout << *oOperStack.GetCurrentOperation() << endl;
    cout << *oOperStack.Do(&d) << endl;
    cout << *oOperStack.GetCurrentOperation() << endl;
    cout << *oOperStack.Do(&e) << endl;
    cout << *oOperStack.GetCurrentOperation() << endl;
    cout << *oOperStack.Undo() << endl;
    cout << *oOperStack.GetCurrentOperation() << endl;
    cout << *oOperStack.Undo() << endl;
    cout << *oOperStack.GetCurrentOperation() << endl;
    cout << *oOperStack.Do(&f) << endl;
    cout << *oOperStack.GetCurrentOperation() << endl;
    cout << *oOperStack.Redo() << endl;
    cout << *oOperStack.GetCurrentOperation() << endl;
    cout << *oOperStack.Redo() << endl;
    cout << *oOperStack.GetCurrentOperation() << endl;

    return 0;
}
