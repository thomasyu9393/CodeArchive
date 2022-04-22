#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define REP(i, n) for(int i=0 ; i<n ; ++i)

const int maxn = 1505;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rd(ll l, ll r){
    return uniform_int_distribution<ll>(l, r)(rng);
}

ll A[maxn][maxn], B[maxn][maxn], C[maxn][maxn];
ll R[maxn];
ll NA[maxn]{}, NB[maxn]{}, NC[maxn]{};
int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    REP(i, n) REP(j, m) cin >> A[i][j];
    REP(i, m) REP(j, k) cin >> B[i][j];
    REP(i, n) REP(j, k) cin >> C[i][j];

    REP(j, k){
        R[j] = rd(1, 1e9);
        REP(i, m){ //B * R -> NB (m*k * k*1 -> m*1)
            NB[i] += B[i][j] * R[j];
        }
        REP(i, n){ //C * R -> NC (n*k * k*1 -> n*1)
            NC[i] += C[i][j] * R[j];
        }
    }
    REP(j, m){ //A * NB -> NA (n*m * m*1 -> n*1)
        REP(i, n){
            NA[i] += A[i][j] * NB[j];
        }
    }

    bool ok = 1;
    REP(i, n){
        ok &= NA[i] == NC[i];
    }
    cout << (ok ? "Yes\n" : "No\n");

    return 0;
}
