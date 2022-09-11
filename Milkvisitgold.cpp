#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
ll n,k,m,q;
int timer=1;
int trs[sz],dep[sz];
int id[sz],top[sz],a[sz];
int par[sz];
set<ll>col[sz];
vector<ll>adj[sz];
ll dfs(int u,int p){
    trs[u]=1;
    for(auto v:adj[u]){
        if(v==p) continue;
        par[v]=u;
        dep[v]=dep[u]+1;
        trs[u]+=dfs(v,u);
    } return trs[u];
}
void dfs_hld(int u,int anc){
    id[u]=timer++;
    top[u]=anc;
    int hchi=0;
    int hsize=0;
    for(auto v:adj[u]){
        if(v==par[u]) continue;
        if(hsize<trs[v]){
            hsize=trs[v];
            hchi=v;
        }
    }
    if(hchi==0) return;
    dfs_hld(hchi,anc);
    for(auto v:adj[u]){
        if(v==par[u] or v==hchi) continue;
        dfs_hld(v,v);
    }
}
bool get(int l,int r,int val){
    auto it=col[val].lower_bound(l);
    if(it!=col[val].end() and (*it)<=r) return 1;
    else return 0;
}
bool path(int x,int y,int val){
    int ret=0;
    while(top[x]!=top[y]){
       if(dep[top[x]]<dep[top[y]])swap(x,y);
       ret|=get(id[top[x]],id[x],val);
       x=par[top[x]];
    }   
    if(dep[x]>dep[y]) swap(x,y);
    ret|=get(id[x],id[y],val);
    return ret;
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=0;i<n-1;i++){
        ll u,v;cin>>u>>v;
        adj[v].push_back(u);
        adj[u].push_back(v);
    } dfs(1,0);
      dfs_hld(1,1);
      for(int i=1;i<=n;i++) col[a[i]].insert(id[i]);
      for(int i=0;i<q;i++){
          int u,v,val;cin>>u>>v>>val;
          bool res=path(u,v,val);
          cout<<res;
      }
}