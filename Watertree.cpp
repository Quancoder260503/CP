#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=5e5+1;
int n,x,k,i,q,j,w,m,mod;
ll trs[sz];
array<ll,2>chld[sz];
ll dp[sz];
ll id[sz],top[sz];
ll par[sz],en[sz];
vector<ll>adj[sz];
int timer=1; 
struct node{
    ll w;
    ll lzadd;
    node(){};
} tree[sz<<2];
ll dfs(int u){
    trs[u]=1;
    for(auto v:adj[u]){
        if(v==par[u]) continue;
        dp[v]=dp[par[v]=u]+1;
        trs[u]+=dfs(v);
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
void push_down(int p,int l,int mid,int r){
    if(tree[p].lzadd!=0){
        if(tree[p].lzadd==-1) tree[2*p].w=tree[2*p+1].w=0;
        else{
            tree[2*p].w=mid-l+1;
            tree[2*p+1].w=r-mid;
        }
        tree[2*p].lzadd=tree[p].lzadd;
        tree[2*p+1].lzadd=tree[p].lzadd;
        tree[p].lzadd=0;
    }
}
void update(int val,int L,int R,int l=1,int r=n,int p=1){
    if(l>R or r<L) return;
    if(L<=l and r<=R){
        if(val==-1) tree[p].w=0;
        else tree[p].w=(r-l+1);
        tree[p].lzadd=val;
        return;
    }
    int mid=(l+r)>>1;
    push_down(p,l,mid,r);
    update(val,L,R,l,mid,2*p);
    update(val,L,R,mid+1,r,2*p+1);
}
ll query(int L,int R,int l=1,int r=n,int p=1){
    if(l>R or r<L) return 0;
    if(L<=l and r<=R) return tree[p].w;
    int mid=(l+r)>>1;
    push_down(p,l,mid,r);
    return query(L,R,l,mid,2*p)+query(L,R,mid+1,r,2*p+1);
}
void path(int x,int y){
    while(top[y]!=top[x]){
        if(dp[top[x]]<dp[top[y]]) swap(x,y);
        update(-1,id[top[x]],id[x]);
        x=par[top[x]];
    }
    if(dp[x]>dp[y]) swap(x,y);
    update(-1,id[x],id[y]);
}
int main(){
    cin>>n;
    for(int i=0;i<n-1;i++){
         ll u,v;cin>>u>>v;
         adj[v].push_back(u);
         adj[u].push_back(v);
    }
    dfs(1); 
    dfs_hld(1,1);
    cin>>q;
     for(int i=0;i<q;i++){
        int t,u;cin>>t>>u;
        if(t==1) update(1,id[u],en[u]);
        else if(t==2) path(1,u);
        else if (t==3) cout<<query(id[u],id[u])<<endl;
    }
}