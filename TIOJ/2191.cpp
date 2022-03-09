#include <iostream>
#include <algorithm>
using namespace std;
inline int ab(int x){return x < 0 ? -x : x;}
inline void chmax(int &a, int b){a = (a < b ? b : a);}
inline void chmin(int &a, int b){a = (a > b ? b : a);}

struct Point{
	int x, y, w;
} pnts[300005];

signed main(){
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	for(int i=0 ; i<n ; ++i){
		int x, y, w;
		cin >> x >> y >> w;
		int z = ab(__gcd(x, y));
		x /= z, y /= z;
		if(y < 0) x = -x, y = -y;
		pnts[i] = {x, y, w};
	}
	sort(pnts, pnts + n, [&](Point &a, Point &b){
		return 1ll * a.x * b.y > 1ll * a.y * b.x;
	});
	int arr[300005];
	arr[0] = pnts[0].w;
	int ind = 1, lx = pnts[0].x, ly = pnts[0].y;
	for(int i=1 ; i<n ; ++i){
		auto [x, y, w] = pnts[i];
		if(1ll * lx * y != 1ll * ly * x){
			arr[ind++] = w;
			lx = x, ly = y;
		}
		else{
			arr[ind - 1] += w;
		}
	}
	int mx = 0, mn = 0, sum = 0;
	int pre1 = 0, now1, pre2 = 0, now2;
	for(int i=0 ; i<ind ; ++i){
		now1 = arr[i] + (pre1 > 0 ? pre1 : 0);
		now2 = arr[i] + (pre2 < 0 ? pre2 : 0);
		sum += arr[i];
		chmax(mx, now1);
		chmin(mn, now2);
		pre1 = now1, pre2 = now2;
	}
	chmax(mx, sum - mn);
	chmax(mx, 0);
	cout << mx << '\n';
	return 0;
}
