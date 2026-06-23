#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("input1.txt");

/***********************************************************************
 * Binomial Coefficient
 *
 * C(n,k)
 *
 * 점화식:
 *
 * C(n,k)
 * =
 * C(n-1,k-1) + C(n-1,k)
 *
 * 경계조건:
 *
 * C(n,0)=1
 * C(n,n)=1
 ***********************************************************************/
long long binomial(int n, int k)
{
    vector<vector<long long>> dp(
        n + 1,
        vector<long long>(k + 1, 0)
    );

    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=min(i,k);j++)
        {
            if(j==0 || j==i)
            {
                dp[i][j]=1;
            }
            else
            {
                dp[i][j]
                =
                dp[i-1][j-1]
                +
                dp[i-1][j];
            }
        }
    }

    return dp[n][k];
}

int main()
{
    if(!fin)
    {
        cout<<"Cannot open input1.txt\n";
        return 0;
    }

    int n,k;

    fin>>n>>k;

    cout<<binomial(n,k)<<"\n";

    fin.close();

    return 0;
}