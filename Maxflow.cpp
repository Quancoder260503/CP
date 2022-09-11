#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz1=5e6+1;
const int sz=2e5+1;
int n,q;
bool yes=0;
ll res=0;
ll timer=0;
int dp[sz];
ll st[sz],en[sz],ans[sz];
int up[31][sz];
vector<int>adj[sz];
ll freq[sz];
const int mod=1e9+7;
int jump(int x, int d){
    for(int i=0;i<=20;i++){
        if((d>>i)&1){x=up[i][x];freq[x]++;} 
    }  return x;
}
void dfs(int u){
     for(int i=1;i<=20;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v==up[0][u]) continue;
        dp[v]=dp[up[0][v]=u]+1;
        dfs(v);
    } 
}
int lca(ll a, ll b){
    if(dp[a]<dp[b]) swap(a,b);
    a=jump(a,dp[a]-dp[b]);
    if(a==b) return a;
    for(int i=20;i>=0;i--){
         int tA=up[i][a]; int tB=up[i][b];
         if(tA!=tB) {a=tA; b=tB;}
    } return up[0][a];
}   
ll dfs1(int u,int p){
    ll sum=0;
    for(auto v:adj[u]){
        if(v==p) continue;
        sum+=dfs1(v,u);
    } ans[u]=sum+st[u]-en[u]/2;
      return sum+st[u]-en[u];
}
int main(){   
    cin>>n>>q;
    for(int i=0;i<n-1;i++){
         ll u,v;cin>>u>>v;
         adj[u].push_back(v);
         adj[v].push_back(u);
    } dfs(1);
      for(int i=0;i<q;i++){
          ll u,v;cin>>u>>v;
          st[u]++;st[v]++;
          ll p=lca(u,v); en[p]+=2;
      }   
    dfs1(1,0);
    for(int i=1;i<=n;i++) res=max(res,ans[i]);
    cout<<res;
}    