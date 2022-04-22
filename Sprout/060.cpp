#include <iostream>
using namespace std;
#define ll long long
inline ll cdiv(ll a, ll b){return (a + b - 1) / b;}
inline void chmax(ll &a, ll b){a = (a < b ? b : a);}
inline void chmin(ll &a, ll b){a = (a > b ? b : a);}

int main(){
    ll a, b, c, d, m, s, t;
    cin >> a >> b >> c >> d >> m >> s >> t;
    if(a >= b){
        ll time = cdiv(s, a);
        if(time <= t){
            cout << "Yes\n" << time << '\n';
        }
        else{
            cout << "No\n" << a * t << '\n';
        }
    }
    else{
        ll ok = 1e9, notok = 0;
        for(ll i=0 ; i+(i*c>m?cdiv(i*c-m,d):0)<=t ; ++i){
            ll curdis = i * b;
            ll curtime = i + (i*c>m ? cdiv(i*c-m, d) : 0);
            if(curdis >= s){
                chmin(ok, curtime);
            }
            else{
                ll need = cdiv(s - curdis, a);
                if(curtime + need <= t){
                    chmin(ok, curtime + need);
                }
                else{
                    chmax(notok, curdis + (t - curtime) * a);
                }
            }
        }
        if(ok < 1e9){
            cout << "Yes\n" << ok << '\n';
        }
        else{
            cout << "No\n" << notok << '\n';
        }
    }
}
