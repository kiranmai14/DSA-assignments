#include <bits/stdc++.h>
using namespace std;


int main() {
    
    int n,x;
    cin>>n>>x;
    vector<int> price(n),pieces(n);
    for(int i=0;i<n;i++)
        cin>>price[i];
    for(int i=0;i<n;i++)
        cin>>pieces[i];
    int mat[x+1][n+1];
    for(int i=0;i<=x;i++)
        mat[0][i] = 0;
    for(int i=0;i<=n;i++)
        mat[i][0] = 0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=x;j++)
        {
            if(price[i-1] <= j)
            {
                mat[i][j] = max(mat[i-1][j] , pieces[i-1]+mat[i-1][j-price[i-1]]);
            }
            else
                mat[i][j] = mat[i-1][j];
            
        }
    }
    cout<<mat[x][n];
    
    return 0;
}
