#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define ll long long
#define F first
#define S second
#define eb emplace_back
#define iter(x) x.begin(), x.end()
const int N = 200001;

struct BIT{
	int tr[N]{};
	void MO(int x, int v){
		for(; x<N ; x+=x&-x)
			tr[x] = max(tr[x], v);
	}
	int QU(int x){
		int res = 0;
		for(; x>0 ; x-=x&-x)
			res = max(res, tr[x]);
		return res;
	}
} bit;

pii p[N];
int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n;
	cin >> n;
	vector<int> v;
	for(int i=0 ; i<n ; ++i){
		cin >> p[i].F >> p[i].S;
		v.eb(p[i].S);
	}
	sort(iter(v));
	v.resize(unique(iter(v)) - v.begin());
	for(int i=0 ; i<n ; ++i){
		p[i].S = upper_bound(iter(v), p[i].S) - v.begin();
	}
	sort(p, p + n);
	for(int i=0 ; i<n ; ++i){
		bit.MO(p[i].S, bit.QU(p[i].S) + 1);
	}
	cout << bit.QU(n) << '\n';
}
