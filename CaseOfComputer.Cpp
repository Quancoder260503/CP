#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 5e5 + 5;
int dp[N + 1],ds[N + 1],up[21][N + 1];
int a[N + 1];
int n,m,q,timer;
vector<pair<int,int>>tadj[N + 1];
vector<int>adj[N + 1];
int dsz,psz;
vector<pair<int,int>>edges; 
vector<pair<int,int>>bridges; 
vector<pair<int,int>>queries;
bool brid[N + 1],vis[N + 1]; 
int comps[N + 1];
int low[N + 1],trs[N + 1];
int comp[N + 1];
int fa[N + 1];
int deg[N + 1][2]; 
long long dfs(int u,int p){
    trs[u] = 1;
    for(int i = 1; i < 21 ; i++){
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for(int i = 0;  i < adj[u].size(); i++){
        int v = adj[u][i]; 
        if(v == p) continue;
        ds[v] = ds[up[0][v] = u] + 1;
        trs[u] += dfs(v,u);
    } 
    return trs[u];
}
int jump(int x,int d){
    for(int i = 0; i < 21 ; i++){
        if( (d >> i) & 1) x = up[i][x];
    }
    return x; 
}
int lca(int a, int b){
    if(ds[a] < ds[b]) swap(a,b);
    a = jump(a, ds[a] - ds[b]);
    if(a == b) return a;
    for(int i = 20; i >= 0; i--){
         int tA = up[i][a]; int tB = up[i][b];
         if(tA != tB) {
            a = tA; b = tB;
         }
    } 
    return up[0][a];
}  
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
void dfs1(int u,int p){
    a[u] = low[u] = ++dsz;
    comps[u] = timer; 
    for(int i = 0; i < tadj[u].size(); i++){
        auto x = tadj[u][i];
        int v = x.first;
        if(v == p) continue;
        if(!a[v]){
            dfs1(v,u);
            low[u] = min(low[u] , low[v]);
            if(low[v] > a[u]) brid[x.second] = 1, bridges.push_back({u,v}); 
        }
        else low[u] = min(a[v] , low[u]);
    }
}
void dfs2(int u){
    vis[u] = 1;
    for(int i = 0; i < adj[u].size();i++){
        int v = adj[u][i];
        if(vis[v]) continue;
        dfs2(v);
        deg[u][0] += deg[v][0];
        deg[u][1] += deg[v][1]; 
    }
}
int main(){
     scanf("%d%d%d",&n,&m,&q);
     for(int i = 1; i <= n; i++) fa[i] = i, comp[i] = 1; 
     map<int,int>mp[N + 1];
     for(int i = 0; i < m; i++){
         int u,v; scanf("%d%d",&u,&v);
         mp[u][v]++; mp[v][u]++; 
         tadj[u].push_back({v,i});
         tadj[v].push_back({u,i}); 
         edges.push_back({u,v}); 
     }
     for(int i = 1; i <= n; i++){
          if(!a[i]){
              timer++; 
              dfs1(i,0); 
          }
     }
     for(int i = 0; i < edges.size(); i++){
          if(brid[i]) continue;
         // cout<<edges[i].first<<' '<<edges[i].second<<endl; 
          unite(edges[i].first,edges[i].second); 
     }
     for(int i = 1; i <= n; i++) find(i); 
     for(int i = 0; i < bridges.size(); i++){
          int u = bridges[i].first; int v = bridges[i].second;
          ///cout<<u<<' '<<v<<endl; 
          if(mp[u][v] > 1 or mp[v][u] > 1) continue; 
          adj[fa[u]].push_back(fa[v]);
          adj[fa[v]].push_back(fa[u]);
     }
     for(int i =  1; i <= n; i++){
           if(!trs[i]) dfs(i,0); 
     }
     ///cout<<fa[1]<<' '<<fa[3]<<endl; 
     for(int i = 0; i < q; i++){
          int x,y ; scanf("%d%d",&x,&y); 
          if(comps[x] != comps[y]){
                cout<<"No"<<endl;
                return 0; 
          }
          if(fa[x] == fa[y]) continue;
          x = fa[x]; y = fa[y];
          int anc = lca(x,y);
          deg[anc][0]--; deg[anc][1]--;
          deg[x][0]++; deg[y][1]++;
     } 
     for(int i = 1; i <= n; i++) if(!vis[i]) dfs2(i); 
     for(int i = 1; i <= n; i++){
          if(deg[i][1] && deg[i][0]){
               cout<<"No"<<endl;
               return 0; 
          }
     }
     cout<<"Yes"<<endl; 
     return 0; 
}
