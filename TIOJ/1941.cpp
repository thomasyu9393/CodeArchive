#include <iostream>
using namespace std;
const int maxn = 800005;

struct BIT{
	int tr[maxn]{}, n;
	void init(int _n){
		n = _n;
	}
	int query(int x){
		int res = 0;
		for(; x>0 ; x-=x&-x)
			res += tr[x];
		return res;
	}
	void upd(int x, int v){
		for(; x<=n ; x+=x&-x)
			tr[x] += v;
	}
	int find(int t){
		int v = query(t);
		int l = t + 1, r = n;
		while(l < r){
			int mid = (l + r) / 2;
			if(query(mid) <= v)
				l = mid + 1;
			else
				r = mid;
		}
		return query(l) > v ? l : -1;
	}
} bit;

int main(){
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	bit.init(n);
	for(int i=0 ; i<n ; ++i){
		int s, t;
		cin >> s >> t;
		s++, t++;
		int p = bit.find(t);
		bit.upd(s, 1);
		if(~p)
			bit.upd(p, -1);
	}
	cout << bit.query(n) << '\n';
}
