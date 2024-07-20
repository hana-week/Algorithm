#include <bits/stdc++.h>
using namespace std;
#define ll long long
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target ("avx,avx2,fma")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define usecppio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define int ll
#define all(x) ((x).begin()),((x).end())
#define eps 1e-7

int n, a, b;
int v[2020];
int psum[2020];

inline int rsum(int lft, int rgt)
{
    return psum[rgt]-psum[lft-1];
}
void solve_1()
{
    bitset<51> bton((1ll<<50)-1);
    for (int bt = 50; bt>=0; bt--)
    {
        int dp[2020];
        memset(dp, 0x7f, sizeof(dp));
        dp[0] = 0;
        bton[bt] = false;
        bton.flip();
        int x = bton.to_ullong();
        bton.flip();
        for (int i = 1; i<=n; i++)
        {
            for (int j = 0; j<i; j++)
            {
                int u = rsum(j+1, i);
                if ((u & x)==0)
                    dp[i] = min(dp[i], dp[j]+1);
            }
        }
        bton[bt] = dp[n]>b;
    }
    cout << bton.to_ullong() << '\n';
}
void solve_else()
{
    bitset<51> bton((1ll<<50)-1);
    for (int bt = 50; bt>=0; bt--)
    {
        bool dp[220][220];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i<=200; i++)
            dp[0][0] = 1;
        bton[bt] = false;
        bton.flip();
        int x = bton.to_ullong();
        bton.flip();
        for (int i = 1; i<=n; i++)
        {
            for (int j = 1; j<=b; j++)
            {
                for (int k = 0; k<i; k++)
                {
                    if (!dp[k][j-1]) continue;
                    int u = rsum(k+1, i);
                    if ((u & x)==0)
                        dp[i][j] |= dp[k][j-1];
                }
            }
        }
        bton[bt] = true;
        for (int i = a; i<=b; i++)
            if (dp[n][i])
                bton[bt] = false;
    }
    cout << bton.to_ullong() << '\n';
}
int32_t main()
{
    usecppio
    cin >> n >> a >> b;
    for (int i = 1; i<=n; i++)
        cin >> v[i];
    for (int i = 1; i<=n; i++)
        psum[i] = psum[i-1] + v[i];
    if (a == 1)
        solve_1();
    else solve_else();
}