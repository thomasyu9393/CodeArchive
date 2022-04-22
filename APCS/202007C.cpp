#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long

ll p[400001];
int main(){
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0 ; i<n ; ++i){
		cin >> p[i];
		p[i + n] = p[i];
		p[i] += (i ? p[i-1] : 0);
	}
	for(int i=n ; i<(n<<1) ; ++i){
		p[i] += p[i-1];
	}
	int now = 0;
	while(m--){
		ll q;
		cin >> q;
		now = lower_bound(p + now, p + now + n, (now ? p[now-1] : 0) + q) - p;
		now = (now + 1) % n;
	}
	cout << now << '\n';
	return 0;
}
