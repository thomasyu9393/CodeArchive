#include <iostream>
#include <set>
using namespace std;
const int inf = 1000000001;

inline int ab(int x){
    return x < 0 ? -x : x;
}
set<int> st;
int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int t, x;
    cin >> t;
    st.insert(-inf);
    st.insert(inf);
    while(t--){
        string s;
        cin >> s;
        if(s[0] == 'i'){
            cin >> x;
            st.insert(x);
        }
        else if(s[0] == 'd'){
            cin >> x;
            st.erase(x);
        }
        else{
            cin >> x;
            int ff = *prev(st.lower_bound(x));
            int ss = *st.lower_bound(x);
            if(ff == -inf){
                cout << ss << '\n';
            }
            else if(ss == inf){
                cout << ff << '\n';
            }
            else if(ab(ff - x) == ab(ss - x)){
                cout << ff << ' ' << ss << '\n';
            }
            else if(ab(ff - x) < ab(ss - x)){
                cout << ff << '\n';
            }
            else{
                cout << ss << '\n';
            }
        }
    }
}
