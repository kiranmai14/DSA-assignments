#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

void getSuffixArray(vector<pair<string, int>> &sa, string inp)
{
    map<string, int> mp;
    string intermediate = "";
    for (int i = inp.size() - 1; i >= 0; i--)
    {
        intermediate = inp[i] + intermediate;
        mp[intermediate] = i;
    }
    int i = 0;
    for (auto x : mp)
    {
        sa[i].first = x.first;
        sa[i++].second = x.second;
    }
}
long long maxSubstring(vector<pair<string, int>> &sa, int k)
{
    int maxi = -1;
    for (int i = 0; i < sa.size() - k + 1; i++)
    {
        string a = sa[i].first;
        string b = sa[i + k - 1].first;
        int j = 0;
        while (a[j] == b[j])
            j++;
        if (maxi < j && j > 0)
            maxi = j;
    }
    return maxi;
}
int main()
{
    string inp = "";
    cin >> inp;
    int k;
    cin >> k;

    vector<pair<string, int>> sa(inp.size());
    getSuffixArray(sa, inp);
    cout << maxSubstring(sa, k);
}