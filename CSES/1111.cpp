#include <iostream>
using namespace std;
const int maxn = 1000005;
 
int z[maxn * 2]{};
signed main() {
	string s;
	cin >> s;
	string t = "#";
	for (char c: s) t += c, t += '#';
	int l = 0, r = 0, ans = 0;
	for (int i = 1; i < t.size(); ++i) {
		z[i] = (r > i ? min(z[2 * l - i], r - i) : 1);
		while (i - z[i] >= 0 && i + z[i] < t.size()) {
			if (t[i - z[i]] == t[i + z[i]])
				++z[i];
			else
				break;
		}
		if (i + z[i] > r) r = i + z[i], l = i;
	}
	for (int i = 1; i < t.size(); ++i) {
		ans = max(ans, z[i] - 1);
	}
	string res;
	for (int i = 1; i < t.size(); ++i) if (ans == z[i] - 1) {
		for (int j = i - ans + 1; j < i + ans; ++j) if (t[j] != '#') {
			res += t[j];
		}
		break;
	}
	cout << res << '\n';
	return 0;
}
 
//0123456
//aybabtu
//012345678901234
//#a#y#b#a#b#t#u#