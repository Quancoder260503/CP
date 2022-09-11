#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<map>
#include<vector>
#include<utility>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz1=5e6+1;
const int sz=2e5+1;
ll n,y,z,dx,p,a,c,b,m,q;
int movex[4]={0,0,1,-1};
int movey[4]={-1,1,0,0};
vector<array<ll,4>>edge;
bool yes=0;
ll res=0;
ll dp[sz];
ll up[21][sz];
array<ll,2>query[sz];
const int mod=998244353;
vector<ll>fac,finv,inv;
vector<ll>d1;
vector<array<ll,2>>ans;
vector<vector<ll>>d2;
vector<ll>anc[sz];
vector<ll>adj[sz];
ll compsize[sz];
ll parent[sz];
ll jump(ll x, ll d){
    for(int i=0;i<=20;i++){
        if((d>>i)&1) x=up[i][x];
    } return x;
}
void dfs(ll u,ll p){
     for(int i=1;i<=20;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v==up[0][u]) continue;
        dp[v]=dp[u]+1;
        up[0][v]=u;
        dfs(v,u);
    }
}
ll lca(ll a, ll b){
    if(dp[a]<dp[b]) swap(a,b);
    a=jump(a,dp[a]-dp[b]);
    if(a==b) return a;
    for(int i=20;i>=0;i--){
         ll tA=up[i][a]; ll tB=up[i][b];
         if(tA!=tB) {a=tA; b=tB;}
    } return up[0][a];
}    
int main(){   
    cin>>n>>q;
    for(int i=0;i<n-1;i++){
        ll u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    } 
      dp[1]=0; up[0][1]=0;
      dfs(1,0);
      for(int i=0;i<q;i++){
          ll u,v;
          cin>>u>>v;
          ll p=lca(u,v);
          ll x=dp[u]+dp[v]-2*dp[p];
          cout<<x<<endl;
      }
}    