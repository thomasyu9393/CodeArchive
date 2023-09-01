#include <iostream>
using namespace std;
const int maxn = 1000005;
 
int F[maxn]{};
int match(string& s, string& t) {
	int p = F[0] = -1;
	for (int i = 1; i < t.size(); ++i) {
		while (p != -1 && t[p + 1] != t[i]) p = F[p];
		if (t[p + 1] == t[i]) ++p;
		F[i] = p;
	}
	p = -1;
	int cnt = 0;
	for (int i = 0; i < s.size(); ++i) {
		while (p != -1 && t[p + 1] != s[i]) p = F[p];
		if (t[p + 1] == s[i]) ++p;
		if (p == t.size() - 1) ++cnt, p = F[p];
	}
	return cnt;
}
 
signed main() {
	string s, t;
	cin >> s >> t;
	int ans = match(s, t);
	cout << ans << '\n';
	return 0;
}