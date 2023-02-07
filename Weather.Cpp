#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 5e5 + 5;
int up[21][N + 1];
int dp[N + 1];
int a[N + 1];
int n,m,q,timer;
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
int trs,dsz,psz;
vector<pair<int,int>>bridges; 
bool vis[N + 1]; 
int comp[N + 1]; 
int st[N + 1],low[N + 1];
int fa[N + 1];
int find(int u){
     if(u == fa[u]) return u;
     return fa[u] = find(fa[u]);
}
void unite(int u,int v){
     u = find(u); v = find(v);
     if(u == v) return;
     fa[u] = v;
}
void dfs(int u,int p){
    a[u] = low[u] = ++dsz;
    comp[u] = timer;
    for(int i = 0; i < tadj[u].size(); i++){
        int v = tadj[u][i];
        if(v == p) continue;
        if(!a[v]){
            dfs(v,u);
            low[u] = min(low[u] , low[v]);
            if(low[v] > a[u]) bridges.push_back({u,v});
            else unite(u,v);
        }
        else low[u] = min(a[v] , low[u]);
    }
}
void dfs_calc(int u){
    vis[u] = 1; 
    for(int i = 1; i < 21; i++){
         up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i]; 
        if(vis[v]) continue;
        dp[v] = dp[up[0][v] = u] + 1;
        dfs_calc(v);
    }
} 
int lca(int a, int b){
    if(dp[a] < dp[b]) swap(a,b);
    int d = dp[a] - dp[b];
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
int main(){
     scanf("%d",&n);
     scanf("%d",&m); 
     for(int i = 1; i <= n; i++) fa[i] = i; 
     for(int i = 0; i < m; i++){
         int u,v; scanf("%d%d",&u,&v);
         tadj[u].push_back(v);
         tadj[v].push_back(u); 
     }
     for(int i = 1; i <= n; i++){
         if(!a[i]){
              ++timer;
              dfs(i,0);
         }
     }
     for(int i = 1; i <= n; i++) find(i); 
     for(int i = 0; i < bridges.size(); i++){
         int u = bridges[i].first;
         int v = bridges[i].second;
         adj[fa[u]].push_back(fa[v]);
         adj[fa[v]].push_back(fa[u]); 
     }
     for(int i = 1; i <= n; i++){
         if(!vis[i]) dfs_calc(i);
     }
     long long ans = 0;
     for(int i = 1; i <= n; i++){
         for(int j = i + 1; j <= n; j++){
              if(fa[i] == fa[j]) continue;
              //long long dis = dp[fa[i]] + dp[fa[j]] - 2 * dp[lca(fa[i],fa[j])];
              //cout<<fa[i]<<' '<<fa[j]<<' '<<dis<<endl; 
              ans += dp[fa[i]] + dp[fa[j]] - 2 * dp[lca(fa[i],fa[j])]; 
         }
     }
     cout<<ans<<endl; 
}
