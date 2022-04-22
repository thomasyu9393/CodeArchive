#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;
#define ll long long
using pii = pair<int, int>;
#define F first
#define S second
const int N = 200001;

pii cut[N];

pii tr[N<<2];
void init(int l, int r, int o){
	if(l == r){
		tr[o] = {cut[l].S, l};
		return;
	}
	int m = (l + r) >> 1;
	init(l, m, o<<1);
	init(m+1, r, o<<1|1);
	if(tr[o<<1].F < tr[o<<1|1].F){
		tr[o] = tr[o<<1];
	}
	else{
		tr[o] = tr[o<<1|1];
	}
}
pii query(int ql, int qr, int l, int r, int o){
	if(ql > r || qr < l) return {1<<30, -1};
	if(ql <= l && r <= qr) return tr[o];
	int m = (l + r) >> 1;
	pii L = query(ql, qr, l, m, o<<1);
	pii R = query(ql, qr, m+1, r, o<<1|1);
	return (L.F < R.F ? L : R);
}

int n, l;
ll DQ(int l, int r, int i, int j){
	if(i > j) return 0;
	int p = query(i, j, 0, n - 1, 1).S;
	int L = DQ(l, cut[p].F, i, p - 1);
	int R = DQ(cut[p].F, r, p + 1, j);
	return (r - l) + L + R;
}
int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> l;
	for(int i=0 ; i<n ; ++i){
		cin >> cut[i].F >> cut[i].S;
	}
	sort(cut, cut + n, [&](pii &i, pii &j){
		return i.F < j.F;
	});
	init(0, n - 1, 1);
	cout << DQ(0, l, 0, n - 1) << '\n';
}
