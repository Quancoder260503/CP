#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int mod=1e9+7;
int p,n,mx_d,q,timer,cnt0,cnt1;
ll cur0,cur1,ans;
int trs[sz];
vector<int>adj[sz];
set<pair<int,int>>s;
int dp[sz];
ll a[sz];
bool vis[sz];
int cnt[sz];
int d[sz];
ll add(ll a, ll b) {
    a=(a+b)%mod;
    return a;
}
ll mul(ll a, ll b) {
    a = (a%mod+mod)%mod;
    b = (b%mod+mod)%mod;
    return a*b%mod;
}
int dfs(int u, int p) {
  trs[u] = 1;
  for(auto v : adj[u]) if(v != p and !vis[v]) {
        trs[u] += dfs(v, u);
    }
  return trs[u];
}
int centroid(int u, int p, int n) {
    for(auto v : adj[u]) 
        if(v != p and !vis[v]) {
          if(trs[v] > n / 2) return centroid(v, u, n);
   }
  return u;
}
void path(int u,int p,bool c,ll val,int d=1){
     if(c){
         if(d&1){
             ll x=add(val,a[u]);
             cur1=add(cur1,x);
             cnt1++;
         }
         else{
             ll x=add(-val,a[u]);
             ll x1=add(val,-a[u]);
             ans=add(ans,x);
             cur0=add(cur0,x1);
             cnt0++;
         }
     }
     else{
         ll x=mul(cnt1,(a[u]+val));
         ll y=mul(cnt0,(a[u]-val));
         ll x1=add(x,cur1);
         ll y1=add(y,-cur0);
         if(d&1) ans=add(ans,x1);
         else ans=add(ans,y1);
     }
     ll x;
     if(d&1) x=add(val,a[u]);
     else x=add(val,-a[u]);
     for(auto v:adj[u]){
         if(v==p or vis[v]) continue;
         path(v,u,c,x,d+1);
     }
}
void build(int u,int p){
    int n=dfs(u,p);
    int c=centroid(u,p,n);
    vis[c]=1;
    cur0=cur1=cnt0=cnt1=0;
    int cntx=0;
    for(auto v:adj[c]){
         if(vis[v]) continue;
         path(v,c,0,0);
         path(v,c,1,-a[c]);
         cntx++;
    }
    for(auto v:adj[c]){
        if(!vis[v]) build(v,c);
    }
} 
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build(1,0);
    ans=(ll) mul(ans,2);
    for(int i=1;i<=n;i++){
        ans=add(ans,a[i]);
    }
    ans=add(ans,mod);
    cout<<ans<<endl;
}
