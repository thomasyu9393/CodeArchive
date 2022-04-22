#include <iostream>
#include <iomanip>
using namespace std;

int n;
double a[15], b[15], c[15];
inline double f(double t){
    double res = 0;
    for(int i=0 ; i<n ; ++i){
        double tmp = a[i]*(t-b[i])*(t-b[i]) + c[i];
        if(tmp > res) res = tmp;
    }
    return res;
}
int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int tc;
    cin >> tc;
    while(tc--){
        cin >> n;
        double l = 0, r = 300.0;
        for(int i=0 ; i<n ; ++i){
            cin >> a[i] >> b[i] >> c[i];
        }
        for(int i=0 ; i<100 ; ++i){
            double ml = (l + l + r) / 3.0, mr = (l + r + r) / 3.0;
            double w = f(l), x = f(ml), y = f(mr), z = f(r);
            if(x < y && y < z)
                r = mr;
            else if(w > x && x > y)
                l = ml;
            else
                l = ml, r = mr;
        }
        cout << fixed << setprecision(5) << f(l) << '\n';
    }
}
