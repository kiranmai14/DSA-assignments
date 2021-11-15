#include <iostream>
#include <vector>
#define BITS 43
using namespace std;

class TrieNode
{
public:
    TrieNode *child[2];
    bool isEnd;
    TrieNode()
    {
        isEnd = false;
        for (int i = 0; i < 2; i++)
            child[i] = nullptr;
    }
};
void insert(vector<bool> numBin, TrieNode *root)
{
    TrieNode *temp = root;
    for (int i = 0; i < numBin.size(); i++)
    {
        int index = numBin[i];
        if (temp->child[index] == nullptr)
            temp->child[index] = new TrieNode();
        temp = temp->child[index];
    }
    temp->isEnd = true;
}
vector<bool> converToBin(long long num)
{
    vector<bool> numBin(BITS);
    int i = BITS - 1;
    while (num > 0)
    {
        numBin[i] = num % 2;
        i--;
        num = num / 2;
    }
    return numBin;
}
void buildTrie(vector<long long> l, TrieNode *root)
{
    for (int i = 0; i < l.size(); i++)
    {
        vector<bool> numBin = converToBin(l[i]);
        insert(numBin, root);
    }
}
long long findXOR(TrieNode *root, long long query)
{
    TrieNode *temp = root;
    long long res = 0;
    long long t = 1;
    vector<bool> qBin = converToBin(query);
    for (int i = 0; i < BITS; i++)
    {
        bool index = qBin[i];
        t = 1;
        if (temp->child[!index] != nullptr)
        {
            t = (t << BITS - i -1);
            res = res + t;
            temp = temp->child[!index];
        }
        else if (temp->child[index] != nullptr)
        {
            temp = temp->child[index];
        }
    }
    return res;
}
int main()
{

    TrieNode *root = new TrieNode();
    int n, q;
    cin >> n >> q;
    vector<long long> inp(n);
    vector<long long> qin(q);
    for (int i = 0; i < n; i++)
        cin >> inp[i];
    for (int i = 0; i < q; i++)
        cin >> qin[i];
    buildTrie(inp, root);
    for (int i = 0; i < q; i++)
    {
        long long res = findXOR(root, qin[i]);
        cout << res << endl;
    }
    return 0;
}