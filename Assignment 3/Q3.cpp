#include <iostream>
using namespace std;
#define MAX_ROW 10
#define MAX_COL 10
int r, c;
char mat[MAX_COL][MAX_COL];
bool checkborders(int i, int j, char ch)
{
    return (i >= 0 && i < r && j >= 0 && j < c && mat[i][j] == ch);
}
bool fun(bool visited[MAX_ROW][MAX_COL], int i, int j, string que, int k)
{
     if (k == que.size())
        return true;
    if(visited[i][j] == true)
        return false;
    visited[i][j] = true;
    static int x[4] = {1, -1, 0, 0};
    static int y[4] = {0, 0, 1, -1};
    for (int l = 0; l < 4; l++)
    {
        int X = i + x[l];
        int Y = j + y[l];
        if (checkborders(X, Y, que[k]))
            return fun(visited, X, Y, que, k + 1);
    }
    return false;
}
bool check(string que)
{
    bool visited[MAX_ROW][MAX_COL] = {false};
    int k = 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (mat[i][j] == que[0])
                if (fun(visited, i, j, que, k+1))
                    return true;
        }
    }
    return false;
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
    string list[l];
    for (int i = 0; i < l; i++)
        cin >> list[i];
    // cout<<check(list[0]);
    for (int i = 0; i < l; i++)
    {
        if (check(list[i]))
            cout<<true<<endl;
        else
            cout<<false<<endl;
    }
}