#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define eb emplace_back
const int maxn = 100005;

struct Node{
	ll val, sum;
	int cnt, rank;
	Node *l = NULL, *r = NULL;
	Node(ll v): val(v), sum(v), cnt(1), rank(1){}
	void pull(){
		sum = (l ? l->sum : 0) + (r ? r->sum : 0) + val;
		cnt = (l ? l->cnt : 0) + (r ? r->cnt : 0) + 1;
		if(l && r){
			if(l->rank < r->rank) swap(l, r);
			rank = r->rank + 1;
		}
		else{
			if(r) swap(l, r);
			rank = 1;
		}
	}
};
Node* merge(Node *a, Node *b){
	if(!a) return b;
	if(!b) return a;
	if(a->val < b->val) swap(a, b);
	a->r = merge(a->r, b);
	a->pull();
	return a;
}
void pop(Node *&p){
	Node *n = merge(p->l, p->r);
	delete p;
	p = n;
}

ll lim, ans = 0;
vector<int> g[maxn];
ll cost[maxn], lead[maxn];
void dfs(int u, Node *&p){
	p = merge(p, new Node(cost[u]));
	for(int v: g[u]){
		Node *n = NULL;
		dfs(v, n);
		p = merge(p, n);
	}
	while(p && p->sum > lim) pop(p);
	ans = max(ans, lead[u] * p->cnt);
}

int main(){
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, rt;
	cin >> n >> lim;
	for(int i=0 ; i<n ; ++i){
		int b;
		cin >> b >> cost[i] >> lead[i];
		if(b)
			g[b - 1].eb(i);
		else
			rt = i;
	}
	Node *Leftist = NULL;
	dfs(rt, Leftist);
	cout << ans << '\n';
	return 0;
}
