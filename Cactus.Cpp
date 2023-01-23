#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 4e5 + 5;
const int M = 4e5 + 5;
const int mod = 1e9 + 7; 
long long n,m,k,q,cnt;
long long a[N + 1];
vector<int>adj[N + 1]; 
long long pw2[N + 1];
bool bl[N + 1];
int up[21][N + 1];
int in[N + 1],ord[N + 1]; 
bool vis[N + 1];
int comp[N + 1],low[N + 1]; 
int dp[N + 1],dp1[N + 1];
int timer = 1; 
vector<pair<int,int>>edges;
void dfs(int u,int p){
     comp[u] = cnt; 
     ord[timer] = u; 
     in[u] = low[u] = timer++; 
     for(int i = 1; i < 21; i++){
          up[i][u] = up[i - 1][up[i - 1][u]];
     }
     for(int i = 0; i < adj[u].size(); i++){
           int v = adj[u][i];
           if(v == p) continue;
           if(!in[v]){
              dp[v] = dp[up[0][v] = u] + 1;
              dfs(v,u);
              low[u] = min(low[u],low[v]);
           }
           else low[u] = min(low[u],in[v]);
     }
}
long long jump(int x,int d){
    for(int i = 0; i < 21 ; i++){
        if( (d >> i) & 1) x = up[i][x];
    } 
    return x;
}
int lca(int a, int b){
    if(dp[a] < dp[b]) swap(a,b);
    a = jump(a,dp[a] - dp[b]);
    if(a == b) return a;
    for(int i = 20; i >= 0; i--){
         int tA = up[i][a]; int tB = up[i][b];
         if(tA != tB) a = tA, b = tB;
    } 
    return up[0][a];
}
void calc(int u){
    vis[u] = 1; 
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(vis[v]) continue;
        dp1[v] = dp1[u] + bl[v];
        calc(v);
    }
}
int main(){
     scanf("%d%d",&n,&m);
     for(int i = 0; i < m; i++){
          int u,v; scanf("%d%d",&u,&v);
          adj[u].push_back(v);
          adj[v].push_back(u);
     }
     scanf("%d",&q); 
     for(int i = 1; i <= n; i++){
          if(in[i]) continue; 
          cnt++; 
          dfs(i,0);
     }
     for(int i = 1; i <= n; i++){
           if(in[i] != low[i]){
                //bl[i] = 1;
                bl[ord[low[i]]] = 1; 
           }
     }
     pw2[0] = 1; 
     for(int i = 1; i <= n; i++){
         if(vis[i]) continue;
         dp1[i] = bl[i];
         calc(i);
     }
     for(int i = 1; i <= n; i++){
           if(in[i] != low[i]){
                bl[i] = 1; 
           }
     }
     for(int i = 1; i <= N; i++) pw2[i] = pw2[i - 1] % mod * 2 % mod;
     for(int i = 1; i <= q; i++){
          int u,v; scanf("%d%d",&u,&v); 
          if(comp[u] != comp[v]){
               cout<<0<<endl; 
               continue; 
          }
          else{
               int anc = lca(u,v);
               ///cout<<dp1[anc]<<' '<<dp1[v]<<endl;
               int val = dp1[u] + dp1[v] - 2 * dp1[anc] +  bl[anc] ;
               long long ans = pw2[val]; 
               cout<<ans<<endl; 
          }
     }
} 
