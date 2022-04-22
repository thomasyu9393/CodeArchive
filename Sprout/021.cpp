#include <bits/stdc++.h>
using namespace std;

struct Node{
    int id;
    Node *prv, *nxt;
    Node(int id): id(id), prv(NULL), nxt(NULL){}
};
vector<Node*> v;
vector<int> a;
int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, m;
    cin >> n >> m;
    v.resize(n+1);
    v[0] = new Node(0);
    for(int i=1 ; i<=n ; ++i){
        v[i] = new Node(i);
        v[i]->prv = v[i-1];
        v[i-1]->nxt = v[i];
    }
    for(int i=0 ; i<m ; ++i){
        int t, x;
        cin >> t >> x;
        if(t){
            if(v[x]->prv == v[0]) continue;
            v[x]->prv->prv->nxt = v[x];
            if(v[x]->nxt) v[x]->nxt->prv = v[x]->prv;
            Node *q = v[x]->prv->prv;
            v[x]->prv->prv = v[x];
            v[x]->prv->nxt = v[x]->nxt;
            Node *p = v[x]->prv;
            v[x]->prv = q;
            v[x]->nxt = p;
        }
        else{
            if(v[x]->prv) v[x]->prv->nxt = v[x]->nxt;
            if(v[x]->nxt) v[x]->nxt->prv = v[x]->prv;
            delete v[x];
        }
    }
    Node *p = v[0]->nxt;
    while(p){
        a.emplace_back(p->id);
        p = p->nxt;
    }
    if(a.size()) cout << a[0];
    for(int i=1 ; i<a.size() ; ++i) cout << " " << a[i];
    cout << '\n';
}
