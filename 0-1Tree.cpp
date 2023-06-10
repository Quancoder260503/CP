#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
ll timer=1;
int n,q,m;
ll up[19][sz];
ll dp[sz];
vector<ll>adj[sz];
vector<array<int,2>>edge1;
vector<array<int,2>>edge0;
set<int>s;
int par[sz][2],compsz[sz][2];
const int mod=1e9+7;
void init(int n){
    for(int i=1;i<=n;i++){
        par[i][0]=par[i][1]=i;
        compsz[i][0]=compsz[i][1]=1;
    }
}
int find(int x,int c){
    if(x==par[x][c]) return x;
    else return find(par[x][c],c);
}
void unite(int x,int y,int c){
    x=find(x,c);y=find(y,c);
    if(x==y) return;
    if(compsz[x][c]<compsz[y][c]) swap(x,y);
    compsz[x][c]+=compsz[y][c];
    par[y][c]=x;
}
int main(){   
    cin>>n;
    init(n);
    for(int i=1;i<n;i++){
        int u,v,w;cin>>u>>v>>w;
        if(w) edge1.push_back({u,v}),s.insert(u),s.insert(v);
        else edge0.push_back({u,v});
    }
    for(auto e:edge1) unite(e[0],e[1],1);
    for(auto e:edge0) unite(e[0],e[1],0);
    ll res=0;
    for(int i=1;i<=n;i++){
        int x=find(i,0);int y=find(i,1);
        res+=compsz[x][0]+compsz[y][1]-2;
        if(s.count(i)) res+=(ll) (compsz[x][0]-1)*(compsz[y][1]-1);
    }
    cout<<res<<endl;
}   
