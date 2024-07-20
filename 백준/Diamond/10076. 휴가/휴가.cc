#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MXN = 1e5;
struct Node {
    int l, r; 
    ll sum;
    int cnt;
    Node() : cnt(0), sum(0) {};
};
vector<ll> v;
vector<int> a;
vector<int> roots(MXN+1);
int N, S, D;
vector<Node> tree(MXN*20);
ll ans;
int node_cnt;
void init() {
    node_cnt = v.size() * 2;
    for(int i=1;i<v.size();++i) {
        tree[i].cnt = tree[i].sum = 0;
        tree[i].l = i << 1;
        tree[i].r = i << 1 | 1;
    }
}

void update(int node, int s, int e, int idx, ll val) {
    tree[node].cnt += val;
    tree[node].sum += val * v[idx];
    if(s != e) {
        int mid = s + e >> 1;
        int n1 = tree[node].l, n2 = tree[node].r;
        if(idx <= mid) {
            tree[node_cnt] = tree[n1];
            tree[node].l = node_cnt++;
            update(tree[node].l, s, mid, idx, val);
        }
        else {
            tree[node_cnt] = tree[n2];
            tree[node].r = node_cnt++;
            update(tree[node].r, mid+1, e, idx, val);
        }
    }
}

ll query(int s, int e, int k) {
    int l = 0, r = v.size() - 1;
    ll ret = 0;
    while(l != r) {
        int mid = l + r >> 1;
        int lsz = tree[tree[e].l].cnt - tree[tree[s].l].cnt;
        ll lsum = tree[tree[e].l].sum - tree[tree[s].l].sum;
        if(lsz >= k) {
            s = tree[s].l; e = tree[e].l;
            r = mid;
        }
        else {
            ret += lsum;
            k -= lsz;
            s = tree[s].r; e = tree[e].r;
            l = mid + 1;
        }
    }
    assert(l == r);
    ret += v[l] * min(k, (int)tree[e].cnt - (int)tree[s].cnt);
    return ret;
}

void make_tree() {
    roots[0] = 1;
    for(int i=1;i<=N;++i) {
        roots[i] = node_cnt;
        tree[node_cnt++] = tree[roots[i-1]];
        update(roots[i], 0, v.size()-1, a[i], 1);
    }
}

void dnc(int s, int e, int opts, int opte) {
    if(s > e) return ;
    ll ret = 0;
    int opt_mid = opts;
    int mid = s+e >> 1;
    for(int i=opts;i<=opte;++i) {
        int k = max(0, D - S - i + 2*mid);
        k = min(k, i - mid + 1);
        ll tmp = query(roots[mid-1], roots[i], k);
        if(tmp > ret) {
            ret = tmp; opt_mid = i;
        }
    }
    ans = max(ret, ans);
    dnc(s, mid-1, opts, opt_mid);
    dnc(mid+1, e, opt_mid, opte);
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    cin >> N >> S >> D; ++S;
    a.resize(N+1);
    for(int i=1;i<=N;++i) {
        cin >> a[i]; v.push_back(a[i]);
    }
    sort(v.begin(), v.end(), greater<ll>());
    v.erase(unique(v.begin(), v.end()), v.end());
    for(int i=1;i<=N;++i) a[i] = lower_bound(v.begin(), v.end(), a[i], greater<ll>()) - v.begin();
    init();
    make_tree();
    dnc(1, S, S, N);
    reverse(a.begin()+1, a.begin()+N+1); S = N - S + 1;
    init();
    make_tree();
    dnc(1, S, S, N);
    cout << ans << '\n';
    return 0;
}