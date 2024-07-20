#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;
using pii = pair<int, int>;

template<size_t sz = 1 << 11>
struct SegTree {
	vector<int> tree, lazy;
	SegTree() : tree(sz << 1, INF), lazy(sz << 1, INF) {}
	void Push(int node, int L, int R) {
		if (node < sz) for (const int nxt : { node << 1, node << 1 | 1 }) lazy[nxt] = min(lazy[nxt], lazy[node]);
		tree[node] = min(tree[node], lazy[node]), lazy[node] = INF;
	}
	void Update(int l, int r, int val, int node = 1, int L = 1, int R = sz) {
		Push(node, L, R);
		if (r < L || R < l) return;
		if (l <= L && R <= r) { lazy[node] = min(lazy[node], val), Push(node, L, R); return; }
		int mid = L + R >> 1;
		Update(l, r, val, node << 1, L, mid);
		Update(l, r, val, node << 1 | 1, mid + 1, R);
		tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
	}
	int Query(int l, int r, int node = 1, int L = 1, int R = sz) {
		Push(node, L, R);
		if (r < L || R < l) return INF;
		if (l <= L && R <= r) return tree[node];
		int mid = L + R >> 1;
		return min(Query(l, r, node << 1, L, mid), Query(l, r, node << 1 | 1, mid + 1, R));
	}
};

int n, m, st, en, k, v[2001], inv[2001];
int par_st[2001], par_en[2001];
int dist_st[2001], dist_en[2001];
vector<pii> adj[2001];

void Dijkstra(int dist[], int st) {
	memset(dist + 1, 0x3f, n << 2);
	priority_queue<pii, vector<pii>, greater<pii>> PQ;
	PQ.push({ dist[st] = 0, st });
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (const auto& [nxt, cost] : adj[cur]) {
			if (dist[nxt] > cdist + cost)
				PQ.push({ dist[nxt] = cdist + cost, nxt });
		}
	}
}

void DFS(int par[], int dist[], int cur, int prv, int t) {
	if (par[cur]) return;
	if (inv[cur]) t = cur; par[cur] = t;
	for (const auto& [nxt, cost] : adj[cur]) {
		if (nxt == prv || dist[cur] + cost != dist[nxt]) continue;
		if (!inv[cur] && inv[nxt]) continue;
		DFS(par, dist, nxt, cur, t);
	}
}

int main() {
	fastio;
	cin >> n >> m >> st >> en;
	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}
	cin >> k;
	for (int i = 1; i <= k; i++) cin >> v[i], inv[v[i]] = i;

	Dijkstra(dist_st, st); Dijkstra(dist_en, en);
	DFS(par_st, dist_st, v[1], -1, v[1]);
	DFS(par_en, dist_en, v[k], -1, v[k]);

	SegTree<1 << 11> ST;
	for (int i = 1; i <= n; i++) for (const auto& [j, cost] : adj[i]) {
		if (inv[i] && inv[j] && abs(inv[i] - inv[j]) <= 1) continue;
		const int t1 = inv[par_st[i]];
		const int t2 = inv[par_en[j]];
		ST.Update(t1, t2 - 1, dist_st[i] + cost + dist_en[j]);
	}
	for (int i = 1; i < k; i++) {
		const int ans = ST.Query(i, i);
		cout << (ans == INF ? -1 : ans) << '\n';
	}
}