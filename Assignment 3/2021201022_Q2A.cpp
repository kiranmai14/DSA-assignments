#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> dijksta(vector<vector<pair<int, int>>> g, int d)
{
    int n = g.size();
    bool visited[n] = {false};
    visited[d] = true;
    vector<long long> weight(n, INT64_MAX);
    weight[d] = 0;
    vector<string> path(n, "");
    path[d] = to_string(d);
    for (auto adj : g[d])
    {
        weight[adj.first] = adj.second;
        string x = to_string(adj.first) + " " + to_string(d);
        path[adj.first] = x;
    }
    for (int i = 0; i < n - 1; i++)
    {
        // select min from remaining edges weights
        long long min_weight = INT64_MAX, node;
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
            if (!visited[v] && weight[v] > weight[node] + w)
            {
                weight[v] = weight[node] + w;
                string y = to_string(v) + " " + path[node];
                path[v] = y;
            }
            else if (!visited[v] && weight[v] == weight[node] + w)
            {
                weight[v] = weight[node] + w;
                string y = to_string(v) + " " + path[node];
                if (path[v] > y)
                    path[v] = y;
            }
        }
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
    int dest;
    cin >> dest;
    vector<string> res1(n);
    res1 = dijksta(g, dest);
    for (int i = 0; i < n; i++)
    {
        if (i == dest)
            continue;
        cout << res1[i] << endl;
    }
}