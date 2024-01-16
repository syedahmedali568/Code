#include <iostream>
#include <stack>

using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};

Node *reverseSLL(Node *head)
{
    Node *temp = head;
    Node *prev = NULL;
    while (temp != NULL)
    {
        Node *front = temp->next;
        temp->next = prev;
        prev = temp;
        temp = front;
    }
    return prev;
}

void printList(Node *&head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main()
{
    Node *head = new Node(1);
    head->next = new Node(6);
    head->next->next = new Node(9);
    head->next->next->next = new Node(3);
    head->next->next->next->next = new Node(2);

    cout << "Original Linked List: ";
    printList(head);
    cout << "head :" << head->data << endl;

    head = reverseSLL(head);

    cout << "Reversed Linked List: ";
    printList(head);
    cout << "head :" << head->data << endl;
    return 0;
}
