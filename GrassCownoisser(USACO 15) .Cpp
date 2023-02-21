#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 4e5 + 10;
const int mod = 1e9 + 7;
long long n,m,k,q,component,ans;
char a[N + 1];
int timer = 1;
vector<int>S; 
long long dp[N + 1],dp1[N + 1]; 
bool vis[N + 1]; 
int in[N + 1], low[N + 1]; 
int fa[N + 1]; 
long long g[2001][2001];
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
vector<int>radj[N + 1];
long long val[N + 1];
void dfs(int u){
     in[u] = low[u] = timer++;
     S.push_back(u);
     for(int i = 0; i < adj[u].size();i++){
            int v = adj[u][i];
            if(vis[v]) continue;
            if(!in[v]){
                 dfs(v);
                 low[u] = min(low[u],low[v]);
            }
            else low[u] = min(low[u],in[v]);
     }
     if(in[u] == low[u]){ 
        component++;
        while(1){
             int v = S.back();
             S.pop_back();
             fa[v] = component;  
             vis[v] = 1; 
             if(u == v) break; 
        }   
    }
}
void calc(int u){
      for(int i = 0; i < tadj[u].size(); i++){
           int v = tadj[u][i];
           if(dp[v] < dp[u] + val[v]){
               dp[v] = dp[u] + val[v];
               calc(v);
           }
      }
}
void rcalc(int u){
      for(int i = 0; i < radj[u].size(); i++){
           int v = radj[u][i];
           if(dp1[v] < dp1[u] + val[v]){
              dp1[v] = dp1[u] + val[v];
              rcalc(v);
           }
      }
}
int main(){
     scanf("%d%d",&n,&m); 
     vector<pair<int,int>>edges;
     for(int i = 0; i < m; i++){
          int u,v; scanf("%d%d",&u,&v);
          adj[u].push_back(v);
          edges.push_back({u,v});
     }
     for(int i = 1; i <= n; i++) if(!in[i]) dfs(i);
     for(int i = 1; i <= n; i++) val[fa[i]]++; 
     for(int i = 1; i <= n; i++){
          for(int j = 0; j < adj[i].size(); j++){
               int v = adj[i][j];
               if(fa[v] == fa[i]) continue;
               tadj[fa[i]].push_back(fa[v]);
               radj[fa[v]].push_back(fa[i]);
          }
     }
     long long ans = val[fa[1]]; 
     fill(dp,dp + n + 1, -INT_MAX); 
     fill(dp1,dp1 + n + 1, - INT_MAX); 
     dp[fa[1]] = dp1[fa[1]] = val[fa[1]]; 
     calc(fa[1]); 
     rcalc(fa[1]);
     for(int i = 0; i < edges.size(); i++){
           int u = edges[i].first; int v = edges[i].second; 
           u = fa[u]; v = fa[v]; 
           if(u == v) continue; 
           if(dp[v] == -INT_MAX or dp1[u] == - INT_MAX) continue; 
           ans = max(ans,  dp[v] + dp1[u] - val[fa[1]]); 
     }
     cout<<ans<<endl; 
     //for(int i = 1; i <= n; i++) cout<<dp[i]<<endl;
     ///calc(fa[1]);
}
