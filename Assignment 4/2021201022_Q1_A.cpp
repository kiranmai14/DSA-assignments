#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

void getSuffixArray(vector<int> &sa, string inp)
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
        sa[i++] = x.second;
    }
}
string lexString(vector<int> &sa, string inp, int orlen)
{
    string res = "";
    for (int i = 0; i < sa.size(); i++)
    {
        if (sa[i] < orlen)
        {
            res = inp.substr(sa[i], orlen);
            return res;
        }
    }
    return "-1";
}
int main()
{
    string inp = "";
    cin >> inp;

    int orlen = inp.size();
    string modinp = inp + inp;

    vector<int> sa(modinp.size()), lcp(modinp.size());
    getSuffixArray(sa, modinp);
    cout << lexString(sa, modinp, orlen);
}