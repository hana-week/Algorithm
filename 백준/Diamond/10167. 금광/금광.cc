#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const ll INF = 1e14;
const int MAXN = (1<<12);

int n;
struct abc {
    int x, y; ll w;
    bool operator <(abc &a)const {
        if (x == a.x) return y < a.y;
        return x < a.x;
    }
} a[MAXN+5];

ll t[MAXN+5];
struct node {
    int s, e;
    ll mmax, lmax, rmax;
} tree[MAXN*4+5];

void t_udpate(int i, ll x) { // point update
    for (; i<=n; i+=i&-i) t[i]+=x;
}

ll t_query(int s, int e) { // range sum [s, e]
    ll r1 = 0, r2 = 0;
    for (; e; e-=e&-e) r1+=t[e];
    for (--s; s; s-=s&-s) r2+=t[s];
    return r1-r2;
}

void update(int now) {
    int idx = a[now].y+MAXN-1;
    t_udpate(a[now].y, a[now].w);
    ll tmp = (tree[idx].mmax == -INF ? INF+a[now].w : a[now].w);
    tree[idx].mmax += tmp;
    tree[idx].lmax += tmp;
    tree[idx].rmax += tmp;
    idx /= 2;
    while (idx) {
        auto &l = tree[idx*2], &r = tree[idx*2+1], &m = tree[idx];
        m.mmax = max({ l.mmax, r.mmax, l.lmax+r.rmax });
        m.lmax = max(r.lmax, l.lmax+t_query(r.s, r.e));
        m.rmax = max(l.rmax, r.rmax+t_query(l.s, l.e));
        idx /= 2;
    }
}

int main() {
    scanf("%d", &n);
    vector<int> vx, vy;
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %lld", &a[i].x, &a[i].y, &a[i].w);
        vx.push_back(a[i].x); vy.push_back(a[i].y);
    }
    sort(vx.begin(), vx.end());
    sort(vy.begin(), vy.end());
    for (int i = 1; i <= n; i++) {
        a[i].x = lower_bound(vx.begin(), vx.end(), a[i].x)-vx.begin()+1;
        a[i].y = lower_bound(vy.begin(), vy.end(), a[i].y)-vy.begin()+1;
    }
    sort(a+1, a+1+n);
    tree[1].s = 1, tree[1].e = MAXN;
    for (int i = 2; i <= MAXN*4; i++) {
        int s = tree[i/2].s, e = tree[i/2].e;
        if (i%2) s = (s+e)/2+1;
        else e = (s+e)/2;
        tree[i] = { s,e,-INF,-INF,-INF };
    }

    ll dap = -INF;
    int chk[3333] = {};
    for (int i = 1; i <= n; i++) {
        if (a[i-1].x != a[i].x) chk[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        if (!chk[i]) continue;
        ll cur = -INF;
        for (int j = i; j <= n; j++) {
            update(j);
            if (chk[j+1] || j == n) cur = max(cur, tree[1].mmax);
        }
        dap = max(dap, cur);
        for (int i = 1; i <= MAXN*2; i++) {
            tree[i].mmax = tree[i].lmax = tree[i].rmax = -INF;
            if (i <= MAXN) t[i] = 0;
        }
    }

    printf("%lld\n", dap);

    return 0;
}