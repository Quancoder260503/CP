#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef long long ll;
const int sz=1e5+5;
ll n,k,m,q,T,p,ans,start;
int par[sz];
int compsz[sz];
int spe[sz];
ll dp[sz];
bool a[sz];
vector<ll>point;
vector<array<ll,3>>edge;
vector<array<ll,2>>adj[sz];
void init(int n){
    for(int i=1;i<=n;i++){
        par[i]=i;
        compsz[i]=1;
    }
}
int find(int x){
    if(x==par[x]) return x;
    else return find(par[x]);   
}
void unite(int x,int y, ll w){
    x=find(x);y=find(y);
    if(x==y) return;
    if(compsz[x]<compsz[y]) swap(x,y);
    if(spe[x]+spe[y]==k){
        for(int i=1;i<=k;i++){
            cout<<w<<" ";
        } exit(0);
    }
    spe[x]+=spe[y];
    compsz[x]+=compsz[y];
    par[y]=x;
}
int main(){
      cin>>n>>m>>k;
      init(n);
      for(int i=1;i<=k;i++){
          int x;cin>>x;
          a[x]=1; spe[x]++;
      }  
     for(int i=1;i<=m;i++){
         ll u,v,w;cin>>u>>v>>w;
         edge.push_back({w,u,v});
     }
    sort(edge.begin(),edge.end());
    for(auto e:edge){
        unite(e[1],e[2],e[0]);
    }
}