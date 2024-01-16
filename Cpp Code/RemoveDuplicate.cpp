#include <iostream>

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

Node *uniqueSortedSLL(Node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    Node *curr = head;
    while (curr != NULL)
    {
        if ((curr->next != NULL) && curr->data == curr->next->data)
        {
            Node *next_next = curr->next->next;
            Node *nodeToDelete = curr->next;
            delete nodeToDelete;
            curr->next = next_next;
        }
        else
        {
            curr = curr->next;
        }
    }
    return head;
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
    head->next = new Node(2);
    head->next->next = new Node(2);
    head->next->next->next = new Node(3);
    head->next->next->next->next = new Node(3);
    head->next->next->next->next->next = new Node(4);

    cout << "Original Linked List: ";
    printList(head);
    cout << "head :" << head->data << endl;

    uniqueSortedSLL(head);
    printList(head);
    cout << "head :" << head->data << endl;

    return 0;
}
