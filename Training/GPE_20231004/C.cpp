#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 20005;

struct BigInt {
	int n = 0;
	int ch[maxn]{};
	BigInt(){}
	BigInt(string s) {
		n = s.size();
		for (int i = 0; i < n; ++i) {
			ch[n - i - 1] = s[i] - '0';
		}
	}
	void pull() {
		for (int i = 0; i < maxn; ++i) {
			if (ch[i]) n = i + 1;
		}
	}
	void print() {
		cout << n << ": ";
		for (int i = n - 1; i >= 0; --i) {
			cout << ch[i];
		}
		if (n == 0) cout << 0;
		cout << '\n';
	}
	bool operator<(BigInt x) {
		if (n < x.n) return 1;
		if (n > x.n) return 0;
		for (int i = n - 1; i >= 0; --i) {
			if (ch[i] < x.ch[i]) return 1;
			if (ch[i] > x.ch[i]) return 0;
		}
		return 0;
	}
};

BigInt add(BigInt a, BigInt b) {
	BigInt res;
	int n = max(a.n, b.n);
	for (int i = 0; i < n; ++i) {
		res.ch[i] += a.ch[i] + b.ch[i];
		res.ch[i + 1] += res.ch[i] / 10;
		res.ch[i] %= 10;
	}
	res.pull();
	return res;
}

BigInt mul(BigInt a, BigInt b) {
	BigInt res;
	for (int i = 0; i < a.n; ++i) {
		for (int j = 0; j < b.n; ++j) {
			res.ch[i + j] += a.ch[i] * b.ch[j];
		}
	}
	for (int i = 0; i + 1 < maxn; ++i) {
		res.ch[i + 1] += res.ch[i] / 10;
		res.ch[i] %= 10;
	}
	res.pull();
	return res;
}

BigInt di2(BigInt a) { //divide by 2
	BigInt res;
	for (int i = a.n - 1; i > 0;) {
		BigInt buff;
		buff.n = i;
		buff.ch[i - 1] = 1;
		BigInt tmp = add(res, buff);
		if (a < add(tmp, tmp)) {
			--i;
		} else {
			res = tmp;
		}
	}
	return res;
}

BigInt sqrt(BigInt a) { //rounded up
	BigInt L("1"), R = a;
	while (L < R) {
		BigInt mid = di2(add(L, R));
		if (mul(mid, mid) < a) {
			BigInt one("1");
			L = add(mid, one);
		} else {
			R = mid;
		}
	}
	return L;
}

signed main() {
	string s;
	cin >> s;
	BigInt a(s);
	a = sqrt(a);
	a.print();
	return 0;
}