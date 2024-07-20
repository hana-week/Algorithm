#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

struct line { //y = a*x + b
    ll a,b;
};
 
struct cht {
    int s = 0, e = 0;
    int idx[1000001];
    line deq[1000001];
    double cross(int a, int b) {
        return 1.0 * (deq[a].b - deq[b].b) / (deq[b].a - deq[a].a);
    }
    void insert(line v, int line_idx) {
        deq[e] = v;
        idx[e] = line_idx;
        while (s + 1 < e && cross(e - 2, e - 1) > cross(e - 1, e)) {
            deq[e - 1] = deq[e];
            idx[e - 1] = idx[e];
            e--;
        }
        e++;
    }
    pll query(ll x) {
        int l = 0, r = e - 1;
        while (l != r) {
            int m = (l + r) / 2;
            if (cross(m, m + 1) <= x) l = m + 1;
            else r = m;
        }
        return pll(deq[l].a * x + deq[l].b, idx[l]);
    }
    void clear() { s = e = 0; }
}CHT;

int main() {
	fastio;
	ll n, a, b, c; cin >> n >> a >> b >> c;
	vector<ll> v(n), pSum(n), dp(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		pSum[i] = (i ? pSum[i - 1] : 0) + v[i];
	}
	dp[0] = a * v[0] * v[0] + b * v[0] + c;
	for (int i = 1; i < n; i++) {
		ll X = pSum[i], Y = pSum[i - 1];
        CHT.insert({ -2 * a * Y, a * Y * Y - b * Y + dp[i - 1] }, i - 1);
		dp[i] = max(CHT.query(X).first, 0LL) + a * X * X + b * X + c;
	}
	cout << dp.back() << '\n';
}