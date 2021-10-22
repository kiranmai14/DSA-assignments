#include <iostream>
#include <vector>
using namespace std;
class TrieNode
{
public:
    TrieNode *child[26];
    bool isEnd;
    string word;
    TrieNode(string word)
    {
        isEnd = false;
        this->word = word;
        for (int i = 0; i < 26; i++)
            child[i] = nullptr;
    }
};
void insert(string str, TrieNode *root)
{
    TrieNode *temp = root;
    string t = "";
    for (int i = 0; i < str.size(); i++)
    {
        int index = str[i] - 'a';
        t = t + str[i];
        if (temp->child[index] == nullptr)
            temp->child[index] = new TrieNode(t);
        temp = temp->child[index];
    }
    temp->isEnd = true;
}
void buildTrie(string l[], int len, TrieNode *root)
{
    for (int i = 0; i < len; i++)
    {
        insert(l[i], root);
    }
}
bool spellCheck(string key, TrieNode *root)
{
    TrieNode *temp = root;
    for (int i = 0; i < key.size(); i++)
    {
        int index = key[i] - 'a';
        if (temp->child[index] == nullptr)
            return false;
        temp = temp->child[index];
    }
    return temp->isEnd;
}
// vector<string> autoComplete(string key, TrieNode *root)
// {
//     vector<string> res;
//     TrieNode *temp = root;
//     int index;
//     for (int i = 0; i < key.size(); i++)
//     {
//         index = key[i] - 'a';
//         if (temp->child[index] == nullptr)
//         {
//             break;
//         }
//         if(temp->isEnd)
//         {
//             res.push_back(temp->word);
//         }
//         temp = temp->child[index];
//     }
//     while()
//     return res;
// }
int main()
{
    TrieNode *root = new TrieNode("$");
    int n, a;
    cin >> n;
    string dict[n], test;
    for (int i = 0; i < n; i++)
        cin >> dict[i];
    buildTrie(dict, n, root);
    cin >> a >> test;
    if (a == 1)
    {
        cout << spellCheck(test, root);
    }
}