#include <iostream>
#include <algorithm>
using namespace std;

struct item {
	long long w, f;
} stack[100005];

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; ++i) cin >> stack[i].w;
	for(int i=0; i<n; ++i) cin >> stack[i].f;
	sort(stack, stack + n, [](item a, item b) {
		return a.w * b.f < b.w * a.f;
	});
	long long ans = 0;
	for(int i=1 ; i<n ; ++i) {
		ans += (stack[i-1].w * stack[i].f);
		stack[i].w += stack[i-1].w;
	}
	cout << ans << '\n';
	return 0;
}
