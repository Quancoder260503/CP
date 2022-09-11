#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
ll n,k,m,q;
int timer=1;
int trs[sz],dp[sz];
int id[sz],top[sz],a[sz];
int up[17][sz];
int tour[sz];
int par[sz];
array<ll,2> val[sz];
vector<ll>adj[sz];
const int mod=998244353;
struct node{
    ll ax;
    ll by;
    node(){};
} tree[sz<<2];
node seg[sz<<2];
void build(int l=1,int r=n,int p=1){
     if(l>r) return;
     tree[p].ax=seg[p].ax=1;
     if(l==r){
         tree[p].ax=seg[p].ax=val[tour[l]][0];
         tree[p].by=seg[p].by=val[tour[l]][1];
         return;
     } 
       int mid=(l+r)>>1;
       build(l,mid,2*p);
       build(mid+1,r,2*p+1);
       tree[p].ax=(tree[2*p].ax)%mod*(tree[2*p+1].ax)%mod;
       tree[p].by=(tree[2*p].by)%mod+(tree[2*p+1].by)%mod*(tree[2*p].ax)%mod;
       seg[p].ax=tree[p].ax;
       seg[p].by=(seg[2*p+1].by)%mod+(seg[2*p].by)%mod*(seg[2*p+1].ax)%mod;
}
ll dfs(int u,int p){
    trs[u]=1;
    for(int i=1;i<=16;i++){
         up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v==p) continue;
        par[v]=u;
        dp[v]=dp[up[0][v]=u]+1;
        trs[u]+=dfs(v,u);
    } 
    return trs[u];
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
ll jump(int x, int d){
    for(int i=0;i<=16;i++){
        if((d>>i)&1) x=up[i][x];
    } return x;
}
int lca(int a,int b){
    if (dp[a]<dp[b])swap(a,b);
    a=jump(a,dp[a]-dp[b]);
    if(a==b) return a;
    for(int i=16;i>=0;i--){
        int ta=up[i][a]; int tb=up[i][b];
        if(ta!=tb){
            a=ta;b=tb;
        }
    } return up[0][a];
}
void update(ll c,ll d,int L,int R,int l=1,int r=n,int p=1){
    if(l>R or L>r) return;
    if(L<=l and r<=R){
        tree[p].ax=seg[p].ax=c;
        tree[p].by=seg[p].by=d;
        return;
    }  
       int mid=(l+r)>>1;
       update(c,d,L,R,l,mid,2*p);
       update(c,d,L,R,mid+1,r,2*p+1); 
       tree[p].ax=(tree[2*p].ax)%mod*(tree[2*p+1].ax)%mod;
       tree[p].by=(tree[2*p].by)%mod+(tree[2*p+1].by)%mod*(tree[2*p].ax)%mod;
       seg[p].ax=tree[p].ax;
       seg[p].by=(seg[2*p+1].by)%mod+(seg[2*p].by)%mod*(seg[2*p+1].ax)%mod;
}
ll query1(ll x, int L,int R,int l=1,int r=n,int p=1){
    if(L>r or R<l) return x%mod;
    if(L<=l and r<=R) { ll ans=tree[p].ax%mod*x%mod+tree[p].by%mod;return ans;}
    int mid=(l+r)>>1;
    ll ans=query1(x,L,R,mid+1,r,2*p+1)%mod;
    ll ans1=query1(ans,L,R,l,mid,2*p)%mod;
    return ans1;
}
array<ll,2> query2(ll x,ll y,int L, int R,int l=1,int r=n,int p=1){
    if(L>r or R<l) return {x%mod,y%mod};
    if(L<=l and r<=R) {
        return {seg[p].ax%mod*x%mod,seg[p].ax%mod*y%mod+seg[p].by%mod};}
    int mid=(l+r)>>1;
    array<ll,2>ans=query2(x,y,L,R,l,mid,2*p);
    return query2(ans[0],ans[1],L,R,mid+1,r,2*p+1);
}
ll path(bool act,int x,int y,ll val){
      ll ret=val;
      ll a,b; a=1;b=0;
      while (top[x]!=top[y]){
          if(dp[top[x]]<dp[top[y]]) swap(x,y);
          if(act) ret=query1(ret,id[top[x]],id[x]);
          else{ 
               array<ll,2> t=query2(1,0,id[top[x]],id[x]); ll stor=a;
               a=a%mod*t[0]%mod; b=stor%mod*t[1]%mod+b%mod;
          }
          x=par[top[x]];
      }
    if(dp[x]>dp[y]) swap(x,y);
    if(act) ret=query1(ret,id[x]+1,id[y]);
    else{
         array<ll,2> t=query2(1,0,id[x],id[y]);  ll stor=a;
         a=a%mod*t[0]%mod; b=stor%mod*t[1]%mod+b%mod;
    }if(act) return ret;
    else return a%mod*val%mod+b%mod;
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>val[i][0]>>val[i][1];
    for(int i=0;i<n-1;i++){
        ll u,v;cin>>u>>v;
        u++;v++;
        adj[v].push_back(u);
        adj[u].push_back(v);
    } dfs(1,0);
      dfs_hld(1,1);
       build();
       for(int i=0;i<q;i++){
           ll t,u,v,d;cin>>t>>u>>v>>d;
           if(t==0) {
               u++; val[u][0]=v; val[u][1]=d;
               update(v,d,id[u],id[u]);
           }
           else{
               u++;v++;
               int p=lca(u,v);
               ll res=path(1,p,u,d)%mod;
               res=path(0,p,v,res)%mod;
               cout<<res<<endl;
           }
      }
}
