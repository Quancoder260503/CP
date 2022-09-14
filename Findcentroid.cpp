#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int mod=998244353;
int n,x,k,i,j,w,q,m;
ll a[sz];
vector<ll>adj[sz];
ll dp[sz];
ll dfs(int u,int p){
    dp[u]=1;
    for(auto v:adj[u]){
        if(v==p) continue;
        dp[u]+=dfs(v,u);
    } return dp[u];
}
ll dfsct(int u,int p){
    for(auto v:adj[u]){
        if(v==p) continue;
        if(dp[v]*2>n) return dfsct(v,u);
    } return u;
}
int main(){
     cin>>n;
     for(int i=0;i<n-1;i++){
         ll u,v;cin>>u>>v;
         adj[u].push_back(v);
         adj[v].push_back(u);
     }
     dfs(1,0);
     cout<<dfsct(1,0)<<endl;
}