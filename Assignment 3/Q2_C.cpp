#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MAX_ROW 1000
#define MAX_COL 1000
// int grid[MAX_ROW][MAX_COL];
bool checkborders(int i, int j, int r, int c, int b)
{
    return (i >= 0 && i < r && j >= 0 && j < c && b == 0);
}
void bfs(int grid[MAX_ROW][MAX_COL], int r, int c)
{
    bool visited[r][c] = {false};
    queue<pair<int, int>> q;
    q.push({1, 0});
    int x[4] = {1, -1, 0, 0};
    int y[4] = {0, 0, 1, -1};
    while (!q.empty())
    {
        pair<int, int> p = q.front();
        q.pop();
        int lef = p.first;
        int rig = p.second;
        visited[lef][rig] = true;
        for (int i = 0; i < 4; i++)
        {
            int X = lef + x[i];
            int Y = rig + y[i];
            if (checkborders(X, Y, r, c, grid[X][Y]))
            {
                if (!visited[X][Y])
                {
                    grid[X][Y] = grid[lef][rig] + 1;
                    q.push({X, Y});
                }
            }
        }
    }
    // for (int i = 0; i < r; i++)
    // {
    //     for (int j = 0; j < c; j++)
    //     {
    //         cout << grid[i][j] << " ";
    //     }
    //     cout << endl;
    // }
}
int main()
{
    int n, m;
    cin >> n >> m;
    int grid[MAX_ROW][MAX_COL];
    vector<pair<int, int>> rider_pos;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char c;
            cin >> c;
            if (c == '#')
                grid[i][j] = -1;
            else if (c == '.' || c == 'A')
                grid[i][j] = 0;
            else if (c == 'R')
            {
                rider_pos.push_back({i, j});
                grid[i][j] = 0;
            }
        }
    }
    bfs(grid, n, m);
    int a = grid[n - 2][m - 2];
    bool flag = 0;
    if (a == 0)
    {
        cout << "NO";
        return 0;
    }
    for (int i = 0; i < rider_pos.size(); i++)
    {
        pair<int, int> p = rider_pos[i];
        int lef = p.first;
        int rig = p.second;

        if (grid[lef][rig] && grid[lef][rig] < a)
        {
            flag = 1;
            break;
        }
    }
    if (!flag)
        cout << "YES" << endl
             << a;
    else
        cout << "NO";
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}