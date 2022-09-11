#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
ll n,k,m,q;
int timer=1;
int trs[sz],dp[sz];
int id[sz],top[sz],a[sz];
int par[sz];
vector<ll>adj[sz];
struct node{
    ll val;
    ll lzadd;
    node(){};
} tree[sz<<2];
void push(int p){
    tree[p].val=tree[2*p+1].val+tree[2*p].val;
}
void pushdown(int p,int l,int mid ,int r){
    if(tree[p].lzadd!=0){
        tree[2*p+1].val+=tree[p].lzadd*(r-mid);
        tree[2*p].val+=tree[p].lzadd*(mid-l+1);
        tree[2*p+1].lzadd+=tree[p].lzadd;
        tree[2*p].lzadd+=tree[p].lzadd;
        tree[p].lzadd=0;
    }
}
void add(ll x ,int L,int R,int l=1,int r=n,int p=1){
     if(l>R or L>r) return;
     if(L<=l and r<=R){
         tree[p].val+=(r-l+1)*x;
         tree[p].lzadd+=x;
         return;
     }
       int mid=(l+r)>>1;
       pushdown(p,l,mid,r);
       add(x,L,R,l,mid,2*p);
       add(x,L,R,mid+1,r,2*p+1);
       push(p);
}
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
ll query(int L,int R,int l=1,int r=n,int node=1){
    if(L>r or R<l) return 0;
    if(L<=l and r<=R) return tree[node].val;
    int mid=(l+r)>>1;
    pushdown(node,l,mid,r);
    return query(L,R,l,mid,2*node)+query(L,R,mid+1,r,2*node+1);
}
void upd(int x,int y){
    while(top[x]!=top[y]){
        if(dp[top[x]]<dp[top[y]]) swap(x,y);
        add(1,id[top[x]],id[x]);
        x=par[top[x]];
    } 
      if(dp[x]>dp[y]) swap(x,y);
      add(1,id[x],id[y]);
      add(-1,id[x],id[x]);
}
ll path(int x,int y){
    ll ret=0;
    while(top[x]!=top[y]){
       if(dp[top[x]]<dp[top[y]]) swap(x,y);
       ret+=query(id[top[x]],id[x]);
       x=par[top[x]];
    }   
     if(dp[x]>dp[y]) swap(x,y);
     ret+=query(id[x],id[y]);
     ret-=query(id[x],id[x]);
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
           char c;ll u,v;cin>>c>>u>>v;
           if(c=='P') upd(u,v);
           else{
               ll res=path(u,v);
               cout<<res<<endl;
           }
      }
}