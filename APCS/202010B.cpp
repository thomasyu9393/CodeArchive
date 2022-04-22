#include <bits/stdc++.h>
using namespace std;

int mp[52][52][2];
int main(){
	ios_base::sync_with_stdio(false), cin.tie(0);
	memset(mp, -1, sizeof(mp));
	int n, m, k, d;
	cin >> n >> m >> k >> d;
	for(int i=1 ; i<=n ; ++i)
		for(int j=1 ; j<=m ; ++j)
			cin >> mp[i][j][0];
	int now = 1, prv = 0;
	for(int _=0 ; _<d ; ++_){
		for(int i=1 ; i<=n ; ++i)
			for(int j=1 ; j<=m ; ++j){
				if(~mp[i][j][prv]){
					mp[i][j][now] = (~mp[i-1][j][prv] ? mp[i-1][j][prv] : 0) / k +
									(~mp[i][j-1][prv] ? mp[i][j-1][prv] : 0) / k +
									(~mp[i][j+1][prv] ? mp[i][j+1][prv] : 0) / k +
									(~mp[i+1][j][prv] ? mp[i+1][j][prv] : 0) / k +
									mp[i][j][prv] - (mp[i][j][prv] / k) *
									((~mp[i-1][j][prv] ? 1 : 0) +
									(~mp[i][j-1][prv] ? 1 : 0) +
									(~mp[i][j+1][prv] ? 1 : 0) +
									(~mp[i+1][j][prv] ? 1 : 0));
				}
			}
		now ^= 1, prv ^= 1;
	}
	int mn, mx;
	for(int i=1 ; i<=n ; ++i)
		for(int j=1 ; j<=m ; ++j){
			if(~mp[i][j][prv]){
				mn = mp[i][j][prv], mx = mp[i][j][prv];
				break;
			}
		}
	for(int i=1 ; i<=n ; ++i)
		for(int j=1 ; j<=m ; ++j){
			if(~mp[i][j][prv]){
				mn = min(mn, mp[i][j][prv]);
				mx = max(mx, mp[i][j][prv]);
			}
		}
	cout << mn << '\n' << mx << '\n';
}
