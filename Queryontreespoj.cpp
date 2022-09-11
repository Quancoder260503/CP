#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
ll n,k,m,q;
int timer=1;
int trs[sz],dp[sz];
ll tour[sz];
int id[sz],top[sz],a[sz];
int par[sz];
vector<ll>adj[sz];
ll tree[sz<<2];
ll dfs(int u,int p){
    trs[u]=1;
    for(auto v:adj[u]){
        if(v==p) continue;
        par[v]=u;
        dp[v]=dp[u]+1;
        trs[u]+=dfs(v,u);
    } return trs[u];
}
void dfs_hld(int u,int anc){
    tour[timer]=u;
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
void upd(int pos,int l=1 ,int r=n,int p=1){
    if(l>r) return;
    if(l==r) {
        tree[p]^=1;
        return;
    }
    int mid=(l+r)>>1;
    if(pos<=mid) upd(pos,l,mid,2*p);
    else upd(pos,mid+1,r,2*p+1);
    tree[p]=max(tree[p*2],tree[2*p+1]);
}
ll query(int L,int R,int l=1,int r=n,int node=1){
    if(L>r or R<l) return 0;
    if(l==r){
        if(tree[node]==1) return l;
    }
    int mid=(l+r)>>1;
    int ans=0;
    if(tree[node*2]==1) ans=query(L,R,l,mid,2*node);
    else ans=query(L,R,mid+1,r,2*node+1);
    return ans;
}
ll path(int x,int y){
    ll ret=0;
    while(top[x]!=top[y]){
       if(dp[top[x]]<dp[top[y]]) swap(x,y);
       ret=max(ret,query(id[top[x]],id[x]));
       x=par[top[x]];
    }   
     if(dp[x]>dp[y]) swap(x,y);
     ret=max(ret,query(id[x],id[y]));
     return ret;
}
int main(){
    cin>>n>>q;
    for(int i=0;i<n-1;i++){
        ll u,v;cin>>u>>v;
        adj[v].push_back(u);
        adj[u].push_back(v);
    } dfs(1,0);
      dfs_hld(1,1);
      for(int i=0;i<q;i++){
          ll t,v;cin>>t>>v;
          if(t==0) upd(id[v]);
          else{
              ll res=path(1,v);
              if(res==0) cout<<-1<<endl;
              else cout<<tour[res]<<endl;
          }
      }
}