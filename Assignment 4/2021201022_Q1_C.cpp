#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
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
void longestPalindrome(vector<int> &sa, vector<int> &lcp)
{
    int len = 0;
    for(int i=0;i<sa.size();i++)
    {
        // if(lcp[i])
    }
}
int main()
{
    string inp = "";
    cin >> inp;
    vector<int> sa(inp.size()), lcp(inp.size());
    getSuffixArray(sa, inp);
    getLCP(sa, lcp, inp);
    
}