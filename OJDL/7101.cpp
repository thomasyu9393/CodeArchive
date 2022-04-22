#include <bits/stdc++.h>
using namespace std;
#define jass_FHVirus_8e7_Orz ios_base::sync_with_stdio(false), cin.tie(0);
#define int long long
const int N = 1000010;

int a[N];
int l, r, k;
inline int calc(int x){
	if(x < 0) return 1LL<<60;
	if(x < l || r <= x) return a[x];
	int ret = (l ? a[l-1] : 0);
	int orz = x-l+1;
	ret += a[r] - (r >= orz ? a[r-orz] : 0);
	return ret;
}

signed main(){
	jass_FHVirus_8e7_Orz
	int n;
	cin >> n;
	for(int i=0 ; i<n ; ++i)
		cin >> a[i], a[i] += (i ? a[i-1] : 0);
	int q;
	cin >> q;
	while(q--){
		cin >> l >> r >> k;
		int ll = 0, rr = n;
		int pl = -1, pr = -1;
		bool ok = false;
		while(ll < rr){
			if(ll == rr-1){
				int ret = calc(rr-1);
				cout << (ret <= k ? rr : ll) << '\n';
				ok = true;
				break;
			}
			int mm = (ll+rr)>>1;
			int ret = calc(mm-1);
			if(ret <= k) ll = mm;
			else rr = mm-1;
		}
		if(!ok) cout << ll << '\n';
	}
}
