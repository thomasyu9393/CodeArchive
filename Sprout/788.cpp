#include <iostream>
using namespace std;
#define ll long long
const int maxn = 500005;

int ar[maxn];
int sufmx[maxn], sufmn[maxn], prefmx[maxn], prefmn[maxn];
int ad[1500100]{}, sb[1500100]{};
ll ans;
void OAO(int l, int r){ //[l, r)
    if(l >= r) return;
    if(l + 1 == r) return ans++, void();
    int mid = (l + r) / 2;
    OAO(l, mid), OAO(mid, r);
    for(int i=mid-1 ; i>=l ; --i){
        sufmx[i] = max((i + 1 == mid ? 0 : sufmx[i+1]), ar[i]);
        sufmn[i] = min((i + 1 == mid ? maxn : sufmn[i+1]), ar[i]);
    }
    for(int i=mid ; i<r ; ++i){
        prefmx[i] = max((i == mid ? 0 : prefmx[i-1]), ar[i]);
        prefmn[i] = min((i == mid ? maxn : prefmn[i-1]), ar[i]);
    }
    for(int i=l ; i<mid ; ++i){
        int rig = i + sufmx[i] - sufmn[i]; //R = L + mxL - mnL
        if(rig < mid || rig >= r) continue;
        if(prefmx[rig] < sufmx[i] && prefmn[rig] > sufmn[i]) ans++;
    }
    for(int i=mid ; i<r ; ++i){
        int lef = i - prefmx[i] + prefmn[i]; //L = R - mxR + mnR
        if(lef < l || lef >= mid) continue;
        if(sufmx[lef] < prefmx[i] && sufmn[lef] > prefmn[i]) ans++;
    }
    int okl = mid - 1, okr = mid - 1; //(okl, okr]
    for(int i=mid ; i<r ; ++i){ //L + mxL = R + mnR
        while(okl >= l && sufmn[okl] > prefmn[i]) ad[okl + sufmx[okl] + maxn]++, okl--;
        while(okr > okl && sufmx[okr] < prefmx[i]) ad[okr + sufmx[okr] + maxn]--, okr--;
        ans += ad[i + prefmn[i] + maxn];
    }
    while(okr > okl) ad[okr + sufmx[okr] + maxn]--, okr--;
    okl = mid - 1, okr = mid - 1; //(okl, okr]
    for(int i=mid ; i<r ; ++i){ //L - mnL = R - mxR
        while(okl >= l && sufmx[okl] < prefmx[i]) sb[okl - sufmn[okl] + maxn]++, okl--;
        while(okr > okl && sufmn[okr] > prefmn[i]) sb[okr - sufmn[okr] + maxn]--, okr--;
        ans += sb[i - prefmx[i] + maxn];
    }
    while(okr > okl) sb[okr - sufmn[okr] + maxn]--, okr--;
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        for(int i=0 ; i<n ; ++i){
            cin >> ar[i];
        }
        ans = 0;
        OAO(0, n);
        cout << ans << '\n';
    }
}
