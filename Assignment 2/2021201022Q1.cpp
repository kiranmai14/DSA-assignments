#include <iostream>
#include <string>
using namespace std;
class student
{
public:
    int age;
    string name;
    // student(int age, string name)
    // {
    //     this->age = age;
    //     this->name = name;
    // }
};
template <typename T>
class Node
{
public:
    T data;
    int count;
    int height;
    Node *left;
    Node *right;
    Node(T data)
    {
        this->data = data;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
        this->count = 1;
    }
};

bool operator>=(student a, student b)
{
    return (a.age == b.age);
}
bool operator==(student a, student b)
{
    return (a.age == b.age);
}
bool operator<(student a, student b)
{
    return (a.age < b.age);
}
bool operator<=(student a, student b)
{
    return (a.age <= b.age);
}
bool operator>(student a, student b)
{
    return (a.age > b.age);
}
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
        if (data == node->data)
        {
            node->count++;
            return node;
        }
        if (data < node->data)
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
        Node<T> *temp = node;
        while (temp->left)
        {
            temp = temp->left;
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
                node->count = minValptr->count;
                // minValptr->count = 1;
                node->right = deleteNode(node->right, minValptr->data);
            }
        }
        calculateHeight(node);
        int bf = getBalanceFactor(node);
        if (bf > 1 && getBalanceFactor(node->left) >= 0)
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
        else if (bf < -1 && getBalanceFactor(node->right) <= 0)
        {
            return leftRotate(node);
        }
        return node;
    }
    Node<T> *search(Node<T> *node, T data)
    {
        if (!node)
        {
            return nullptr;
        }
        if (data == node->data)
        {
            return node;
        }
        if (data < node->data)
        {
            return search(node->left, data);
        }
        else
        {
            return search(node->right, data);
        }
    }
    void count(Node<T> *node, T data)
    {
        Node<T> *temp = this->search(node, data);
        if (temp)
            cout << temp->count << "\n";
        else
            cout << "Element not found\n";
    }
    Node<T> *lowerBound(Node<T> *node, T data)
    {
        if (!node)
            return nullptr;
        if (node->data == data)
        {
            return node;
        }
        if (data < node->data)
        {
            Node<T> *left = lowerBound(node->left, data);
            if (!left)
                return node;
            else
                return left;
        }
        else
        {
            Node<T> *right = lowerBound(node->right, data);
            if (!right)
                return nullptr;
            else
                return right;
        }
    }
    Node<T> *upperBound(Node<T> *node, T data)
    {
        if (!node)
            return nullptr;
        if (data >= node->data)
        {
            Node<T> *right = upperBound(node->right, data);
            if (!right)
                return nullptr;
            else
                return right;
        }
        else
        {
            Node<T> *left = upperBound(node->left, data);
            if (!left)
                return node;
            else
                return left;
        }
    }
    Node<T> *closestElement(Node<T> *node, T data)
    {
        if (!node)
            return nullptr;
        if (data == node->data)
        {
            return node;
        }
        if (data > node->data)
        {
            Node<T> *right = closestElement(node->right, data);
            if (!right)
                return node;
            else
            {
                if (abs(data - node->data) <= abs(data - right->data))
                    return node;
                else
                    return right;
            }
        }
        else
        {
            Node<T> *left = closestElement(node->left, data);
            if (!left)
                return node;
            else
            {
                if (abs(data - node->data) < abs(data - left->data))
                    return node;
                else
                    return left;
            }
        }
    }
    void kthLargestElement(Node<T> *node, int &count, int k)
    {
        if (!node || count >= k)
            return;
        kthLargestElement(node->right, count, k);
        count++;
        if (count == k)
        {
            cout << node->data << "\n";
        }
        kthLargestElement(node->left, count, k);
    }
    int countInRange(Node<T> *node, T l, T r)
    {
        if (!node)
            return 0;
        if (node->data == l && l == r)
            return 1;
        if (node->data >= l && node->data <= r)
        {
            return 1 + countInRange(node->left, l, r) + countInRange(node->right, l, r);
        }
        if (node->data > r)
        {
            return countInRange(node->left, l, r);
        }
        else
        {
            return countInRange(node->right, l, r);
        }
    }
};
int main()
{
    // AVLTree<student> *tree = new AVLTree<student>();
    // student s1;
    // s1.age = 24;
    // s1.name="kiran";
    // student s2;
    // s2.age = 12;
    // s2.name="krupa";
    // cout<<"firstone\n";
    // tree->root = tree->insert(tree->root, s1);
    // cout<<"secondone\n";
    // tree->root = tree->insert(tree->root, s2);
    // student s3;
    // s3.age = 9;
    // s3.name="krupa2";
    // tree->root = tree->insert(tree->root, s3);
    // tree->root = tree->deleteNode(tree->root, s2);
    AVLTree<int> *tree = new AVLTree<int>();
    // AVLTree<string> *tree = new AVLTree<string>();
    while (1)
    {
        cout << "1.Insert 2.Delete 3.Search 4.Count 5.lower_bound 6.upper_bound\n7.Closest element 8.KthLargest Element 9.count elements in range 10.exit\n";
        int option, count, k;
        cin >> option;
        Node<int> *res;
        // Node<string> *res;
        int val,l, r;
        // string val,l, r;
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
        case 3:
            cout << "Enter value: ";
            cin >> val;
            if (tree->search(tree->root, val))
                cout << "Element found!!\n";
            else
                cout << "Element not found\n";
            break;
        case 4:
            cout << "Enter value: ";
            cin >> val;
            tree->count(tree->root, val);
            break;
        case 5:
            cout << "Enter value: ";
            cin >> val;
            res = tree->lowerBound(tree->root, val);
            if (res)
                cout << res->data << "\n";
            else
                cout << "Cannot found\n";
            break;
        case 6:
            cout << "Enter value: ";
            cin >> val;
            res = tree->upperBound(tree->root, val);
            if (res)
                cout << res->data << "\n";
            else
                cout << "Cannot found\n";
            break;
        case 7:
            cout << "Enter value: ";
            cin >> val;
            // res = tree->closestElement(tree->root, val);
            if (res)
                cout << res->data << "\n";
            else
                cout << "Cannot found\n";
            break;
        case 8:
            cout << "Enter k: ";
            cin >> k;
            count = 0;
            tree->kthLargestElement(tree->root, count, k);
            break;
        case 9:
            cout << "Enter [l,r]: ";
            cin >> l >> r;
            cout << tree->countInRange(tree->root, l, r)<<"\n";
            break;
        case 10:
            return 0;
            break;
        }
    }
    return 0;
}