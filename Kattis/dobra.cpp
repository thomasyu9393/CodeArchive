#include <iostream>
using namespace std;
#define ll long long

int vowel(int c) {
	if (c == 'A' - 'A') return 1;
	if (c == 'E' - 'A') return 1;
	if (c == 'I' - 'A') return 1;
	if (c == 'O' - 'A') return 1;
	if (c == 'U' - 'A') return 1;
	return 0;
}
bool check(int a, int b, int c) {
	int cnt = vowel(a) + vowel(b) + vowel(c);
	return (cnt > 0 && cnt < 3);
}
bool isL(int c) {
	return (c + 'A' == 'L');
}

string s;
bool qq(int p, int c) {
	if (s[p] == '_') return 1;
	return (s[p] - 'A' == c);
}

ll dp[105][26][26][2]{};

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	cin >> s;
	int n = s.size();
	if (n == 1) {
		cout << (s[0] == '_' || s[0] == 'L' ? 1 : 0) << '\n';
	} else if (n == 2) {
		if (s[0] == '_' && s[1] == '_') {
			cout << 52 << '\n';
		} else if (s[0] == '_') {
			cout << (s[1] == 'L' ? 26 : 1) << '\n';
		} else if (s[1] == '_') {
			cout << (s[0] == 'L' ? 26 : 1) << '\n';
		} else {
			cout << (s[0] == 'L' || s[1] == 'L' ? 1 : 0) << '\n';
		}
	} else {
		for (int i=0; i<26; ++i) {
			for (int j=0; j<26; ++j) {
				for (int k=0; k<26; ++k) {
					if (!qq(0, i) || !qq(1, j) || !qq(2, k)) continue;
					if (!check(i, j, k)) continue;
					if (isL(i) || isL(j) || isL(k)) {
						++dp[2][j][k][1];
					} else {
						++dp[2][j][k][0];
					}
				}
			}
		}
		for (int p=3; p<n; ++p) {
			for (int j=0; j<26; ++j) {
				for (int k=0; k<26; ++k) {
					for (int i=0; i<26; ++i) {
						if (!check(j, k, i)) continue;
						if (!qq(p-2, j) || !qq(p-1, k) || !qq(p, i)) continue;
						if (isL(i)) {
							dp[p][k][i][1] += dp[p-1][j][k][1];
							dp[p][k][i][1] += dp[p-1][j][k][0];
						} else {
							dp[p][k][i][1] += dp[p-1][j][k][1];
							dp[p][k][i][0] += dp[p-1][j][k][0];
						}
					}
				}
			}
		}
		ll ans = 0;
		for (int j=0; j<26; ++j) {
			for (int k=0; k<26; ++k) {
				if (!qq(n-2, j) || !qq(n-1, k)) continue;
				ans += dp[n-1][j][k][1];
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
