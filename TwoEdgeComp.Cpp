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
vector<int>components[N + 1]; 
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
            if(low[v] > a[u]) bridges.push_back({{u,v},x.second}); 
            else unite(u,v); 
        }
        else low[u] = min(a[v] , low[u]);
    }
}
int main(){
     scanf("%d%d",&n,&m);
     for(int i = 1; i <= n; i++) fa[i] = i, comp[i] = 1; 
     map<int,int>mp[N + 1]; 
     for(int i = 0; i < m; i++){
         int u,v; scanf("%d%d",&u,&v);
         ++u,++v; 
         mp[u][v]++; mp[v][u]++; 
         tadj[u].push_back({v,i});
         tadj[v].push_back({u,i}); 
         edges.push_back({u,v}); 
     }
     for(int i = 1; i <= n; i++){
          if(!a[i]) dfs(i,0); 
     }
     for(int i = 0; i < bridges.size(); i++){
          auto v = bridges[i].first;
          if(mp[v.first][v.second] == 1) continue;
          unite(v.first,v.second); 
     }
     for(int i = 1; i <= n; i++) find(i);
     int res = 0; 
     for(int i = 1; i <= n; i++){  
          if(!use[fa[i]]) res++, use[fa[i]] = 1; 
          components[fa[i]].push_back(i); 
     }
     cout<<res<<endl;
     for(int i = 1; i <= n; i++){
          if(components[i].size()){
            cout<<components[i].size()<<' ';
            for(int j = 0; j < components[i].size(); j++) cout<<components[i][j] - 1<<' ';
            cout<<endl; 
          }
     }
     return 0; 
}
