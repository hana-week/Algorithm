#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;

typedef long long ll;

int n;
int a[101010];
vector<int> comp;
vector<int> g[101010];

struct SplayTree{
    struct Node{
        Node *l, *r, *p;
        int sz, v, flip, dummy;
        Node() : Node(0, nullptr) {}
        Node(int v) : Node(v, nullptr) {}
        Node(int v, Node *p) : v(v), p(p) { l = r = nullptr; sz = flip = dummy = 0; }
        ~Node(){
            if(l) delete l;
            if(r) delete r;
        }
    };

    Node *root, *ptr[101010];
    SplayTree() : root(nullptr) { memset(ptr, 0, sizeof ptr); }
    ~SplayTree(){ if(root) delete root; }
    void init(){
        if(root) delete root;
        ptr[0] = root = new Node(-1e9); //left dummy node
        auto now = root;
        for(int i=1; i<=n; i++){
            ptr[a[i]] =  now->r = new Node(a[i], now);
            now = now->r;
        }
        ptr[n+1] = now->r = new Node(1e9, now); //right dummy node
        root->dummy = now->r->dummy = 1;
        for(int i=n+1; ~i; i--) update(ptr[i]);
    }

    // basic operation
    void rotate(Node *x){
        auto p = x->p;
        Node *y;
        push(p); push(x);
        if(x == p->l) p->l = y = x->r, x->r = p;
        else p->r = y = x->l, x->l = p;
        x->p = p->p; p->p = x;
        if(y) y->p = p;
        if(x->p){
            if(p == x->p->l) x->p->l = x;
            else x->p->r = x;
        }
        else root = x;
        update(p); update(x);
    }
    void splay(Node *x, Node *g = nullptr){
        Node *y;
        while(x->p != g){
            Node *p = x->p;
            if(p->p == g){ rotate(x); break; }
            auto pp = p->p;
            if((p->l == x) == (pp->l == p)) rotate(p);
            else rotate(x);
            rotate(x);
        }
        if(!g) root = x;
    }
    void update(Node *x){
        x->sz = 1;
        if(x->l) x->sz += x->l->sz;
        if(x->r) x->sz += x->r->sz;
    }
    void push(Node *x){
        if(!x->flip) return;
        swap(x->l, x->r);
        if(x->l) x->l->flip = !x->l->flip;
        if(x->r) x->r->flip = !x->r->flip;
        x->flip = 0;
    }

    // additional operation
    Node* gather(int s, int e){ //gather [s, e]
        kth(e+1);
        auto tmp = root;
        kth(s-1);
        splay(tmp, root);
        return root->r->l;
    }
    void flip(int s, int e){
        Node *x = gather(s, e);
        x->flip = !x->flip;
    }
    int getidx(int k){
        splay(ptr[k]);
        return root->l->sz;
    }

    void kth(int k){ //1-based
        auto now = root;
        push(now);
        while(1){
            while(now->l && now->l->sz > k) now = now->l, push(now);
            if(now->l) k -= now->l->sz;
            if(!k) break; k--;
            now = now->r;
            push(now);
        }
        splay(now);
    }
};

void input(){
    comp.clear(); comp.reserve(n);
    for(int i=1; i<=n; i++) cin >> a[i], comp.push_back(a[i]);
    compress(comp);
    for(int i=0; i<comp.size(); i++) g[i].clear();
    for(int i=1; i<=n; i++){
        a[i] = lower_bound(all(comp), a[i]) - comp.begin();
        g[a[i]].push_back(i);
    }
    int pv = 0;
    for(int i=0; i<comp.size(); i++){
        for(auto j : g[i]) a[j] = ++pv;
    }
}

void solve(){
    input();
    SplayTree tree;
    tree.init();
    for(int i=1; i<=n; i++){
        int t = tree.getidx(i);
        cout << t << " ";
        tree.flip(i, t);
    }
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    while(1){
        cin >> n; if(!n) return 0;
        solve();
    }
}