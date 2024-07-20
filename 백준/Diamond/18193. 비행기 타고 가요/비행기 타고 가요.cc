#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
const ll LNF = 1e18 + 7;

int main() {
	fastio;
	int n, m, k, sz = 1; cin >> n >> m >> k;
	while (sz < n) sz <<= 1;
	--k |= sz;

	vector<vector<pll>> adj(sz << 2);
	for (int i = 1; i < sz; i++) {
		adj[i].push_back({ 0, i << 1 });
		adj[i].push_back({ 0, i << 1 | 1 });
	}
	for (int i = sz; i < sz << 1; i++) {
		adj[i].push_back({ 0, i + (sz << 1) });
	}
	for (int i = 1; i < sz; i++) {
		adj[(i << 1) + (sz << 1)].push_back({ 0, i + (sz << 1) });
		adj[(i << 1 | 1) + (sz << 1)].push_back({ 0, i + (sz << 1) });
	}

	while (m--) {
		int cost, a, b, c, d; cin >> cost >> a >> b >> c >> d;
		--a |= sz, --b |= sz, --c |= sz, --d |= sz;
		adj.push_back(vector<pll>{});
		while (a <= b) {
			if (a & 1) adj[a + (sz << 1)].push_back({ 0, adj.size() - 1 }), a++;
			if (~b & 1) adj[b + (sz << 1)].push_back({ 0, adj.size() - 1 }), b--;
			a >>= 1, b >>= 1;
		}
		while (c <= d) {
			if (c & 1) adj.back().push_back({ cost, c }), c++;
			if (~d & 1) adj.back().push_back({ cost, d }), d--;
			c >>= 1, d >>= 1;
		}
	}

	vector<ll> dist(adj.size(), LNF);
	priority_queue<pll, vector<pll>, greater<pll>> PQ;
	dist[k + (sz << 1)] = 0;
	PQ.push({ dist[k + (sz << 1)], k + (sz << 1) });
	while (!PQ.empty()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (auto [ndist, nxt] : adj[cur]) {
			if (dist[nxt] > cdist + ndist) {
				dist[nxt] = cdist + ndist;
				PQ.push({ dist[nxt], nxt });
			}
		}
	}

	for (int i = 3 * sz; i < 3 * sz + n; i++) {
		cout << (dist[i] == LNF ? -1 : dist[i]) << ' ';
	}
	cout << '\n';
}