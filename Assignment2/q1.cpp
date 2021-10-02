#include <iostream>
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
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    Node<T> *leftRightRotate(Node<T> *node)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
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
    Node<T> *minVal(Node<T> *node)
    {
        Node<T> * temp = node;
        while (temp->left || temp->right)
        {
            if (temp->left)
                temp = temp->left;
            else
                temp = temp->right;
        }
        return temp;
    }
    Node<T> *deleteNode(Node<T> *node, T data)
    {
        if (!node)
            return nullptr;
        if (data < node->data)
        {
            node->left = deleteNode(node->left, data);
        }
        else if (data > node->data)
        {
            node->right = deleteNode(node->right, data);
        }
        else
        {
            if (!node->left && !node->right)
            {
                delete node;
                return nullptr;
            }
            if (!node->left)
            {
                Node<T> *temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right)
            {
                Node<T> *temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                Node<T> *minValptr = minVal(node->right);
                node->data = minValptr->data;
                node->right = deleteNode(node->right, minValptr->data);
            }
        }
        calculateHeight(node);
        int bf = getBalanceFactor(node);
        if (bf > 1 && getBalanceFactor(node->left) > 0)
        {
            return rightRotate(node);
        }
        else if (bf > 1 && getBalanceFactor(node->left) < 0)
        {
            return leftRightRotate(node);
        }
        else if (bf < -1 && getBalanceFactor(node->right) > 0)
        {
            return rightleftRotate(node);
        }
        else if (bf < -1 && data > getBalanceFactor(node->right) < 0)
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
        case 2:
            cout << "Enter value: ";
            cin >> val;
            tree->root = tree->deleteNode(tree->root, val);
            break;
        case 10:
            return 0;
            break;
        }
    }
}