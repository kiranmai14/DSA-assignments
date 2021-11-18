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
void getLCP(vector<int> &sa, vector<int> &lcp, string inp)
{
    vector<int> saInv(sa.size());
    for (int i = 0; i < sa.size(); i++)
    {
        saInv[sa[i]] = i;
    }
    int inter = 0;
    for (int i = 0; i < sa.size(); i++)
    {
        if (saInv[i] == sa.size() - 1)
        {
            inter = 0;
        }
        else
        {
            int j = sa[saInv[i] + 1];
            while (j + inter < sa.size() && i + inter < sa.size())
            {
                if (inp[j + inter] == inp[i + inter])
                {
                    inter++;
                }
                else
                    break;
            }
            lcp[saInv[i]] = inter;
            if (inter > 0)
                inter--;
        }
    }
}
string longestPalindrome(vector<int> &sa, vector<int> &lcp, string modinp, int orlen)
{
    int longlen = 0;
    int pos = 0;
    string res = "";
    for (int i = 0; i < sa.size(); i++)
    {
        if (lcp[i] > longlen)
        {
            if ((sa[i] < orlen && sa[i - 1] > orlen) || (sa[i - 1] < orlen && sa[i] > orlen))
            {
                longlen = lcp[i];
                pos = sa[i];
                res = modinp.substr(pos, pos + longlen - 1);
            }
        }
        else if (lcp[i] == longlen)
        {
            pos = sa[i];
            string x = modinp.substr(pos, pos + longlen - 1);
            if (x < res)
                res = x;
        }
    }
    return res;
}
int main()
{
    string inp = "";
    cin >> inp;
    int orlen = inp.size();

    string modinp = inp + "$";
    reverse(inp.begin(), inp.end());
    modinp = modinp + inp;

    vector<int> sa(modinp.size()), lcp(modinp.size());
    getSuffixArray(sa, modinp);
    getLCP(sa, lcp, modinp);

    cout << longestPalindrome(sa, lcp, modinp, orlen) << endl;
}