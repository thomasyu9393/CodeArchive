#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
const int maxn = 1000005;
const ll P = 41;
const ll mod = 1000696969;

ll modp[maxn]{};
ll hashv[2][maxn]{};

ll calc(string &s, int t) {
	ll res = 0;
	for (int i = 0; i < s.size(); ++i) {
		res = (res * P + s[i]) % mod;
		hashv[t][i] = res;
	}
	return res;
}

ll get_v(int l, int r, int t) {
	if (l == 0) return hashv[t][r];
	return ((hashv[t][r] - hashv[t][l-1] * modp[r-l+1]) % mod + mod) % mod;
}

bool sub(string &s, string &t) {
	calc(s, 0);
	ll val_t = calc(t, 1);
	if (s.size() < t.size()) return 0;
	for (int i = 0; i + t.size() - 1 < s.size(); ++i) {
		if (get_v(i, i + t.size() - 1, 0) == val_t) return 1;
	}
	return 0;
}

string new_s(string &s, string &t) {
	if (sub(s, t)) return s;
	string res = s;
	for (int l = min(s.size(), t.size()); l > 0; --l) {
		if (get_v(s.size() - l, s.size() - 1, 0) == get_v(0, l - 1, 1)) {
			for (int j = l; j < t.size(); ++j) {
				res += t[j];
			}
			return res;
		}
	}
	res += t;
	return res;
}

bool check(string &s, string &t) {
	if (s.size() == 0) return 1;
	if (t.size() < s.size()) return 1;
	if (t.size() > s.size()) return 0;
	for (int i = 0; i < s.size(); ++i) {
		if (t[i] < s[i]) return 1;
		if (t[i] > s[i]) return 0;
	}
	return 0;
}

string input[18];
string dp[18][(1<<18)|(1<<10)];

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	modp[0] = 1;
	for (int i = 1; i < maxn; ++i) {
		modp[i] = (modp[i-1] * P) % mod;
	}
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> input[i];
		dp[1][1<<i] = input[i];
	}
	for (int m = 2; m <= n; ++m) {
		for (int s = 1; s < (1<<n); ++s) {
			if (__builtin_popcount(s) != m) continue;
			for (int i = 0; i < n; ++i) if (s & (1<<i)) {
				string a = dp[m - 1][s^(1<<i)];
				string b = input[i];
				string res = new_s(a, b);
				if (check(dp[m][s], res)) {
					dp[m][s] = res;
				}
			}
		}
	}
	cout << dp[n][(1<<n)-1] << '\n';
	return 0;
}

/*
4
i
love
saito
asuka

11
genshin
impact
start
hee
hee
hee
i
am
a
klee
player
*/