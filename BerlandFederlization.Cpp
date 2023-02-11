#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 401;
long long  n,q,l,r,m;
long long dp[N + 1][N + 1];
int trace[N + 1][N + 1][N + 1];
int road[N + 1][N + 1];
int fa[N + 1];
vector<int>adj[N + 1];
vector<int>tadj[N + 1]; 
void dfs(int u,int p){
    for(int i = 0; i <= n; i++) dp[u][i] = INT_MAX;
    dp[u][1] = 0;
    fa[u] = p;
    int curr = 0;
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(v == p) continue;
        dfs(v,u);
        tadj[u].push_back(v);
        curr++; 
        for(int k = q; k >= 0; k--){
           dp[u][k]++; 
           for(int j = 0; j <= k; j++){
             if(dp[u][k] > dp[u][k - j] + dp[v][j]){
                    dp[u][k] = dp[u][k - j] + dp[v][j];
                    trace[u][k][curr] = j;
                 }
             }
        }
    }
}
void dfs1(int u,int p,int size){
    for(int i = tadj[u].size() - 1; i >= 0;i--){
          int v = tadj[u][i];
          if(v == p) continue;
          int w = trace[u][size][i + 1];
          if(w)  dfs1(v,u,w);
          else{
              cout<<road[v][u]<<" ";
          }
          size -= w;
    }
}
int main(){
    scanf("%d%d",&n,&q); 
    for(int i = 1; i <= n - 1; i++){
         int u,v; scanf("%d%d",&u,&v);
         adj[u].push_back(v);
         adj[v].push_back(u);
         road[u][v] = road[v][u] = i;
    }
    dfs(1,0);
    long long res = dp[1][q];  
    int opt = 1;
    for(int i = 2; i <= n; i++){
        if(res > dp[i][q] + 1){
           // cout<<dp[i][q]<<' '<<i<<endl;
            res = dp[i][q] + 1;
            opt = i;
        }
    }
    cout<<res<<endl;
    if(res){
        if(opt != 1) cout<<road[opt][fa[opt]]<<" ";
        dfs1(opt,0,q);
    }
}
