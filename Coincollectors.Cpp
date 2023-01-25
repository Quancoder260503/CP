#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 5;
const int M = 1e6 + 5;
const int mod = (1 << 32); 
long long n,m,k,q,bridges,comp;
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
deque<int>S;
int up[21][N + 1];
int in[N + 1];
long long a[N + 1],val[N + 1];
int out[N + 1],low[N + 1]; 
bool vis[N + 1];
long long dp[N + 1];
int timer = 1; 
vector<pair<int,int>>edges;
void dfs(int u){
     in[u] = low[u] = timer++;
     vis[u] = 1;
     S.push_back(u);
     for(int i = 0; i < adj[u].size();i++){
            int v = adj[u][i];
            if(!in[v]) dfs(v);
            if (vis[v]) low[u] = min(low[u],low[v]);
     }
     if(in[u] == low[u]){
        comp++;  long long sum = 0; 
        while(1){
             int v = S.back();
             S.pop_back();
             out[v] = comp; 
             vis[v] = 0; 
             sum += a[v];
             if(u == v) break; 
        }   
        val[comp]+= sum; 
    }
}
long long calc(int u){
    if(dp[u]) return dp[u];
    dp[u] = val[u]; 
    for(int i = 0; i < tadj[u].size(); i++){
         int v = tadj[u][i]; 
         dp[u] = max(dp[u], val[u] + calc(v));
    }
    return dp[u];
}
int main(){
     scanf("%d%d",&n,&m);
     for(int i = 1; i <= n; i++) scanf("%lld",&a[i]);
     for(int i = 0; i < m; i++){
          int u,v; scanf("%d%d",&u,&v);
          adj[u].push_back(v);
     }
     for(int i = 1; i <= n; i++) if(!in[i]) dfs(i);
     memset(vis,0,sizeof(vis));
     for(int i = 1; i <= n; i++){
          for(int j = 0; j < adj[i].size(); j++){
               int v = adj[i][j];
               if(out[v] == out[i]) continue;
               tadj[out[v]].push_back(out[i]);
          }
     }
     long long ans = 0;
     for(int i = 1; i <= n; i++){
          if(!vis[i]) calc(i);
     }
     for(int i = 1; i <= n; i++) ans = max(ans,dp[i]); 
     cout<<ans<<endl; 
}
