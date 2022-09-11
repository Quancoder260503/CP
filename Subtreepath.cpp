#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
ll n,k,m,q;
int timer=1;
int trs[sz],dep[sz];
int id[sz],top[sz],a[sz];
int en[sz];
int par[sz];
set<ll>col[sz];
vector<ll>adj[sz];
struct node{
    ll val;
    ll lzadd;
    node(){};
} tree[sz<<2];
void push(int p){
    tree[p].val=max(tree[2*p+1].val,tree[2*p].val);
}
void pushdown(int p){
    if(tree[p].lzadd!=0){
        tree[2*p+1].val+=tree[p].lzadd;
        tree[2*p].val+=tree[p].lzadd;
        tree[2*p+1].lzadd+=tree[p].lzadd;
        tree[2*p].lzadd+=tree[p].lzadd;
        tree[p].lzadd=0;
    }
}
void add(int x,int L,int R,int l=1,int r=n,int p=1){
     if(l>R or L>r) return;
     if(L<=l and r<=R){
         tree[p].val+=x;
         tree[p].lzadd+=x;
         return;
     } int mid=(l+r)>>1;
       pushdown(p);
       add(x,L,R,l,mid,2*p);
       add(x,L,R,mid+1,r,2*p+1);
       push(p);
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
    int hchi=0;
    int hsize=0;
    for(auto v:adj[u]){
        if(v==par[u]) continue;
        if(hsize<trs[v]){
            hsize=trs[v];
            hchi=v;
        }
    }
    if(hchi==0){
        en[u]=timer-1;
        return;
    }
    dfs_hld(hchi,anc);
    for(auto v:adj[u]){
        if(v==par[u] or v==hchi) continue;
        dfs_hld(v,v);
    } 
    en[u]=timer-1;
}
ll query(int L,int R,int l=1,int r=n,int node=1){
    if(L>r or R<l) return -INT_MAX;
    if(L<=l and r<=R) return tree[node].val;
    int mid=(l+r)>>1;
    pushdown(node);
    return max(query(L,R,l,mid,2*node),query(L,R,mid+1,r,2*node+1));
}
ll path(int x,int y){
    ll ret=-INT_MAX;
    while(top[x]!=top[y]){
       if(dep[top[x]]<dep[top[y]])swap(x,y);
       ret=max(ret,query(id[top[x]],id[x]));
       x=par[top[x]];
    }   
    if(dep[x]>dep[y]) swap(x,y);
     ret=max(ret,query(id[x],id[y]));
     return ret;
}
int main(){
    cin>>n;
    for(int i=0;i<n-1;i++){
        ll u,v;cin>>u>>v;
        adj[v].push_back(u);
        adj[u].push_back(v);
    } dfs(1,0);
      dfs_hld(1,1);
      cin>>q;
      for(int i=0;i<q;i++){
           int u,v;string ord;
           cin>>ord;
           if(ord=="add"){
               cin>>u>>v;
               add(v,id[u],en[u]);
           }else{
             cin>>u>>v;
             ll res=path(u,v);
             cout<<res<<endl;
         }
     }
}