#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e3 + 10;
const int INF = 1e7 + 10; 
long long n,m,q,dsz,M,res;
int timer = 1;
vector<int>adj[N + 1];
int cost[N + 1], pel[N + 1]; 
int fa[N + 1], comp[N + 1];
bool vis[N + 1];
int up[22][N + 1];
long long dp[N + 1][N + 1],val[N + 1];
void dfs(int u,int p){
     for(int i = 0; i <= m; i++) dp[u][i] = -INT_MAX; 
     dp[u][cost[u]] = pel[u]; 
     for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(v == p) continue;
            dfs(v,u);
            for(int j = m; j >= 0; j--){
                 for(int k = 0; k <= j; k++){
                     dp[u][j] = max(dp[u][j],dp[u][j - k] + dp[v][k]); 
                 }
            }
      }    
}
int main(){
     scanf("%d%d",&n,&m); 
     for(int i = 2; i <= n; i++) scanf("%d",&pel[i]);
     for(int i = 2; i <= n; i++) scanf("%d",&cost[i]); 
     for(int i = 1; i < n; i++){
          int u,v; scanf("%d%d",&u,&v);
          adj[u].push_back(v);
          adj[v].push_back(u); 
     }
     dfs(1,0);
     long long ans = 0; 
     for(int i = 0; i <= m; i++) ans = max(ans, dp[1][i]);
     printf("%d",ans); 
}
