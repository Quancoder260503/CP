#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
//This is the correct idea for the problems however still need to hash and some optimization to get AC 
int n,x,k,i,q,j,w,m,mod;
ll trs[sz];
string sup[19][sz];
string num[sz];
ll up[19][sz];
ll dp[sz];
ll tour[sz],id[sz],top[sz];
vector<ll>adj[sz];
int timer=1; 
string tree[sz<<1];
string tree1[sz<<1];
ll jump(int x,int d){
    for(int i=0;i<=18;i++){
        if((d>>i)&1) x=up[i][x];
    }return x;
}
ll dfs(int u){
    trs[u]=1;
    for(int i=1;i<=18;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v==up[0][u]) continue;
        dp[v]=dp[up[0][v]=u]+1;
        trs[u]+=dfs(v);
    } return trs[u];
}
void dfs_hld(int u,int anc){
    tour[timer]=u;
    id[u]=timer++;
    top[u]=anc;
    int hchi=0;
    int hsize=0;
    for(auto v:adj[u]){
        if(v==up[0][u]) continue;
        if(hsize<trs[v]){
            hsize=trs[v];
            hchi=v;
        }
    }
    if(hchi==0) return;
    dfs_hld(hchi,anc);
    for(auto v:adj[u]){
        if(v==up[0][u] or v==hchi) continue;
        dfs_hld(v,v);
    } 
}
void build(int l=1,int r=n,int p=1){
    if(l==r){
        tree[p]=tree1[p]=num[tour[l]];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,2*p);
    build(mid+1,r,2*p+1);
    tree[p]=tree[2*p]+tree[2*p+1];
    tree1[p]=tree1[2*p+1]+tree1[2*p];
}
string query(int L,int R, int l=1,int r=n,int p=1){
    if(L>r or l>R) return"";
    if(L<=l and r<=R) return tree1[p];
    int mid=(l+r)>>1;
    string s0=query(L,R,mid+1,r,2*p+1)+query(L,R,l,mid,2*p);
    return s0;
}
string query1(int L,int R, int l=1,int r=n,int p=1){
    if(L>r or l>R) return "";
    if(L<=l and r<=R) return tree[p];
    int mid=(l+r)>>1;
    string s0=query1(L,R,l,mid,2*p)+query1(L,R,mid+1,r,2*p+1);
    return s0;
}
string path_up(int x,int y){
    string s="";
    while(top[x]!=top[y]){
        if(dp[top[x]]<dp[top[y]]) swap(x,y);
        s=s+query(id[top[x]],id[x]);
        x=up[0][top[x]];
    }
    if(dp[x]>dp[y]) swap(x,y);
    s=s+query(id[x],id[y]);
    return s;
}
string path_down(int x,int y){
    string s="";
    while(top[x]!=top[y]){
        if(dp[top[x]]<dp[top[y]]) swap(x,y);
        s=query1(id[top[x]],id[x])+s;
        x=up[0][top[x]];
    }
    if(dp[x]>dp[y]) swap(x,y);
    s=query1(id[x]+1,id[y])+s;
    return s;
}
int lca(int a ,int b){
    if(dp[a]<dp[b]) swap(a,b);
    a=jump(a,dp[a]-dp[b]);
    if(a==b) return a;
    for(int i=18;i>=0;i--){
        int ta=up[i][a]; int tb=up[i][b];
        if(ta!=tb) a=ta,b=tb;
    } return up[0][a];
}
ll convert(string s, ll mod){
    ll res=0; ll mul=1;
    for(int i=s.length()-1;i>=0;i--){
        res+=(ll) mul*((s[i]-'0')%mod);
        mul=((ll) mul*10)%mod;
    } 
    return res;
}
int main(){
    cin>>n>>mod>>q;
    for(int i=0;i<n-1;i++){
         ll u,v;cin>>u>>v;
         adj[v].push_back(u);
         adj[u].push_back(v);
    }
    for(int i=1;i<=n;i++) cin>>num[i];
    dfs(1); 
    dfs_hld(1,1);
    build();
    for(int i=0;i<q;i++){
        ll u,v;cin>>u>>v;
        int t=lca(u,v);
        string s0=path_up(u,t)+path_down(t,v);
        ll res=convert(s0,mod);
        cout<<res<<endl;
    }
}
