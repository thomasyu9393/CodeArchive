#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
const int maxn = 100005;

struct Point {
	ll x, y;
	int i;
	Point(){}
	Point(ll x, ll y, int i): x(x), y(y), i(i){}
	Point operator+(const Point p) const {return Point(x + p.x, y + p.y, -1);}
	Point operator-(const Point p) const {return Point(x - p.x, y - p.y, -1);}
	ll operator*(const Point p) const {return x * p.x + y * p.y;}
	ll operator^(const Point p) const {return x * p.y - y * p.x;}
};

Point p[maxn];
int lc[maxn], uc[maxn];
int lcp = 0, ucp = 0;

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	for (int i=0; i<n; ++i) {
		ll x, y;
		cin >> x >> y;
		p[i] = {x, y, i + 1};
	}
	if (n == 1) {
		cout << "1\n1\n";
		return 0;
	}
	sort(p, p + n, [&](Point a, Point b) {
		return a.x < b.x;
	});
	for (int i=0; i<n; ++i) {
		while (ucp > 1 && ((p[i] - p[uc[ucp-2]]) ^ (p[uc[ucp-1]] - p[uc[ucp-2]])) >= 0) ucp--;
		uc[ucp++] = i;
		while (lcp > 1 && ((p[i] - p[lc[lcp-2]]) ^ (p[lc[lcp-1]] - p[lc[lcp-2]])) <= 0) lcp--;
		lc[lcp++] = i;
	}
	int con[maxn], ind = 0;
	for (int i=0; i<ucp-1; ++i) {
		con[ind++] = p[uc[i]].i;
	}
	for (int i=lcp-1; i>0; --i) {
		con[ind++] = p[lc[i]].i;
	}
	sort(con, con + ind);
	cout << ind << '\n';
	for (int i=0; i<ind; ++i) {
		cout << con[i] << '\n';
	}
	return 0;
}
