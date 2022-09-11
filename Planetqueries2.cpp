#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
ll n,k,m,q;
int timer=1;
int st[1<<19],trs[sz],dep[sz];
int id[sz],top[sz],a[sz];
int par[sz];
vector<ll>adj[sz];
void update(int idx,ll val){
    st[idx+=n]=val;
    for(idx/=2;idx;idx/=2){
        st[idx]=max(st[idx*2],st[idx*2+1]);
    }
}
int query(int lo ,int high){
    int ra=0;int  rb=0;
    for(lo+=n,high+=n+1;lo<high;lo/=2,high/=2){
        if(lo&1) ra=max(ra,st[lo++]);
        if(high&1) rb=max(rb,st[--high]);
    } return max(ra,rb); 
}
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
    update(id[u],a[u]);
    int hchi,hsize;
    for(auto v:adj[u]){
        if(v==par[u]) continue;
        if(hsize<trs[v]){hsize=trs[v];hchi=v;}
    }
    if(hchi==0) return;
    dfs_hld(hchi,anc);
    for(auto v:adj[u]){
        if(v==par[u] or v==hchi) continue;
        dfs_hld(v,v);
    }
}
ll path(int x,int y){
    int ret=0;
    while(top[x]!=top[y]){
       if(dep[top[x]]<dep[top[y]])swap(x,y);
       ret=max(ret,query(id[top[x]],id[x]));
       x=par[id[x]];
    }   
    if(dep[x]>dep[y]) swap(x,y);
    ret=max(ret,query(id[x],id[y]));
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
       for(int i=0;i<q;i++){
          ll t,u,v; cin>>t;
          if(t==1){
              cin>>u>>v;
              a[u]=v;
              update(u,v);
          }
          if(t==2){
              cin>>u>>v;
              int x=path(v,u);
              cout<<x<<" ";
          }
      }
} 