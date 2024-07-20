#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<deque>
#include<set>
#include<map>
#include<math.h>
#include<algorithm>
using namespace std;

#define INF 987654321
#define ll long long

struct Query {
	int l, r, val;
	bool operator< (Query &n)
	{
		return val < n.val;
	}
};

struct Query2 {
	int l, r;
	ll val;
};

struct SEG {
	int l, r, a;
	ll b;
};

int N, M, Q, P, X = 1; //P=세그인덱스, X=pst인덱스
int n2ov[100101], n2ot[600601]; //n2ov=val, n2ot=[L,R](time)
vector<Query> v;
vector<Query2> q;
vector<pair<pair<int, int>, pair<int, int> > > w;
//w : 직선의 방정식으로 바뀐 쿼리 (시간,val,기울기,y절편)
int pst[600601], e[600601];
vector<SEG> seg(1, { 0,0,0,0 });
vector<int> com, change(100101);
map<int, int> m;

int Init(int l, int r)
{
	int n = seg.size();
	seg.push_back({ 0,0,0,0 });
	if (l == r) return n;

	int mid = l + r >> 1;
	seg[n].l = Init(l, mid);
	seg[n].r = Init(mid + 1, r);
	return n;
}

int Update(int prv, int idx, int a, int b, int l, int r)
{
	if (r < idx || idx < l) return prv;
	int n = seg.size();
	seg.push_back({ 0,0,0,0 });
	if (l == r && l == idx)
	{
		seg[n].a = seg[prv].a + a;
		seg[n].b = seg[prv].b + b;
		return n;
	}
	int mid = l + r >> 1;
	seg[n].l = Update(seg[prv].l, idx, a, b, l, mid);
	seg[n].r = Update(seg[prv].r, idx, a, b, mid + 1, r);
	seg[n].a = seg[seg[n].l].a + seg[seg[n].r].a;
	seg[n].b = seg[seg[n].l].b + seg[seg[n].r].b;
	return n;
}

int kth(int Lt, int Rt, int L, int R, ll k, int l, int r)
{
	if (l == r) return l;

	int nL = seg[L].l, nR = seg[R].l;
	ll right = (ll)seg[nR].a * Rt + seg[nR].b;
	ll left = (ll)seg[nL].a * Lt + seg[nL].b;
	int mid = l + r >> 1;
	if (right - left >= k) return kth(Lt, Rt, nL, nR, k, l, mid);
	return kth(Lt, Rt, seg[L].r, seg[R].r, k - (right - left), mid + 1, r);
}

int main()
{
	scanf("%d %d %d", &N, &M, &Q);
	v.resize(M);
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d", &v[i].l, &v[i].r, &v[i].val);
		com.push_back(v[i].l);
		com.push_back(v[i].r);
		com.push_back(v[i].r + 1); //틀린 이유. 따로 압축해줘야 한다.
	}

	//val에 대한 좌표 압축
	sort(v.begin(), v.end());
	for (int i = 0; i < M; i++)
	{
		if (i > 0 && v[i - 1].val != v[i].val) P++;
		n2ov[P] = v[i].val;
		change[i] = P; //i-1번째 인덱스를 비교하는데 좌표압축을 동시에 하면 안 된다.
	}

	for (int i = 0; i < M; i++)
		v[i].val = change[i];

	vector<int>().swap(change);

	q.resize(Q);
	for (int i = 0; i < Q; i++)
	{
		scanf("%d %d %lld", &q[i].l, &q[i].r, &q[i].val);
		q[i].l--;
		com.push_back(q[i].l);
		com.push_back(q[i].r);
	}

	//L,R에 대한 좌표 압축
	sort(com.begin(), com.end());
	for (int i = 0; i < com.size(); i++)
	{
		if (i > 0 && com[i - 1] != com[i]) X++;
		if (i == 0 || com[i - 1] != com[i])
		{
			m[com[i]] = X;
			n2ot[X] = com[i];
		}
	}

	vector<int>().swap(com);

	for (int i = 0; i < M; i++)
	{
		v[i].l = m[v[i].l];
		v[i].r = m[v[i].r];
	}
	for (int i = 0; i < Q; i++)
	{
		q[i].l = m[q[i].l];
		q[i].r = m[q[i].r];
	}

	map<int, int>().swap(m);

	//더미 쿼리 추가!! 아주 중요함!! e[q[i].l]에서 참조할 때 있어야 하기 때문
	for (int i = 0; i < Q; i++)
	{
		w.push_back({ { q[i].l, 0 }, { 0, 0 } });
		w.push_back({ { q[i].r, 0 }, { 0, 0 } });
	}

	//쿼리를 직선의 방정식으로 바꾸기
	for (int i = 0; i < M; i++)
	{
		w.push_back({ {v[i].l, v[i].val}, { 1, -n2ot[v[i].l] + 1 } });
		w.push_back({ {v[i].r + 1, v[i].val}, { -1, n2ot[v[i].r] } });
	}
	sort(w.begin(), w.end());

	vector<Query>().swap(v);
	seg.reserve(20000000);

	// PST 구축
	pst[0] = Init(0, P);
	int p = 1;
	for (int i = 0; i < w.size(); i++)
	{
		e[w[i].first.first] = max(e[w[i].first.first], p - 1); //1~x 쿼리, e[x]번째 pst까지 봐줘야 함을 의미

		int vv = w[i].first.second, a = w[i].second.first, b = w[i].second.second;
		if (a == 0 && b == 0) continue;
		pst[p] = Update(pst[p - 1], vv, a, b, 0, P); //shift

		e[w[i].first.first] = p; //continue문 때문에 두 개로 분산시킴
		p++; //서순
	}

	vector<pair<pair<int, int>, pair<int, int> > >().swap(w);

	for (int i = 0; i < Q; i++)
	{
		printf("%d\n", n2ov[kth(n2ot[q[i].l], n2ot[q[i].r], pst[e[q[i].l]], pst[e[q[i].r]], q[i].val, 0, P)]);
	}

	return 0;
}