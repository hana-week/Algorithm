#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int inf = 1e9;

int n, q;
struct Node{
	ll l, r, mx, sum;
    Node(){ l = r = mx = sum = 0; }
    Node(ll l, ll r, ll mx, ll sum) : l(l), r(r), mx(mx), sum(sum) {}
    void go(){
        l = max<ll>(0, l);
        r = max<ll>(0, r);
        mx = max<ll>(0, mx);
    }
};

Node tree[1 << 18];
int tmp[1 << 18];
const int base = 1 << 17;

Node merge(Node a, Node b){
	Node ret;
	ret.l = max(a.l, a.sum + b.l);
	ret.r = max(a.r + b.sum, b.r);
	ret.sum = a.sum + b.sum;
	ret.mx = max({a.mx, b.mx, a.r + b.l});
    ret.go();
	return ret;
}

void push(int node, int s, int e){
    if(tmp[node] == inf) return;
    tree[node].l = tree[node].r = tree[node].mx = tree[node].sum = (e-s+1) * tmp[node];
    tree[node].go();
    if(s ^ e){
        tmp[node << 1] = tmp[node];
        tmp[node << 1 | 1] = tmp[node];
    }
    tmp[node] = inf;
}

void seg_update(int l, int r, int v, int node = 1, int s = 1, int e = n){
    push(node, s, e);
    if(r < s || e < l) return;
    if(l <= s && e <= r){
        tmp[node] = v;
        push(node, s, e);
        return;
    }
    int m = s + e >> 1;
    seg_update(l, r, v, node << 1, s, m);
    seg_update(l, r, v, node << 1 | 1, m+1, e);
    tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
}

Node seg_query(int l, int r, int node = 1, int s = 1, int e = n){
    push(node, s, e);
    if(r < s || e < l) return Node(0, 0, 0, 0);
    if(l <= s && e <= r) return tree[node];
    int m = s + e >> 1;
    Node t1 = seg_query(l, r, node << 1, s, m);
    Node t2 = seg_query(l, r, node << 1 | 1, m+1, e);
    return merge(t1, t2);
}

int arr[101010];
int top[101010], in[101010], dep[101010], sz[101010], par[101010], pv;
vector<int> g[101010], inp[101010];
void dfs(int v = 1, int p = -1){
    for(auto i : inp[v]){
        if(i == p) continue;
        par[i] = v; g[v].push_back(i);
        dfs(i, v);
    }
}
void dfs1(int v = 1){
    sz[v] = 1;
    for(auto &i : g[v]){
        dep[i] = dep[v] + 1;
        dfs1(i); sz[v] += sz[i];
        if(sz[i] > sz[g[v][0]]) swap(i, g[v][0]);
    }
}
void dfs2(int v = 1){
    in[v] = ++pv;
    for(auto i : g[v]){
        top[i] = i == g[v][0] ? top[v] : i;
        dfs2(i);
    }
}

void update(int s, int e, int x){
    while(top[s] ^ top[e]){
        if(dep[top[s]] < dep[top[e]]) swap(s, e);
        seg_update(in[top[s]], in[s], x);
        s = par[top[s]];
    }
    if(dep[s] > dep[e]) swap(s, e);
    seg_update(in[s], in[e], x);
}

ll query(int s, int e){
    Node t1, t2;
    if(in[s] > in[e]) swap(s, e);
    while(top[s] ^ top[e]){
        if(dep[top[s]] > dep[top[e]]){
            t1 = merge(seg_query(in[top[s]], in[s]), t1);
            s = par[top[s]];
        }else{
            t2 = merge(seg_query(in[top[e]], in[e]), t2);
            e = par[top[e]];
        }
    }
    if(dep[s] > dep[e]) t1 = merge(seg_query(in[e], in[s]), t1);
    else t2 = merge(seg_query(in[s], in[e]), t2);
    swap(t1.l, t1.r);
    return merge(t1, t2).mx;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n; top[1] = 1;
    for(int i=1; i<=n; i++) cin >> arr[i];
    for(int i=1; i<n; i++){
        int s, e; cin >> s >> e;
        inp[s].push_back(e); inp[e].push_back(s);
    }
    dfs(); dfs1(); dfs2();
    for(int i=0; i<(1 << 18); i++) tmp[i] = inf;
    for(int i=1; i<=n; i++) seg_update(in[i], in[i], arr[i]);

    cin >> q;
    while(q--){
        int op, s, e; cin >> op >> s >> e;
        if(op == 1){
            cout << query(s, e) << "\n";
        }else{
            int x; cin >> x;
            update(s, e, x);
        }
    }
}