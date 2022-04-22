#include <iostream>
#include <cstring>
using namespace std;
using ll = long long;

ll bit[100010], p[100010];
void MO(int x, int n){
	for(; x<=n ; x+=x&-x)
		bit[x]++;
}
ll QU(int x){
	ll ret = 0;
	for(; x>0 ; x-=x&-x) ret += bit[x];
	return ret;
}
int main(){
	ios_base::sync_with_stdio(false), cin.tie(0);
	memset(p, -1, sizeof(p));
	int n, h;
	cin >> n;
	ll ans = 0;
	for(int i=1 ; i<=(n<<1) ; ++i){
		cin >> h;
		ll tmp = QU(h-1);
		if(~p[h]) ans += tmp - p[h];
		MO(h, n), p[h] = tmp;
	}
	cout << ans << '\n';
}
