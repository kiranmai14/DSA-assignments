#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// vector<vector<int>> backTrack(vector<vector<int>> parent, int d, int n)
// {
//     vector<vector<int>> res(n);
//     for (int i = 0; i < n; i++)
//     {
//         sort(parent[i].begin(), parent[i].end());
//     }
//     for (int i = 0; i < n; i++)
//     {
//         if (parent[i][0] == -1)
//             continue;
//         for (int p : parent[i])
//         {
//             int j = p;
//             res[i].push_back(i);
//             while (j != -1)
//             {
//                 res[i].push_back(j);
//                 j = parent[j][0];
//             }
//         }

//         // reverse(res[i].begin(), res[i].end());
//     }
//     return res;
// }
vector<vector<string>> dijksta(vector<vector<pair<int, int>>> g, int d)
{
    int n = g.size();
    bool visited[n] = {false};
    visited[d] = true;
    vector<int> weight(n, INT32_MAX);
    weight[d] = 0;
    vector<vector<string>> path(n);
    path[d].push_back(to_string(d));
    for (auto adj : g[d])
    {
        weight[adj.first] = adj.second;
        string x = to_string(adj.first) + " " + to_string(d);
        path[adj.first].push_back(x);
    }
    for (int i = 0; i < n - 1; i++)
    {
        // select min from remaining edges weights
        int min_weight = INT32_MAX, node;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && weight[j] <= min_weight)
            {
                min_weight = weight[j];
                node = j;
            }
        }
        visited[node] = true;
        // relaxing edges
        for (auto adj : g[node])
        {
            int v = adj.first;
            int w = adj.second;
            if (!visited[v] && weight[v] >= weight[node] + w)
            {
                weight[v] = weight[node] + w;
                for (auto x : path[node])
                {
                    string y = to_string(v) + " " + x;
                    path[v].push_back(y);
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        sort(path[i].begin(), path[i].end());
    }
    return path;
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++)
    {
        int s, d, w;
        cin >> s >> d >> w;
        g[s].push_back({d, w});
        g[d].push_back({s, w});
    }
    // for (int i = 0; i < n; i++)
    // {
    //     sort(g[i].begin(), g[i].end());
    // }
    int dest;
    cin >> dest;
    vector<vector<string>> res1(n);
    res1 = dijksta(g, dest);
    for (int i = 0; i < n; i++)
    {
        if (i == dest)
            continue;
        // for (int j = 0; j < res1[i][0].size(); j++)
        // {
        //     cout << res1[i][0][j] << " ";
        // }
        cout << res1[i][0]<<endl;
    }
}