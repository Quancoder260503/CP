#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int inf=1e7+5;
int n,m,src,d,cnt;
int a[sz];
vector<int>adj1[sz];
vector<int>adj[sz];
vector<pair<int,int>>edge;
int ds[sz];
int dp[sz];
bool vis[sz];
void bfs(int src){
    queue<int>q;
    q.push(src);
    ds[src]=0;
    while(q.size()){
         int u=q.front();
         q.pop();
         for(int i=0;i<adj1[u].size();i++){
              int v=adj1[u][i];
              if(ds[v]>ds[u]+1){
                    ds[v]=ds[u]+1;
                    q.push(v);
              }
         }
    }
}
void dfs(int u){
    vis[u]=1;
    dp[u]=ds[u];
    for(int i=0;i<adj1[u].size();i++){
         int v=adj1[u][i];
         if(!vis[v] and ds[u]<ds[v]) dfs(v);
         if(ds[u]<ds[v]) dp[u]=min(dp[u],dp[v]);
         else dp[u]=min(dp[u],ds[v]);
    }
}
void solve(){
     cin>>n>>m;
     for(int i=1;i<=n;i++){ 
         ds[i]=inf;
         edge.clear();
         vis[i]=0;
         adj1[i].clear();
     }
     for(int i=0;i<m;i++){
          int u,v ; cin>>u>>v;
          adj1[u].push_back(v);
     }
     bfs(1);
     dfs(1);
     for(int i=1;i<=n;i++){
         cout<<dp[i]<<' ';
    }
    cout<<endl;
}
int main(){
     int t; cin>>t;
     while(t--){
          solve();
     }
} 
