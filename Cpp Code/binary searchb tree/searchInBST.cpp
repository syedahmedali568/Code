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

Node *minValue(Node *root)
{
    Node *temp = root;
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

Node *deletefromBST(Node *root, int val)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->data == val)
    {
        // 0
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }

        // 1
        // left
        if (root->left != NULL && root->right == NULL)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        // right
        if (root->left == NULL && root->right != NULL)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }

        // 2
        if (root->left != NULL && root->right != NULL)
        {
            Node *temp = minValue(root->right);
            root->data = temp->data;
            root->right = deletefromBST(root->right, temp->data);
            return root;
        }
    }
    else if (root->data > val)
    {
        root->left = deletefromBST(root->left, val);
        return root;
    }
    else
    {
        root->right = deletefromBST(root->right, val);
        return root;
    }
}

bool searchInBST(Node *root, int key)
{
    // Base case: if the root is null, the key is not present
    if (root == NULL)
    {
        return false;
    }

    // If the key is equal to the current node's data, the key is found
    if (root->data == key)
    {
        return true;
    }

    // If the key is less than the current node's data, search in the left subtree
    if (key < root->data)
    {
        return searchInBST(root->left, key);
    }
    // If the key is greater than the current node's data, search in the right subtree
    else
    {
        return searchInBST(root->right, key);
    }
}

int main()
{
    // Example usage
    Node *root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->left = new Node(3);
    root->left->right = new Node(7);
    root->right->left = new Node(12);
    root->right->right = new Node(18);

    int key;
    cout << "Enter key to search in the BST: ";
    cin >> key;

    if (searchInBST(root, key))
    {
        cout << key << " found in the BST." << endl;
    }
    else
    {
        cout << key << " not found in the BST." << endl;
    }

    // Deleting a node with value 5
    root = deletefromBST(root, 5);

    return 0;
}
