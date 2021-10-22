#include <iostream>
using namespace std;
#define MAX_ROW 10
#define MAX_COL 10
int r, c , len_st;
char mat[MAX_COL][MAX_COL];
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
    for (int i = 0; i < str.size(); i++)
    {
        int index = str[i] - 'a';
        if (temp->child[index] == nullptr)
            temp->child[index] = new TrieNode(str);
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
bool checkborders(int i, int j)
{
    return (i >= 0 && i < r && j >= 0 && j < c);
}
void fun(bool visited[MAX_ROW][MAX_COL], int i, int j, TrieNode *que,string ans[])
{
    if (visited[i][j] == true)
        return;
    if(que->isEnd)
    {
        ans[len_st] = que->word;
        len_st++;
    }
    visited[i][j] = true;
    static int x[4] = {1, -1, 0, 0};
    static int y[4] = {0, 0, 1, -1};
    for (int l = 0; l < 4; l++)
    {
        int X = i + x[l];
        int Y = j + y[l];
        if (checkborders(X, Y))
        {
            int index = mat[X][Y] - 'a';
            if (que->child[index] != nullptr && mat[X][Y] - 'a' == (char)index)
            {
                fun(visited, X, Y, que->child[index],ans);
            }
        }
    }
    visited[i][j] = false;
}
void check(TrieNode *root,string ans[])
{
    bool visited[MAX_ROW][MAX_COL] = {false};
    bool traversed[26] = {false};
    int last_len;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int index = mat[i][j] - 'a';
            if (root->child[index] != nullptr && !traversed[index])
            {
                last_len = len_st;
                fun(visited, i, j, root->child[index],ans);
                if(last_len < len_st)
                    traversed[index] = true;
            }
        }
    }
}
int main()
{
    int l;
    cin >> r >> c;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            cin >> mat[i][j];
    }
    cin >> l;
    bool res[l] = {false};
    string list[l], answer[l];
    for (int i = 0; i < l; i++)
    {
        cin >> list[i];
        answer[i] = "";
    }
    TrieNode *root = new TrieNode("$");
    buildTrie(list, l, root);
    check(root,answer);
    for (string st:answer)
    {
        if(st == "")
            break;
        cout<<st<<endl;
    }
}