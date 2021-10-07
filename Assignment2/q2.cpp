#include <iostream>
#include <cmath>
using namespace std;

template <typename T1,typename T2>
class Node
{
public:
    T1 key;
    T2 val;
    Node *left;
    Node *right;
    Node(T1 key,T2 val)
    {
        this->key = key;
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
    }
};
template <class T1, class T2>
class unoredered_map
{

public:
    Node<T1,T2> *hashtable[1024];
    unoredered_map()
    {
        memset(hashtable,nullptr,1024);
    }
    int hash(int key){
        return key%1031;
    }
    void insert(int key,T2 val){
        int pos = hash(key);
        
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