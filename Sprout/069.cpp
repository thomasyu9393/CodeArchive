#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long

ll a[10005], b[10005], A[10005];
ll c[10005];
int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        for(int i=0 ; i<n ; ++i){
            cin >> a[i] >> b[i];
        }
        for(int i=0 ; i<n ; ++i){
            cin >> c[i];
        }
        sort(c, c + n);
        ll l = 0, r = 1e9;
        bool ok;
        while(l < r){ // [l, r]
            if(l + 1 == r){
                for(int i=0 ; i<n ; ++i){
                    A[i] = a[i] + l * b[i];
                }
                sort(A, A + n);
                int i = 0;
                for(int j=0 ; j<n ; ++j){
                    if(c[i] < A[j]){
                        i++;
                    }
                }
                if(i < k) l = r;
                break;
            }
            int m = (l + r) >> 1;
            for(int i=0 ; i<n ; ++i){
                A[i] = a[i] + m * b[i];
            }
            sort(A, A + n);
            int i = 0;
            for(int j=0 ; j<n ; ++j){
                if(c[i] < A[j]){
                    i++;
                }
            }
            if(i >= k) r = m;
            else l = m + 1;
        }
        ok = 1;
        for(int i=0 ; i<n ; ++i){
            A[i] = a[i] + l * b[i];
        }
        sort(A, A + n);
        int i = 0;
        for(int j=0 ; j<n ; ++j){
            if(c[i] < A[j]){
                i++;
            }
        }
        cout << (i >= k ? l : -1) << '\n';
    }
}
