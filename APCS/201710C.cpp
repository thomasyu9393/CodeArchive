#include <iostream>
using namespace std;

int parent[100100];
int childnum[100100]{};
int height[100100]{};

int FindParent(int n) {
	while(n != parent[n]) n = parent[n];
	return n;
}

void visit(int o, int n) {
	while(o != parent[o] && n > height[parent[o]]) {
		height[parent[o]] = n;
		o = parent[o];
		n++;
	}
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, c;
	cin >> n;
	for(int i=1 ; i<=n ; ++i) {
		parent[i] = i;
	}
	for(int i=1 ; i<=n ; ++i) {
		cin >> childnum[i];
		for(int j=0 ; j<childnum[i] ; ++j) {
			cin >> c;
			parent[c] = i;
		}
	}
	cout << FindParent(1) << '\n';
	for(int i=1 ; i<=n ; ++i) {
		if(!childnum[i]) visit(i, 1);
	}
	long long ans = 0;
	for(int i=1 ; i<=n ; ++i) {
		ans += height[i];
	}
	cout << ans << '\n';
	return 0;
}
