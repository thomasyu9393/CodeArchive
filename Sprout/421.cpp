#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 200005;

struct BIT{
	int tr[maxn]{}, n;
	void init(int _n){
		n = _n;
		for(int i=1 ; i<=n ; ++i)
			tr[i] = 0;
	}
	void upd(int x, int v){
		for(; x<=n ; x+=x&-x)
			tr[x] = max(tr[x], v);
	}
	int query(int x){
		int res = 0;
		for(; x>0 ; x-=x&-x)
			res = max(res, tr[x]);
		return res;
	}
} bit;

int main(){
	ios_base::sync_with_stdio(false), cin.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n, m;
		cin >> n >> m;
		vector<pair<int, int>> a;
		vector<int> u;
		u.eb(m);
		for(int i=0 ; i<n ; ++i){
			int x;
			cin >> x;
			a.eb(x, x * 2);
			u.eb(x);
			u.eb(x * 2);
		}
		sort(iter(u));
		m = upper_bound(iter(u), m) - begin(u);
		bit.init(n * 2 + 1);
		for(auto &[ff, ss]: a){
			ff = upper_bound(iter(u), ff) - begin(u);
			ss = upper_bound(iter(u), ss) - begin(u);
			if(ss >= m)
				bit.upd(ss, bit.query(ss) + 1);
			if(ff >= m)
				bit.upd(ff, bit.query(ff) + 1);
		}
		cout << bit.query(n * 2 + 1) << '\n';
	}
}
