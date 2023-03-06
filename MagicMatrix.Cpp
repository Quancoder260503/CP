#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
int n;
int up[22][N + 1];
int dp[22][N + 1]; 
int g[2501][2501];
int ds[N + 1];
int fa[N + 1]; 
vector<pair<int,int>>adj[N + 1];
int find(int u){
     if(u == fa[u]) return u;
     return fa[u] = find(fa[u]); 
}
void unite(int u,int v){
     u = find(u); v = find(v);
     if(u == v) return; 
     fa[v] = u; 
}
void dfs_calc(int u){
    for(int i = 1; i < 21 ; i++){
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for(int i = 0; i < adj[u].size(); i++){
        auto v = adj[u][i]; 
        if(v.first == up[0][u]) continue;
        ds[v.first] = ds[up[0][v.first] = u] + 1;
        dp[0][v.first] = v.second;  
        dfs_calc(v.first);
    }
}
int lca(int a, int b){
    if(ds[a] < ds[b]) swap(a,b);
    int d = ds[a] - ds[b];
    for(int i = 0; i < 21 ; i++){
        if( (d >> i) & 1) a = up[i][a];
    }
    if(a == b) return a;
    for(int i = 20; i >= 0; i--){
         int tA = up[i][a]; int tB = up[i][b];
         if(tA != tB) {
            a = tA; b = tB;
         }
    } 
    return up[0][a];
} 
int jmpm(int x, int d){
      int ans = 0;    
      for(int i = 0; i < 21; i++){
          if((d >> i) & 1){
               ans = max(dp[i][x], ans); 
               x = up[i][x]; 
          }
     } 
     return ans; 
}
void push(){
      for(int i = 1; i < 21; i++){
           for(int j = 1; j <= n; j++){
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][up[i - 1][j]]); 
           }
      }
}
int main(){
    scanf("%d",&n); 
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
              scanf("%d",&g[i][j]); 
        }
    }
    for(int i = 1; i <= n; i++) fa[i] = i; 
    vector<pair<int,pair<int,int>>>edge;
    vector<pair<int,pair<int,int>>>nedge;
    for(int i = 1; i <= n; i++){ 
         for(int j = i; j <= n; j++){
                if(g[i][j] != g[j][i] or (g[i][j] != 0 and i == j)){
                      printf("NOT MAGIC\n");
                      return 0;
                }
                if(i != j) edge.push_back({g[i][j],{i,j}});
         }
    }
    sort(edge.begin(),edge.end());
    for(int i = 0; i < edge.size(); i++){
         int u = edge[i].second.first;
         int v = edge[i].second.second; 
         int w = edge[i].first;
         if(find(u) == find(v)){
             nedge.push_back({w,{u,v}});
             continue;
         }
         unite(u,v);
         adj[u].push_back({v,w});
         adj[v].push_back({u,w}); 
    }
    dfs_calc(1);
    push();
//    cout<<dp[0][4]<<endl; 
    for(int i = 0; i < nedge.size(); i++){
          int u = nedge[i].second.first;
          int v = nedge[i].second.second;
          int w = nedge[i].first;
          int anc = lca(u,v);
          if(w !=  max(jmpm(u,ds[u] - ds[anc]),jmpm(v,ds[v] - ds[anc]))){
                printf("NOT MAGIC\n");
                return 0; 
          }
    }
    printf("MAGIC\n");
    return 0; 
}
