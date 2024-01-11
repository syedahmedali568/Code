#include <iostream>
using namespace std;

class MinHeap
{
public:
    int array[100];
    int size;
    MinHeap()
    {
        array[0] = -1;
        size = 0;
    }
    void insert(int value)
    {
        size = size + 1;
        int index = size;
        array[index] = value;
        while (index > 1)
        {
            int parent = index / 2;
            if (array[parent] > array[index])
            {
                swap(array[index], array[parent]);
                index = parent;
            }
            else
            {
                return;
            }
        }
    }
    void print()
    {
        for (int i = 1; i <= size; i++)
        {
            cout << array[i] << " ";
        }
        cout << endl;
    }
    void deleteFromHeap()
    {
        if (size == 0)
        {
            cout << "Nothing to delete";
            return;
        }
        // put the value of last node in the first node
        array[1] = array[size];
        // deleting the Node
        size--;
        // getting root to its correct position for satisfying heap property
        int index = 1;
        while (index < size)
        {
            int leftIndex = 2 * index;
            int rightIndex = 2 * index + 1;
            if (leftIndex < size && leftIndex < array[index])
            {
                swap(array[index], array[leftIndex]);
                index = leftIndex;
            }
            else if (rightIndex < size && rightIndex < array[index])
            {
                swap(array[index], array[rightIndex]);
                index = rightIndex;
            }
            else
            {
                return;
            }
        }
    }
};

int main()
{
    MinHeap h;
    h.insert(60);
    h.insert(90);
    h.insert(40);
    h.insert(70);
    h.insert(50);
    h.print();
    h.deleteFromHeap();
    h.deleteFromHeap();
    h.print();

    return 0;
}