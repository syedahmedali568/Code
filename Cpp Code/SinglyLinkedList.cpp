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
    ~Node()
    {
        int value = this->data;
        if (this->next != NULL)
        {
            delete next;
            this->next = NULL;
        }
        cout << "memory is free for the data " << value << endl;
    }
};
void insertAtHead(Node *&head, int data)
{
    Node *temp = new Node(data);
    temp->next = head;
    head = temp;
}
void insertAtTail(Node *&tail, int data)
{
    Node *temp = new Node(data);
    tail->next = temp;
    tail = temp;
}
void print(Node *&head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void insertAtAnyPosition(Node *&head, Node *&tail, int position, int data)
{
    if (position == 1)
    {
        insertAtHead(head, data);
        return;
    }
    Node *temp = head;
    int cnt = 1;
    while (cnt < position - 1)
    {
        temp = temp->next;
        cnt++;
    }
    if (temp->next = NULL)
    {
        insertAtTail(tail, data);
        return;
    }
    Node *nodeToInsert = new Node(data);
    nodeToInsert->next = temp->next;
    temp->next = nodeToInsert;
}

void deleteNodeByValue(Node *&head, Node *&tail, int value)
{
    Node *curr = head;
    Node *prev = NULL;

    // Traverse the list to find the node with the specified value
    while (curr != NULL && curr->data != value)
    {
        prev = curr;
        curr = curr->next;
    }

    // If the value is not found
    if (curr == NULL)
    {
        cout << "Node with value " << value << " not found." << endl;
        return;
    }

    // If the node to be deleted is the first node
    if (prev == NULL)
    {
        head = curr->next;
        curr->next = NULL;
        delete curr;
    }
    else
    {
        prev->next = curr->next;
        curr->next = NULL;
        delete curr;
        tail = prev;
    }
}

void deleteNodeByPosition(Node *&head, int position)
{

    if (position == 1)
    {
        Node *temp = head;
        head = head->next;
        temp->next = NULL;
        delete temp;
    }
    else
    {
        Node *curr = head;
        Node *prev = NULL;
        int cnt = 1;
        while (cnt < position)
        {
            prev = curr;
            curr = curr->next;
            cnt++;
        }
        prev->next = curr->next;
        curr->next = NULL;
        delete curr;
    }
}

int getLength(Node *head)
{
    Node *temp = head;
    int len = 0;
    while (temp != NULL)
    {
        len++;
        temp = temp->next;
    }
    cout << endl;
    return len;
}

int main()
{
    Node *node1 = new Node(10);
    Node *head = node1;
    Node *tail = node1;

    insertAtHead(head, 12);
    print(head);

    insertAtTail(tail, 2);
    print(head);

    insertAtAnyPosition(head, tail, 1, 18);
    print(head);

    cout << "head :" << head->data << endl;
    cout << "tail :" << tail->data << endl;

    cout << "the length of the linkedlist is " << getLength(head) <<endl;

    deleteNodeByValue(head, tail, 2);
    print(head);

    cout << "head :" << head->data << endl;
    cout << "tail :" << tail->data << endl;

    cout << "the length of the linkedlist is " << getLength(head);

    return 0;
}