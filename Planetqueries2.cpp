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
int deg[sz];
ll n,y,z,dx,p,a,c,b,m,q;
int movex[4]={0,0,1,-1};
int movey[4]={-1,1,0,0};
vector<array<ll,4>>edge;
bool yes=0;
ll res=0;
ll dp[sz];
ll up[25][sz];
ll succ[25][sz];
const int mod=998244353;
vector<ll>fac,finv,inv;
vector<ll>d1;
vector<array<ll,2>>ans;
vector<vector<ll>>d2;
vector<ll>anc[sz];
vector<ll>adj[sz];
bool vis[sz];
ll jump(ll x, ll d){
    for(int i=0;i<=20;i++){
        if((d>>i)&1) x=succ[i][x];
    } return x ;
}
void dfs(int u){
    if(vis[u]) return;
    vis[u]=1;
    dfs(succ[0][u]);
    dp[u]=dp[succ[0][u]]+1;
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){ 
      cin>>succ[0][i];
      if(succ[0][i]!=i) deg[succ[0][i]]++;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]) dfs(i);
    }
    for(int i=1;i<=20;i++){
        for(int j=1;j<=n;j++){
            succ[i][j]=succ[i-1][succ[i-1][j]];
        }
    }
    bool iscycled = true;
    for(int i=1;i<n;i++){
        if(deg[i]!=1){
            iscycled=false;
            break; 
        }
    }
    if(iscycled == true){
       for(int i=1;i<=q;i++){
            int u,v; cin>>u>>v;
            if(dp[u]>dp[v]) cout<<dp[u]-dp[v]<<endl;
            else cout<< n-(dp[v]-dp[u])<<endl;
       }   
       return 0; 
    }
    for(int i=0;i<q;i++){
        ll u,v;cin>>u>>v;
        ll p=jump(u,dp[u]);
        ll str=dp[u]-dp[v]; ll str1=dp[p]+dp[u];
        p=jump(p,dp[p]-dp[v]);
        u=jump(u,dp[u]-dp[v]);
        if(u==v) cout<<str<<endl;
        else if(v==p) cout<<-dp[v]+str1<<endl;
        else cout<<-1<<endl;
    }
} 
