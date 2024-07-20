#include <bits/stdc++.h>
#define x first
#define y second
#define pb push_back
#define all(v) v.begin(),v.end()
#pragma gcc optimize("O3")
#pragma gcc optimize("Ofast") 
#pragma gcc optimize("unroll-loops")
using namespace std;
const int INF = 1e9;
const int TMX = 1 << 18;
const long long llINF = 1e18+10;
const long long mod = 1e9+7;
const long long hashmod = 100003;
const int MAXN = 100000;
const int MAXM = 1000000;
typedef long long ll;
typedef long double ld;
typedef pair <int,int> pi;
typedef pair <ll,ll> pl;
typedef vector <int> vec;
typedef vector <pi> vecpi;
typedef long long ll;
int n,k,ne,pw = 1,p = -1,pv[4200005];

void dfs(int x) {
    while(pv[x] != n) {
        ne = 1LL*x*n%pw+pv[x];
        pv[x]++;
        dfs(ne);
    }
    if(p != -1) cout << p << ' ';
    p = x%n;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    if(k-- == 1) {
        for(int i = 0;i < n;i++) cout << i << ' ';
        return 0;
    }
    for(int i = 1;i <= k;i++) pw *= n;
    dfs(0);
}