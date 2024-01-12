// <----Lab 06 - Queues---->
#include <iostream>
#include "Queue.h"
using namespace std;

int main()
{
    Queue<int> *q = new Queue<int>(10);
    if (q->isEmpty())
    {
        cout << "Queue is empty." << endl;
    }
    q->Put(1);
    q->Put(2);
    q->Put(3);
    while (!q->isEmpty())
    {
        cout << q->Get() << endl;
    }
    return 0;
}