int n, cnt[1505];
void initialize(int _n){
    n = _n;
    for(int i=0 ; i<n ; ++i){
        cnt[i] = 0;
    }
}
int hasEdge(int a, int b){
    if(a > b){
        int c = a;
        a = b;
        b = c;
    }
    cnt[a]++;
    if(cnt[a] == n - a - 1) return 1;
    else return 0;
}
