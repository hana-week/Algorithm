#include<bits/stdc++.h>
#define MAXN 100100
#define LOGN 20
using namespace std;
using ll = long long;
const int INF = -1e9;
int N, M, timer;
int euler[2*MAXN], lev[MAXN];
ll h[MAXN];
vector<vector<int>> idx(MAXN*2);
vector<vector<pair<int,ll>>> G(MAXN);

void dfs(int cur, int par, int l, ll d){
    lev[cur] = l;
    h[cur] = d;
    euler[++timer] = cur;
    idx[cur].push_back(timer);
    for(const auto &p : G[cur]) {
        int v = p.first;
        ll w = p.second;
        if(v == par) continue;
        dfs(v, cur, l+1, d+w);
        euler[++timer] = cur;
        idx[cur].push_back(timer);
    }
}

int pw2[LOGN], lg2[MAXN*2];
pair<int,int> ST[LOGN][MAXN*2];

void sparsetable_build(){
    // calculate pw2 array
    pw2[0] = 1;
    for(int k=1;k<LOGN;k++) pw2[k] = pw2[k-1] * 2;

    // calculate lg2 array
    memset(lg2, -1, sizeof lg2);
    for(int k=0;k<LOGN;k++) if( pw2[k] < MAXN*2 ) lg2[pw2[k]] = k;
    for(int i=1;i<MAXN*2;i++) if( lg2[i] == -1 ) lg2[i] = lg2[i-1];

    // calculate sparse table
    for(int i=1;i<=2*N-1;i++) ST[0][i] = {lev[euler[i]], euler[i]};

    for(int k=1;k<LOGN;k++){
        for(int i=1;i<=2*N-1;i++){
            if( i + pw2[k-1] > 2*N-1 ) continue;
            ST[k][i] = min(ST[k-1][i], ST[k-1][i+pw2[k-1]]);
        }
    }    
}

int LCA(int u, int v){
    int l = idx[u][0], r = idx[v][0];
    if( l > r ) swap(l,r);
    int k = lg2[r-l+1];
    return min(ST[k][l], ST[k][r-pw2[k]+1]).second;
}

ll dist(int u, int v) {
    return h[u] + h[v] - 2*h[LCA(u,v)];
}

vector<int> sub_sz, parent;
vector<bool> vis, color;

int get_size(int cur, int par) {
    sub_sz[cur] = 1;
    for(auto &p:G[cur]) {
        int nxt = p.first;
        if(nxt == par || vis[nxt]) continue;
        sub_sz[cur] += get_size(nxt, cur);
    }
    return sub_sz[cur];
}

int get_cent(int cur, int par, int thr) {
    for(auto &p:G[cur]) {
        int nxt = p.first;
        if(nxt == par || vis[nxt]) continue;
        if(sub_sz[nxt] > thr) return get_cent(nxt, cur, thr);
    }
    return cur;
}

void make_tree(int cur, int par) {
    int thr = get_size(cur, -1);
    int cent = get_cent(cur, -1, thr/2);
    vis[cent] = true;
    if(par == -1) parent[cent] = 0;
    else parent[cent] = par;
    for(auto &p:G[cent]) {
        int nxt = p.first;
        if(!vis[nxt]) make_tree(nxt, cent);
    }
}

vector<unordered_map<int,multiset<int>>> subtree;
vector<multiset<int>> sub_dm;
multiset<int> ans;
vector<int> dp;
int cnt;

void update_ans(int idx) {
    if(sub_dm[idx].size() < 2) {
        if(dp[idx] != INF) ans.erase(ans.find(dp[idx]));
        dp[idx] = INF;
        return ;
    }
    int tmp = *(sub_dm[idx].rbegin()) + *next(sub_dm[idx].rbegin());
    if(dp[idx] == INF) {
        ans.insert(tmp);
        dp[idx] = tmp;
    }
    else if(dp[idx] != tmp) {
        ans.erase(ans.find(dp[idx]));
        ans.insert(tmp); dp[idx] = tmp;
    }
}

void update(int cur) {
    if(color[cur]) --cnt;
    else ++cnt;
    color[cur] = !color[cur];
    int prev = cur;
    int p = cur;
    while(p) {
        int d = 0;
        if(p != cur) d = dist(p, cur);
        auto &ms = subtree[p][prev];
        if(color[cur]) {
            if(ms.lower_bound(d) == ms.end()) {
                if(!ms.empty()) sub_dm[p].erase(sub_dm[p].find(*(ms.rbegin())));
                ms.insert(d); sub_dm[p].insert(d);
                update_ans(p);
            }
            else {
                ms.insert(d);
            }
        }
        else {
            int mx = *(ms.rbegin());
            ms.erase(ms.find(d));
            if(ms.lower_bound(mx) == ms.end()) {
                sub_dm[p].erase(sub_dm[p].find(mx));
                if(!ms.empty()) sub_dm[p].insert(*(ms.rbegin()));
                update_ans(p);
            }
        }
        prev = p;
        p = parent[p];
    }
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    cin >> N;
    for(int i=1;i<N;++i) {
        int u, v, w; cin >> u >> v >> w;
        G[u].emplace_back(v,w);
        G[v].emplace_back(u,w);
    }
    dfs(1, -1, 0, 0);
    sparsetable_build();
    vis.resize(N+1); color.resize(N+1); sub_sz.resize(N+1); parent.resize(N+1);
    subtree.resize(N+1); dp.resize(N+1, INF); sub_dm.resize(N+1);
    make_tree(1, -1);
    for(int i=1;i<=N;++i) {
        subtree[i][i] = multiset<int>();
        if(parent[i]) subtree[parent[i]][i] = multiset<int>();
    }
    for(int i=1;i<=N;++i) update(i);
    cin >> M;
    for(int i=0;i<M;++i) {
        int q, x;
        cin >> q;
        if(q == 1) {
            cin >> x; update(x);
        }
        else {
            if(!cnt) cout << -1 << '\n';
            else if(cnt == 1) cout << 0 << '\n';
            else {
                int tmp = *(ans.rbegin());
                if(tmp < 0) tmp = 0;
                cout << tmp << '\n';
            }
        }
    }
    return 0;
}