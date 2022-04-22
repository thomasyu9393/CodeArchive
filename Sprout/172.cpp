#include <iostream>
using namespace std;
#define ll long long
const ll mod = 1000007;

ll C[105][105]{};
void init(){
    for(int i=0 ; i<105 ; ++i){
        C[i][0] = 1;
        C[i][i] = 1;
    }
    for(int i=2 ; i<105 ; ++i){
        for(int j=1 ; j<i ; ++j){
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
        }
    }
}

void solve(){
    int n, m, a[105];
    cin >> n >> m;
    int sum = 0;
    for(int i=1 ; i<=n ; ++i){
        cin >> a[i];
        sum += a[i];
    }
    if(sum < m){
        cout << "0\n";
        return;
    }
    if(sum == m){
        ll ans = 1;
        for(int i=1 ; i<=n ; ++i){
            ans = (ans * C[m][a[i]]) % mod;
            m -= a[i];
        }
        cout << ans << '\n';
        return;
    }
    ll dp[105][105]{};
    dp[0][0] = 1;
    for(int i=1 ; i<=n ; ++i){
        for(int j=a[i] ; j<=m ; ++j){
            for(int k=0 ; k<=j ; ++k){
                if(j - k > a[i]) continue;
                dp[i][j] = (dp[i][j] + dp[i-1][k] * C[m-k][j-k] % mod * C[k][a[i]-j+k]) % mod;
            }
        }
    }
    cout << dp[n][m] << '\n';
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    init();
    int t;
    cin >> t;
    while(t--) solve();
}
