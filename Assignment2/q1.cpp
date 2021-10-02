#include <bits/stdc++.h>
using namespace std;
template <typename T>
class Node
{
public:
    T data;
    int height;
    Node *left;
    Node *right;
    Node(T data)
    {
        this->data = data;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
};
template <class T>
class AVLTree
{
public:
    Node<T> *root;
    AVLTree()
    {
        root = nullptr;
    }
    int getHeight(Node<T> *node)
    {
        if (node == nullptr)
            return 0;
        else
            return node->height;
    }
    void calculateHeight(Node<T> *node)
    {
        node->height = 1 + max(getHeight(node->left),
                               getHeight(node->right));
    }
    Node<T> *rightRotate(Node<T> *node)
    {
       
        Node<T> *temp = node->left;
        node->left = node->left->right;
        temp->right = node;
        calculateHeight(node);
        calculateHeight(temp);
        return temp;
    }
    Node<T> *leftRotate(Node<T> *node)
    {
        Node<T> *temp = node->right;
        node->right = node->right->left;
        temp->left = node;
        calculateHeight(node);
        calculateHeight(temp);
        return temp;
    }
    Node<T> *rightleftRotate(Node<T> *node)
    {
        // if (node->right)
        // {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        // }
    }
    Node<T> *leftRightRotate(Node<T> *node)
    {
        // if (node->left)
        // {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        // }
    }
    
    int getBalanceFactor(Node<T> *node)
    {
        return (getHeight(node->left) - getHeight(node->right));
    }
    Node<T> *insert(Node<T> *node, T data)
    {
        if (!node)
        {
            return new Node<T>(data);
        }
        if (data <= node->data)
        {
            node->left = insert(node->left, data);
        }
        else
        {
            node->right = insert(node->right, data);
        }
        calculateHeight(node);
        int bf = getBalanceFactor(node);
        if (bf > 1 && data <= node->left->data)
        {
            return rightRotate(node);
        }
        else if (bf > 1 && data > node->left->data)
        {
            return leftRightRotate(node);
        }
        else if (bf < -1 && data <= node->right->data)
        {
            return rightleftRotate(node);
              
        }
        else if (bf < -1 && data > node->right->data)
        {
            return leftRotate(node);
        }
        return node;
    }
};
int main()
{
    AVLTree<int> *tree = new AVLTree<int>();
    while (1)
    {
        cout << "1.Insert 10.exit\n";
        int option;
        cin >> option;
        int val;
        switch (option)
        {
        case 1:
            cout << "Enter value: ";
            cin >> val;
            tree->root = tree->insert(tree->root, val);
            break;
        case 10:
            return 0;
            break;
        }
    }
}