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
const int sz=2e5+1;
ll n,y,z,dx,p,a,c,b,m,q;
int movex[4]={0,0,1,-1};
int movey[4]={-1,1,0,0};
vector<array<ll,4>>edge;
ll dp[sz];
ll dp1[25][sz];
ll up[25][sz];
ll ans[sz];
vector<array<ll,2>>adj[sz];
ll dir[sz];
ll jump(ll x, ll d){
    for(int i=0;i<=20;i++){
        if((d>>i)&1) x=up[i][x];
    } return x ;
}
void dfs(int u){
    for(int i=1;i<=20;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v[0]==up[0][u]) continue;
        dp[v[0]]=dp[up[0][v[0]]=u]+1;
        dir[v[0]]=v[1];
        dfs(v[0]);
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
void add(int u,int d,ll w){
    for(int i=20;i>=0;i--){
        if(d&(1<<i)){
           dp1[i][u]=min(dp1[i][u],w);
           u=up[i][u];
        }    
    }
}
void upd(int u, int v, ll w){
    int x=lca(u,v);
    add(u,dp[u]-dp[x],w);
    add(v,dp[v]-dp[x],w);
}
void push(){
    for(int i=20;i>0;i--){
        for(int j=1;j<=n;j++){
            dp1[i-1][j]=min(dp1[i][j],dp1[i-1][j]);
            dp1[i-1][up[i-1][j]]=min(dp1[i-1][up[i-1][j]],dp1[i][j]);
        }
    }
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n-1;i++){
        ll u,v;cin>>u>>v;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    } 
     for(int i=0;i<=20;i++){
         for(int j=1;j<=n;j++){
             dp1[i][j]=INT_MAX;
         }
     }
     dfs(1);
     for(int i=0;i<q;i++){
         ll u,v,w;cin>>u>>v>>w;
         upd(u,v,w);
    } push();
      for(int i=1;i<=n;i++){
          if(dir[i]==0) continue;
          if(dp1[0][i]==INT_MAX) ans[dir[i]]=-1;
          else ans[dir[i]]=dp1[0][i];
      } 
    for(int i=1;i<=n-1;i++) cout<<ans[i]<<endl;
}