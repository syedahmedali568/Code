#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

Node *insertIntoBST(Node *root, int data)
{
    if (root == NULL)
    {
        root = new Node(data);
        return root;

        if (data < root->data)
        {
            root->left = insertIntoBST(root->left, data);
        }
        else
        {
            root->right = insertIntoBST(root->right, data);
        }
    }
    return root;
}

void takeInput(Node *&root)
{

    int data;
    cin >> data;
    while (data != -1)
    {
        root = insertIntoBST(root, data);
        cin >> data;
    }
}

int main()
{
    Node *root = NULL;

    cout << "Enter data to creat BST" << endl;

    takeInput(root);

    

    return 0;
}