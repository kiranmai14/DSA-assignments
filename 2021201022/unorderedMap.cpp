#include <iostream>
#include <sstream>
#include <string>
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
    if (node == nullptr)
        return nullptr;
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
    int tsize = 1031;
    Node<T1, T2> *hashtable[1031];

    unordered_map()
    {
        for (int i = 0; i < tsize; i++)
            hashtable[i] = nullptr;
    }
    int hash(T1 key)
    {
        int p = 256;
        long long hashVal = 0;
        string str;
        ostringstream st;
        st << key;
        str = st.str();
        long long powOfP = 1;
         int m = 1e9 + 9;
        for (int i = 0; i < str.length(); i++)
        {
            hashVal = (hashVal + (str[i] * powOfP)) % m;
            powOfP = (powOfP*p) % m;
        }
        return ((hashVal % m + m) % m) % tsize;
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
    T2 operator[](T1 key)
    {
        int pos = hash(key);
        Node<T1, T2> *node = search(hashtable[pos], key);
        if (node == nullptr)
        {
            // this->insert(key,0);
            return -1;
        }
        else
        {
            return node->val;
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