#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;

typedef long long ll;

int n, m; ll k;
ll inp[2020][2020];
ll a[2020][2020];
ll tmp[2020][2020];

inline ll query(int x, int xx, int y, int yy){ return a[xx][yy] - a[x-1][yy] - a[xx][y-1] + a[x-1][y-1]; }

int chk(int l, int r){
    int t = r - l + 1;
    int a = 1, b = n, c = 1, d = m;
    for(int i=0; i<n+m-t-1; i++){
        if(b-a+1 > 1 && query(a, a, c, d) <= k){ a++; continue; }
        if(b-a+1 > 1 && query(b, b, c, d) <= k){ b--; continue; }
        if(c < l && query(a, b, c, c) <= k){ c++; continue; }
        if(d > r && query(a, b, d, d) <= k){ d--; continue; }
        return 0;
    }
    if(query(a, b, c, d) <= k) return 1;
    return 0;
}

int solve(){
    for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) a[i][j] = inp[i][j] + a[i-1][j] + a[i][j-1] - a[i-1][j-1];
    int l = 1, r = 1;
    int ans = 1e9+7;
    while(1){
        int res = chk(l, r);
        if(res) ans = min(ans, n+m-(r-l+1));
        if(l == m && r == m) break;
        if(r == m) l++;
        else if(l == r) r++;
        else if(res) r++;
        else l++;
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> k >> m >> n;
    for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) cin >> inp[i][j], a[i][j] = inp[i][j];
    int t1 = solve();
    memcpy(tmp, inp, sizeof tmp);
    for(int i=1; i<=m; i++) for(int j=1; j<=n; j++) inp[i][j] = tmp[n-j+1][i];
    swap(n, m);
    int t2 = solve();
    cout << min(t1, t2);
}