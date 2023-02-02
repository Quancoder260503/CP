#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 5e5 + 5;
int up[21][N + 1];
int dp[N + 1],ds[N + 1];
int a[N + 1];
int n,m,q;
vector<pair<int,int>>tadj[N + 1];
vector<int>adj[N + 1];
char ans[N + 1]; 
int trs,dsz,psz;
vector<pair<int,int>>edges; 
vector<pair<int,int>>bridges; 
int cnt; 
bool vis[N + 1],use[N + 1],brid[N + 1]; 
int st[N + 1],low[N + 1];
int comp[N + 1];
int fa[N + 1];
int find(int u){
     if(u == fa[u]) return u;
     return fa[u] = find(fa[u]);
}
void unite(int u,int v){
     u = find(u); v = find(v);
     if(u == v) return;
     if(comp[u] > comp[v]) swap(u,v); 
     comp[v] += comp[u]; 
     fa[u] = v;
}
void dfs(int u,int p){
    a[u] = low[u] = ++dsz;
    for(int i = 0; i < tadj[u].size(); i++){
        auto x = tadj[u][i];
        int v = x.first;
        if(v == p) continue;
        if(!a[v]){
            dfs(v,u);
            low[u] = min(low[u] , low[v]);
            if(low[v] > a[u]) brid[x.second] = 1, bridges.push_back({u,v}); 
        }
        else low[u] = min(a[v] , low[u]);
    }
}
void dfs_calc(int u,int p){
    vis[u] = 1; 
    for(int i = 0; i < adj[u].size(); i++){
        auto v = adj[u][i]; 
        if(vis[v]) continue;
        ds[v] = ds[u] + 1; 
        dfs_calc(v,u);
        dp[u] += dp[v];
    }
     ///cout<<u<<; dp[u]<<' '<<dp[p]<<endl; 
} 
int main(){
     scanf("%d%d",&n,&m);
     for(int i = 1; i <= n; i++) fa[i] = i, comp[i] = 1; 
     for(int i = 0; i < m; i++){
         int u,v; scanf("%d%d",&u,&v);
         tadj[u].push_back({v,i});
         tadj[v].push_back({u,i}); 
         edges.push_back({u,v}); 
     }
     for(int i = 1; i <= n; i++){
          if(!a[i]) dfs(i,0); 
     }
     for(int i = 0; i < edges.size(); i++){
          if(brid[i]) continue;
          unite(edges[i].first,edges[i].second); 
     }
     for(int i = 1; i <= n; i++) find(i); 
     for(int i = 0; i < bridges.size(); i++){
          int u = bridges[i].first; int v = bridges[i].second;
          //cout<<fa[u]<<' '<<fa[v]<<endl; 
          adj[fa[u]].push_back(fa[v]);
          adj[fa[v]].push_back(fa[u]);
     }
     scanf("%d",&q); 
     for(int i = 0; i < q; i++){
          int x,y ; scanf("%d%d",&x,&y); 
          dp[fa[x]]++;
          dp[fa[y]]--;
     } 
     for(int i = 1; i <= n; i++) if(!vis[i]) dfs_calc(i,0); 
     for(int i = 0; i < edges.size(); i++){
           int u = edges[i].first; int v = edges[i].second;
           if(fa[u] == fa[v]) cout<<'B'; 
           else{
                u = fa[u]; v = fa[v]; 
               //if(i == 14) cout<<ds[fa[u]]<<' '<<ds[fa[v]]<<endl; 
                if(ds[u] > ds[v]){
                      if(dp[u] == 0) cout<<'B';
                      else if(dp[u] > 0) cout<<'R'; 
                      else cout<<'L'; 
                }
                if(ds[u] < ds[v]){
                      if(dp[v] == 0) cout<<'B'; 
                      else if(dp[v] > 0) cout<<'L'; 
                      else cout<<'R'; 
                }
           }
     }
     return 0; 
}
//Test case: 
// 20 23
// 1 15
//   1 16
// 15 16
// 6 5
// 5 16
// 15 5
// 6 10
//18 20
//19 18
// 3 4
3 10
17 20
19 20
13 14
11 9
11 12
12 2
2 11
9 8
7 8
9 10
6 8
12 13
7
13 4
2 7
16 3
// 17 18
// 17 19
// 8 10
// 10 8
