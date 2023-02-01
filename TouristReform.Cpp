#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 5e5 + 5;
int up[21][N + 1],dp[N + 1],par[N + 1];
int a[N + 1];
int n,m,q;
vector<pair<int,int>>tadj[N + 1];
vector<int>adj[N + 1]; 
int trs,dsz,psz;
vector<pair<int,int>>edges; 
vector<pair<pair<int,int>,int>>bridges; 
int cnt; 
bool vis[N + 1],use[N + 1],brid[N + 1]; 
int st[N + 1],low[N + 1];
int comp[N + 1];
int fa[N + 1];
pair<int,int>ans[N + 1];
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
            dp[v] = dp[u] + 1; 
            dfs(v,u);
            low[u] = min(low[u] , low[v]);
            if(low[v] > a[u]) brid[x.second] = 1, bridges.push_back({{u,v},x.second}); 
            else ans[x.second] = {u,v}; 
        }
        else low[u] = min(a[v] , low[u]);
    }
}
void dfs_calc(int u,int p){
    vis[u] = 1; par[u] = p; 
    for(int i = 0; i < adj[u].size(); i++){
        auto v = adj[u][i]; 
        if(vis[v]) continue;
        dfs_calc(v,u); 
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
         int u = edges[i].first; int v = edges[i].second;
         if(brid[i]) continue; unite(u,v); 
         if(ans[i].first) continue; 
         if(dp[u] < dp[v]) swap(u,v);
         ans[i] = {u,v}; 
     }
     for(int i = 1; i <= n; i++) find(i);  
     for(int i = 0; i < bridges.size(); i++){
          int u = bridges[i].first.first; int v = bridges[i].first.second;
          adj[fa[u]].push_back(fa[v]);
          adj[fa[v]].push_back(fa[u]);
     }
     vector<pair<int,int>>comps; 
     for(int i = 1; i <= n; i++){
          if(use[fa[i]]) continue;
          use[fa[i]] = 1;
          comps.push_back({comp[fa[i]],fa[i]}); 
     }
     int res = INT_MAX; 
     sort(comps.rbegin(),comps.rend());
     for(int i = 0; i < comps.size(); i++){
           if(vis[comps[i].second]) continue;
           res = min(res, comps[i].first); 
           dfs_calc(comps[i].second, 0);
     }
     for(int i = 0; i < bridges.size(); i++){
           int u = bridges[i].first.first; int v = bridges[i].first.second;
           if(par[fa[u]] == fa[v]) ans[bridges[i].second] = {u,v};
           if(par[fa[v]] == fa[u]) ans[bridges[i].second] = {v,u}; 
     }
     cout<<res<<endl; 
     for(int i = 0; i < m; i++) cout<<ans[i].first<<' '<<ans[i].second<<endl; 
     return 0; 
}
