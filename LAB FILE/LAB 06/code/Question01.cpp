// <----Lab 06 - Queues---->

// Q1. Write the definition of all the functions listed in Example 01.

#include <iostream>
using namespace std;

class Queue
{
private:
    int front, rear;
    unsigned capacity;
    int *array;

public:
    Queue(int capacity)
    {
        array = new int[capacity];
        front = -1;
        rear = -1;
        this->capacity = capacity;
    }

    bool isEmpty()
    {
        return (rear == -1 && front == -1);
    }

    bool isFull()
    {
        return ((rear + 1) % capacity == front);
    }

    void enqueue(int element)
    {
        if (isFull())
        {
            cerr << "Queue is full cannot enqueue." << endl;
            return;
        }
        else if (isEmpty())
        {
            front = rear = 0;
        }
        else
        {
            rear = (rear + 1) % capacity;
        }
        array[rear] = element;
        cout << array[rear] << " is enqueued in the queue." << endl;
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cerr << "Queue is Empty cannot dequeue." << endl;
            return;
        }
        else if (front == rear)
        {
            cout << array[front] << " is dequeued from the queue." << endl;
            rear = front = -1;
        }
        else
        {
            cout << array[front] << " is dequeued from the queue." << endl;
            front = (front + 1) % capacity;
        }
    }

    int peek()
    {
        if (isEmpty())
        {
            cerr << "Queue is empty." << endl;
        }
        return array[front];
    }

    int queue_size()
    {
        if (isEmpty())
            return 0;
        else if (rear >= front)
        {
            return rear - front + 1;
        }
        else
        {
            return (capacity - front + rear) % capacity;
        }
    }
};

int main()
{
    Queue q(10);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    q.enqueue(6);
    q.enqueue(7);
    q.enqueue(8);
    cout << "Front element " << q.peek() << endl;
    cout << "Size of queue " << q.queue_size() << endl;
    return 0;
}
