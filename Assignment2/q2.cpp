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
    while (ptr != nullptr)
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
    Node<T1, T2> *val = search(Node<T1, T2> * ptr, T1 key);
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
    Node<T1, T2> *node = search(Node<T1, T2> * ptr, T1 key);
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
        delete temp;
        return node;
    }
}

template <class T1, class T2>
class unoredered_map
{

public:
    Node<T1, T2> *hashtable[1024];
    unoredered_map()
    {
        memset(hashtable, nullptr, 1024);
    }
    int hash(int key)
    {
        return key % 1031;
    }
    int hash(T1 key)
    {
        string str = to_string(key);
        it p = 256;
        int m = 1e9 + 9;
        long long p_pow = 1;
        long long hashVal = 0;
        for (int i = 0; i < str.length(); i++)
        {
            hashVal = (hashVal+(str[i]*p_pow)%m;
            p_pow = p_pow%m;
        }
        return ((hashVal % m + m) % m) % 1031;
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
        Node<T1, T2> *node = search(hashtable[pos], T1 key);
        if (node == nullptr)
        {
            cout << "Not found\n";
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
        Node<T1, T2> *node = search(hashtable[pos], T1 key);
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
    // unordered_map<int,int> m;
    // m.insert({1,10});
    double f = 123.45;
    double f3;
    double f2 = std::modf(f, &f3);
    std::cout << "modf() makes " << f3 << " + " << f2 << '\n';
    uint64_t T[8][256];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 256; j++)
            T[i][j] = getRandomUInt64();
}