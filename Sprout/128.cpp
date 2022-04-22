#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using vvi = vector<vector<int>>;

vvi OAO(int n){
    if(n == 2){
        vvi res = {{1, 2}, {3, 1}};
        return res;
    }
    if(n == 4){
        vvi res = {{1, 2, 4, 5},
                   {3, 1, 6, 7},
                   {7, 5, 1, 2},
                   {6, 4, 3, 1}};
        return res;
    }
    vvi res(n, vector<int>(n, 0));
    int m = n / 2;
    vvi omg = OAO(m);
    for(int i=0 ; i<m ; ++i){
        for(int j=0 ; j<m ; ++j){
            res[i][j] = omg[i][j];
            res[i + m][j + m] = omg[i][j];
        }
    }
    vector<int> v;
    for(int i=n ; i<(n<<1) ; ++i){
        v.emplace_back(i);
    }
    int s = 0;
    for(int i=0 ; i<m ; ++i){
        for(int j=0 ; j<m ; ++j){
            res[i][j + m] = v[(s + j) % n];
        }
        for(int j=0 ; j<m ; ++j){
            res[j + m][i] = v[(s + m + j) % n];
        }
        s = (s - 1 + n) % n;
    }
    return res;
}

void solve(int n){
    vvi res = OAO(n);
    for(auto i: res){
        for(int j: i){
            Report(j);
        }
    }
}
