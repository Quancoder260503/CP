#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int inf=1e6+1;
int n,q,m;
int ans[sz];
int par[sz];
int trs[sz];
set<int>adj[sz];
map<int,int>dis[sz];
int dfs(int u, int p) {
  trs[u] = 1;
  for(auto v : adj[u]) if(v != p) {
        trs[u] += dfs(v, u);
    }
  return trs[u];
}
int centroid(int u, int p, int n) {
    for(auto v : adj[u]) if(v != p) {
      if(trs[v] > n / 2) return centroid(v, u, n);
   }
  return u;
}
void dfs2(int u,int p,int anc,int d){
     dis[anc][u]=d;
     for(auto v:adj[u]){
         if(v==p) continue;
         dfs2(v,u,anc,d+1);
     }
}
void build(int u, int p) {
    int n = dfs(u, p);
    int c = centroid(u, p, n);
    if(p == -1) p = c;
    par[c] = p;
    dfs2(c,p,c,0);
    vector<int> tmp(adj[c].begin(), adj[c].end());
    for(auto v : tmp) {
       adj[c].erase(v); adj[v].erase(c);
       build(v, c);
    }
}
void modify(int u){
    ans[u]=0;
    for (int v=u;v!=0;v=par[v]) ans[v]=min(ans[v],dis[v][u]);
}
int query(int u){
    int res=inf;
    for(int v=u ;v!=0; v=par[v]) res=min(res,ans[v]+dis[v][u]);
    return res;
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) ans[i]=inf;
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    build(1,0);
    modify(1);
    for(int i=1;i<=q;i++){
         int t,u;cin>>t>>u;
         if(t==1) modify(u);
         else cout<<query(u)<<endl;
    }
}