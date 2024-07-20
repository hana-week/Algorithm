#include <bits/stdc++.h>
#define eb emplace_back
#define em emplace
#define all(v) v.begin(), v.end()
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef pair <int, ll> pii;
typedef pair <ll, ll> pll;

const int MAX = 303030;
const int INF = (int)1e9;
const ll LINF = (ll)9e18;


struct LiChaoSegmentTree { // [s, e)
    struct Node {
        Node *l = nullptr, *r = nullptr;
        pll val;
        Node(pll val) : val(val) {}
    } *tree = nullptr;

    ll cal(pll l, ll x) {
        return l.fi * x + l.se;
    }
    void add_line(Node *node, pll val, ll s = -INF, ll e = INF + 1) { // modify s & e
        ll m = s + e >> 1;
        bool left = cal(val, s) > cal(node->val, s); // > if max
        bool mid = cal(val, m) > cal(node->val, m); // > if max
        if(mid) swap(val, node->val);
        if(e == s + 1) return;
        if(left != mid) {
            if(!node->l) node->l = new Node(val);
            else add_line(node->l, val, s, m);
        }
        else {
            if(!node->r) node->r = new Node(val);
            else add_line(node->r, val, m, e);
        }
    }

    void add(pll val) {
        if(!tree) tree = new Node(val);
        else add_line(tree, val);
    }

    ll query(Node *node, ll x, ll s = -INF, ll e = INF + 1) { // modify s & e
        if(!node) return -LINF; // -LINF if max
        ll m = s + e >> 1;
        if(e == s + 1) return cal(node->val, x);
        if(x < m) return max(cal(node->val, x), query(node->l, x, s, m));
        else return max(cal(node->val, x), query(node->r, x, m, e));
    }

    ll query(ll x) {
        if(!tree) return -LINF; // -LINF if max
        return query(tree, x);
    }
};

class SEG {
    vector <LiChaoSegmentTree> tree;
    int n;
public :
    void Init(int N) {
        n = N;
        tree.resize(4*n);
    }

    void update(int l, int r, pii val, int s, int e, int node = 1) {
        if(s > r || e < l) return;
        if(s >= l && e <= r) {
            tree[node].add(val);
            return;
        }
        int m = (s + e) / 2;
        update(l, r, val, s, m, node * 2);
        update(l, r, val, m + 1, e, node * 2 + 1);
    }

    void Update(int l, int r, pii val) {
        update(l, r, val, 1, n);
    }

    ll cal_max(int k, int x, int s, int e, int node = 1) {
        if(k == 0) return -LINF;
        if(s == e) return tree[node].query(x);
        int m = (s + e) / 2;
        if(k <= m) return max(tree[node].query(x), cal_max(k, x, s, m, node * 2));
        else return max(tree[node].query(x), cal_max(k, x, m + 1, e, node * 2 + 1));
    }

    ll Cal_max(int k, int x) {
        return cal_max(k, x, 1, n);
    }
} ST;

pii line[MAX];
bool chk[MAX];
vector <pii> pt;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    ST.Init(n);
    for(int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        if(t == 1) {
            cin >> line[i].fi >> line[i].se;
            chk[i] = true;
        }
        if(t == 2) {
            int x;
            cin >> x;
            ST.Update(x, i, line[x]);
            chk[x] = false;
        }
        if(t == 3) {
            int x;
            cin >> x;
            pt.eb(i, x);
        }
    }
    for(int i = 1; i <= n; i++) {
        if(chk[i]) ST.Update(i, n, line[i]);
    }
    for(auto i : pt) {
        ll ans = ST.Cal_max(i.fi, i.se);
        if(ans == -LINF) cout << "EMPTY" << '\n';
        else cout << ans << '\n';
    }
}