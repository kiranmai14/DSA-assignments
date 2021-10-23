#include <iostream>
#include <vector>
#include <algorithm>
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
void fetch(TrieNode *root, vector<string> &res)
{
    for (int i = 0; i < 26; i++)
    {
        if (root->child[i] == nullptr)
        {
            continue;
        }
        if (root->child[i]->isEnd)
        {
            res.push_back(root->child[i]->word);
        }
        fetch(root->child[i], res);
    }
}
vector<string> autoComplete(string key, TrieNode *root)
{
    vector<string> res;
    TrieNode *temp = root;
    int index;
    bool flag = 0;
    for (int i = 0; i < key.size(); i++)
    {
        index = key[i] - 'a';
        if (temp->child[index] == nullptr)
        {
            flag = 1;
            break;
        }
        temp = temp->child[index];
    }
    if (temp->isEnd)
    {
        res.push_back(temp->word);
    }
    if (!flag)
        fetch(temp, res);
    return res;
}
void findDist(string key, vector<vector<int>> &mat, char c)
{
    vector<int> row;
    row.push_back(mat.size());
    for (int j = 1; j <= key.size(); j++)
        row.push_back(0);
    int cost = 0, val = 0;
    int i = mat.size();
    mat.push_back(row);
    for (int j = 1; j <= key.size(); j++)
    {
        if (key[j - 1] == c)
            cost = 0;
        else
            cost = 1;
        val = min(mat[i - 1][j] + 1, mat[i][j - 1] + 1);
        val = min(val, mat[i - 1][j - 1] + cost);
        mat[i][j] = val;
        val = 0;
    }
}
void autoCorrect(string key, TrieNode *root, vector<string> &res, vector<vector<int>> &mat)
{
    for (int i = 0; i < 26; i++)
    {
        if (root->child[i] == nullptr)
        {
            continue;
        }
        char a = i + 'a';
        findDist(key, mat, a);
        int k = mat.size() - 1;
        int l = key.size();
        if (mat[k][l] <= 3 && root->child[i]->isEnd)
        {
            res.push_back(root->child[i]->word);
        }
        autoCorrect(key, root->child[i], res, mat);
        mat.pop_back();
    }
}
int main()
{
    TrieNode *root = new TrieNode("$");
    int n, a;
    cin >> n;
    string dict[n], test;
    vector<string> res2, res3;
    for (int i = 0; i < n; i++)
        cin >> dict[i];
    buildTrie(dict, n, root);
    cin >> a >> test;
    vector<vector<int>> mat;
    if (a == 1)
    {
        cout << spellCheck(test, root);
    }
    else if (a == 2)
    {
        res2 = autoComplete(test, root);
        cout << res2.size() << endl;
        for (string temp : res2)
        {
            cout << temp << endl;
        }
    }
    else if (a == 3)
    {
        vector<int> row;
        for (int i = 0; i <= test.size(); i++)
        {
            row.push_back(i);
        }
        mat.push_back(row);
        autoCorrect(test, root, res3, mat);
        cout << res3.size() << endl;
        for (string temp : res3)
        {
            cout << temp << endl;
        }
    }
}