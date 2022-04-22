#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define ll long long

ll n, x[25], y[25];
double geta(int i, int j){
    return 1.0 * (y[i]*x[j] - y[j]*x[i]) / (x[i]*x[i]*x[j] - x[j]*x[j]*x[i]);
}
double getb(int i, int j){
    return 1.0 * (x[i]*x[i]*y[j] - x[j]*x[j]*y[i]) / (x[i]*x[i]*x[j] - x[j]*x[j]*x[i]);
}

int dp[1<<24];
int qq(int s){
    if(dp[s] < 30) return dp[s];
    int m = __builtin_popcount(s);
    if(m == 2){
        int i = -1, j = -1;
        for(int k=0 ; k<n ; ++k){
            if(s & (1<<k)){
                if(~i) j = k;
                else i = k;
            }
        }
        if(x[i] == x[j] || x[i] * y[j] == x[j] * y[i])
            return dp[s] = 2;
        double a = geta(i, j);
        return dp[s] = (a < 0 ? 1 : 2);
    }
    for(int i=0 ; i<n ; ++i){
        if(s & (1<<i)){
            dp[s] = qq(s^(1<<i)) + 1;
            for(int j=i+1 ; j<n ; ++j){
                if(s & (1<<j)){
                    if(x[i] == x[j] || x[i] * y[j] == x[j] * y[i]) continue;
                    double a = geta(i, j);
                    if(a < 0){
                        int ns = s ^ (1<<i) ^ (1<<j);
                        double b = getb(i, j);
                        for(int k=0 ; k<n ; ++k){
                            if(ns & (1<<k)){
                                if(abs(a*x[k]*x[k] + b*x[k] - y[k]) < 1e-8)
                                    ns ^= (1<<k);
                            }
                        }
                        dp[s] = min(dp[s], qq(ns) + 1);
                    }
                }
            }
            return dp[s];
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        cin >> n;
        for(int i=0 ; i<n ; ++i){
            cin >> x[i] >> y[i];
        }
        fill(dp, dp + (1<<n), 30);
        dp[0] = 0;
        for(int i=0 ; i<n ; ++i){
            dp[1<<i] = 1;
        }
        cout << qq((1<<n)-1) << '\n';
    }
}
