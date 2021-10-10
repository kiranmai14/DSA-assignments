#include <iostream>
#include <cmath>
using namespace std;

template <typename T1, typename T2>
class Node
{
public:
    T1 key;
    T2 val;
    Node<T1, T2> *next;
    Node<T1, T2> *prev;
    Node(T1 key, T2 val)
    {
        this->key = key;
        this->val = val;
        this->next = nullptr;
        this->prev = nullptr;
    }
};
template <typename T1, typename T2>
Node<T1, T2> *search(Node<T1, T2> *ptr, T1 key)
{
    Node<T1, T2> *temp = ptr;
    while (temp != nullptr)
    {
        if (temp->key == key)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}
template <typename T1, typename T2>
Node<T1, T2> *insertNode(Node<T1, T2> *ptr, T1 key, T2 value)
{
    Node<T1, T2> *val = search(ptr, key);
    if (val != nullptr)
    {
        val->val = value;
        return ptr;
    }
    Node<T1, T2> *node = new Node<T1, T2>(key, value);
    if (ptr == nullptr)
    {
        ptr = node;
    }
    else
    {
        node->next = ptr;
        ptr->prev = node;
        ptr = node;
    }
    return ptr;
}
template <typename T1, typename T2>
Node<T1, T2> *removeNode(Node<T1, T2> *ptr, T1 key)
{
    Node<T1, T2> *node = search(ptr, key);
    if (node->next == nullptr)
    {
        if (node->prev)
            node->prev->next = nullptr;
        else
            return nullptr;
        delete node;
        return ptr;
    }
    else if (node->prev != nullptr && node->next != nullptr)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        return ptr;
    }
    else if (node->prev == nullptr)
    {
        Node<T1, T2> *temp = node;
        if (node->next)
            node->next->prev = nullptr;
        else
            return nullptr;
        temp = node->next; 
        delete node;
        return temp;
    }
    return nullptr;
}

template <class T1, class T2>
class unordered_map
{

public:
    Node<T1, T2> *hashtable[5];
    unordered_map()
    {
        for (int i = 0; i < 5; i++)
            hashtable[i] = nullptr;
    }
    // int hash(T1 key)
    // {
    //     string str = to_string(key);
    //     int p = 256;
    //     int m = 1e9 + 9;
    //     long long p_pow = 1;
    //     long long hashVal = 0;
    //     for (int i = 0; i < str.length(); i++)
    //     {
    //         hashVal = (hashVal + (str[i] * p_pow)) % m;
    //         p_pow = p_pow % m;
    //     }
    //     return ((hashVal % m + m) % m) % 1031;
    // }
    int hash(int key)
    {
        return key % 5;
    }
    void insert(T1 key, T2 val)
    {
        int pos = hash(key);
        hashtable[pos] = insertNode(hashtable[pos], key, val);
    }
    void erase(T1 key)
    {
        int pos = hash(key);
        hashtable[pos] = removeNode(hashtable[pos], key);
    }
    void operator[](T1 key)
    {
        int pos = hash(key);
        Node<T1, T2> *node = search(hashtable[pos], key);
        if (node == nullptr)
        {
            // this->insert(key,0);
            cout << "";
        }
        else
        {
            cout << node->val << "\n";
        }
    }
    bool find(T1 key)
    {
        int pos = hash(key);
        if (pos > 1024)
            return false;
        Node<T1, T2> *node = search(hashtable[pos], key);
        if (node == nullptr)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};

int main()
{
    unordered_map<int, int> m;
    while (1)
    {
        cout << "1.Insert 2.Erase 3.Find 4.map[n] 5.exit\n";
        int option, val, key, l, r;
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "Enter [key,value]: ";
            cin >> key >> val;
            m.insert(key, val);
            break;
        case 2:
            cout << "Enter key: ";
            cin >> val;
            m.erase(val);
            break;
        case 3:
            cout << "Enter key: ";
            cin >> val;
            cout<<m.find(val)<<"\n";
            break;
        case 4:
            cout << "Enter key: ";
            cin >> val;
            m[val];
            break;
        case 5:
            return 0;
            break;
        }
    }
}