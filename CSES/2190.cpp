#include <iostream>
using namespace std;
#define ll long long

struct Point {
	ll x, y;
	Point(ll x = 0, ll y = 0): x(x), y(y){}
	Point operator+(const Point p) const {return Point(x + p.x, y + p.y);}
	Point operator-(const Point p) const {return Point(x - p.x, y - p.y);}
	ll operator*(const Point p) const {return x * p.x + y * p.y;}
	ll operator^(const Point p) const {return x * p.y - y * p.x;}
};

bool inseg(Point a, Point b, Point c) {
	return (((a - c) ^ (b - c)) == 0 && ((a - c) * (b - c)) <= 0);
}
int ori(Point a, Point b, Point c) {
	ll w = (a - c) ^ (b - c);
	return (w ? (w > 0 ? 1 : -1) : 0);
}
bool gg(Point a, Point b, Point c, Point d) {
	if (inseg(a, b, c) || inseg(a, b, d) || inseg(c, d, a) || inseg(c, d, b))
		return 1;
	else
		return (ori(a, b, c) * ori(a, b, d) < 0 && ori(c, d, a) * ori(c, d, b) < 0);
}

void solve() {
	Point p[4];
	for (int i=0; i<4; ++i) {
		ll x, y;
		cin >> x >> y;
		p[i] = Point(x, y);
	}
	cout << (gg(p[0], p[1], p[2], p[3]) ? "YES\n" : "NO\n");
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
