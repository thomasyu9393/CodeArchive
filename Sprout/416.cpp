#include <iostream>
using namespace std;
#define int long long
const int mod = 1e9 + 7;

inline void add(int &a, int b){
    a = (a + b) % mod;
}
inline int ab(int x){
    return x < 0 ? -x : x;
}

int pre[2005]{}, now[2005]{};
signed main(){
    int n, a, b, k;
    cin >> n >> a >> b >> k;
    pre[a] = 1;
    for(int i=1 ; i<=k ; ++i){
        for(int j=1 ; j<=n ; ++j){
            int d = ab(j - b) - 1;
            now[max(j - d, 1ll)] += pre[j];
            now[min(j + d, n) + 1] -= pre[j];
            now[j] -= pre[j];
            now[j + 1] += pre[j];
        }
        for(int j=1 ; j<=n ; ++j){
            pre[j] = pre[j-1] + now[j];
            pre[j] = (pre[j] % mod + mod) % mod;
            now[j] = 0;
        }
    }
    int ans = 0;
    for(int i=1 ; i<=n ; ++i){
        add(ans, pre[i]);
    }
    cout << ans << '\n';
}
