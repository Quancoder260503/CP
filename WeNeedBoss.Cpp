#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 5e5 + 5;
int up[21][N + 1];
int dp[N + 1];
int a[N + 1];
int n,m,q;
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
int trs,dsz,psz;
vector<pair<int,int>>bridges; 
bool vis[N + 1]; 
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
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i]; 
        if(vis[v]) continue;
        dp[v] = dp[u] + 1;
        dfs_calc(v);
    }
} 
int main(){
     scanf("%d%d",&n,&m);
     for(int i = 1; i <= n; i++) fa[i] = i; 
     for(int i = 0; i < m; i++){
         int u,v; scanf("%d%d",&u,&v);
         tadj[u].push_back(v);
         tadj[v].push_back(u); 
     }
     dfs(1,0);
     for(int i = 0; i < bridges.size(); i++){
         int u = bridges[i].first;
         int v = bridges[i].second;
         //cout<<fa[u]<<' '<<fa[v]<<endl; 
         adj[fa[u]].push_back(fa[v]);
         adj[fa[v]].push_back(fa[u]); 
     }
     for(int i = 1; i <= n; i++){
         if(!vis[i]) dfs_calc(i);
     }
     int length = 0; 
     int start = 0;
     for(int i = 1; i <= n; i++){
          if(length < dp[i]){
               length = dp[i];
               start = i; 
          }
     }
     memset(dp,0,sizeof(dp));
     memset(vis,0,sizeof(vis));
     dfs_calc(start);
     int ans = 0;
     for(int i = 1; i <= n; i++) ans = max(ans, dp[i]);
     cout<<ans<<endl; 
}
