#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

void dfs(vector<vector<pair<int, int>>> g, int i, vector<vector<string>> &path, vector<bool> &visited, string &d, int weight)
{
    visited[i] = true;
    for (auto adj : g[i])
    {
        if (!visited[adj.first])
        {
            weight = weight + adj.second;
            d = d + " "+to_string(adj.first);
            path[weight].push_back(d);
            dfs(g, adj.first, path, visited, d, weight);
            d.pop_back();
            d.pop_back();
            weight = weight - adj.second;
        }
    }
    visited[i] = false;
}
void printPaths(vector<vector<pair<int, int>>> g, int k)
{
    int n = g.size();
    vector<bool> visited(n, false);
    vector<vector<string>> w(110);
    string d = "";
    int weight = 0;
    for (int i = 0; i < n; i++)
    {
        d = to_string(i);
        weight = 0;
        dfs(g, i, w, visited, d, weight);
    }
    for (int i = 0; i < 110; i++)
    {
        sort(w[i].begin(), w[i].end());
    }
    for (int i = 0; i < 110; i++)
    {
        int s = w[i].size();
        for (int j = 0; j < s; j++)
        {
            if (w[i][j] == "")
                continue;
            string toSearch = w[i][j];
            reverse(toSearch.begin(), toSearch.end());
            for (int k = j + 1; k < s; k++)
            {
                if (toSearch == w[i][k])
                {
                    w[i][k] = "";
                    break;
                }
            }
        }
    }
    for (int i = 0; i < 110; i++)
    {
        if (k == 0)
            break;
        for (auto x : w[i])
        {
            if (k == 0)
                break;
            if (k && x.size() > 0)
            {
                cout << x;
                k--;
                cout << endl;
            }
        }
    }
}
int main()
{
    int n, m, k;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++)
    {
        int s, d, w;
        cin >> s >> d >> w;
        g[s].push_back({d, w});
        g[d].push_back({s, w});
    }
    cin >> k;
    printPaths(g, k);
}