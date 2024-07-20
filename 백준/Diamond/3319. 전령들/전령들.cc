#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

struct Line{
    ll m, b;
    Line() : m(0), b(0) {};
    Line(ll m_, ll b_) : m(m_), b(b_) {};
    ll f(ll x) { return m*x + b; }
};

vector<Line> lines;
int ptr = 1;
vector<ll> dp, V, S;
vector<vector<pair<int,ll>>> G;
int N;

ld intersect(Line &a, Line &b) {
    return (ld)(a.b - b.b)/(b.m - a.m);
}

int add_line(Line &line) {
    int lo = 1, hi = ptr;
    while(lo < hi) {
        int mid = lo + hi >> 1;
        if(intersect(lines[mid-1], line) < intersect(lines[mid], lines[mid-1])) hi = mid;
        else lo = mid+1;
    }
    return lo;
}

ll query(ll x) {
    int lo = 0, hi = ptr - 1;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(intersect(lines[mid], lines[mid-1]) < x) lo = mid;
        else hi = mid-1;
    }
    return lines[lo].f(x);
}

void dfs(int cur, int par, ll dist) {
    int rb_idx, rb_ptr = ptr;
    Line rb_line;
    if(par) {
        dp[cur] = query(V[cur]) + dist * V[cur] + S[cur];
        Line cur_line(-dist, dp[cur]);
        rb_idx = add_line(cur_line);
        rb_line = lines[rb_idx];
        lines[rb_idx] = cur_line;
        ptr = rb_idx+1;
    }
    for(auto &nxt:G[cur]) {
        int v = nxt.first;
        ll w = nxt.second;
        if(v == par) continue;
        dfs(v, cur, dist+w);
    }
    if(par) {
        lines[rb_idx] = rb_line;
        ptr = rb_ptr;
    }
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    cin >> N;
    dp.resize(N+1); S.resize(N+1); V.resize(N+1);
    G.resize(N+1); lines.resize(N+1, Line());
    for(int i=1;i<N;++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v,w);
        G[v].emplace_back(u,w);
    }
    for(int i=2;i<=N;++i) cin >> S[i] >> V[i];
    dfs(1, 0, 0);
    for(int i=2;i<=N;++i) cout << dp[i] << " \n"[i==N];
    return 0;
}