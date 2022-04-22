#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 500005;

struct seg{
	ll a, b, ind;
};
deque<seg> dq;

ll S[maxn], dp[maxn];
ll getv(int j, ll i){
	return dq[j].a * i + dq[j].b;
}
bool fail(seg i, seg j, seg k, ll t){
	return min(i.ind + t, (j.b-i.b) / (i.a-j.a)) > (k.b-j.b) / (j.a-k.a);
}
int main(){
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	for(int i=n ; i ; --i){
		cin >> S[i];
	}
	for(int i=2 ; i<=n ; ++i){
		S[i] += S[i-1];
	}
	dq.emplace_back(seg{0, 0, 0});
	for(ll i=1 ; i<=n ; ++i){
		while(dq.front().ind < i - k) dq.pop_front();
		while(dq.size() > 1 && getv(0, i) <= getv(1, i)) dq.pop_front();
		dp[i] = getv(0, i) - i*i;
		ll na = i * 2, nb = dp[i] + S[i] - i*i;
		while(dq.size() > 1 && fail(dq[dq.size()-2], dq.back(), seg{na, nb, i}, k)) dq.pop_back();
		dq.emplace_back(seg{na, nb, i});
	}
	cout << dp[n] << '\n';
}
