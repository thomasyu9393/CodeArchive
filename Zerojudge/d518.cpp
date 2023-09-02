#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int id = 0;

struct node {
	int ch[26]{};
	int cnt = 0;
};

struct Trie {
	vector<node> t;
	void init() {
		t.clear();
		t.emplace_back(node());
	}
	int insert(string s) {
		int ptr = 0;
		for (int i = 0; i < s.size(); ++i) {
			if (!t[ptr].ch[s[i] - 'a']) {
				t[ptr].ch[s[i] - 'a'] = (int)t.size();
				t.emplace_back(node());
			}
			ptr = t[ptr].ch[s[i] - 'a'];
			if (i == s.size() - 1) {
				if (t[ptr].cnt) return -t[ptr].cnt;
				return t[ptr].cnt = ++id;
			}
		}
		return 0;
	}
} trie;

int ab(int x) {
	return x < 0 ? -x : x;
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	while (cin >> n) {
		id = 0;
		trie.init();
		for (int i = 0; i < n; ++i) {
			string s;
			cin >> s;
			int res = trie.insert(s);
			cout << (res < 0 ? "Old! " : "New! ") << ab(res) << '\n';
		}
	}
	return 0;
}