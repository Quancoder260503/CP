#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 5;
const int M = 1e6 + 5;
const int mod = (1 << 32); 
long long n,m,k,q,bridges;
long long a[N + 1];
vector<pair<int,int>>adj[N + 1]; 
int up[21][N + 1];
int in[N + 1];
int out[N + 1];
int low[N + 1]; 
bool use[N + 1];
int dp[N + 1];
int timer = 1; 
vector<pair<int,int>>edges;
void dfs(int u,int p){
     in[u] = low[u] = timer++; 
     for(int i = 0; i < adj[u].size(); i++){
           auto v = adj[u][i];
           if(v.first == p) continue;
           if(!in[v.first]){
              edges.push_back({u,v.first});
              use[v.second] = 1; 
              dp[v.first] = dp[u] + 1;
              dfs(v.first,u);
              low[u] = min(low[u],low[v.first]);
              if(low[v.first] == in[v.first]) bridges++; 
           }
           else low[u] = min(low[u],in[v.first]);
     }
}
int main(){
     scanf("%d%d",&n,&m);
     vector<pair<int,int>>Nedges;
     for(int i = 0; i < m; i++){
          int u,v; scanf("%d%d",&u,&v);
          adj[u].push_back({v,i});
          adj[v].push_back({u,i});
          Nedges.push_back({u,v});
     }
     int components = 0; 
     for(int i = 1; i <= n; i++){
         if(!in[i]){
             components++;
             dfs(i,0);
         }
     }
     if(bridges > 0 or components > 1){
          cout<<"IMPOSSIBLE"<<endl;
          return 0; 
     }
     for(int i = 0; i < Nedges.size(); i++){
           if(use[i]) continue;
           int u = Nedges[i].first; int v = Nedges[i].second;
           if(dp[u] < dp[v]) swap(u,v);
           edges.push_back({u,v});
     }
     for(int i = 0; i < edges.size(); i++){
           cout<<edges[i].first<<' '<<edges[i].second<<endl;
     }
}
