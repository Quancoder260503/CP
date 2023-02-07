#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 5e5 + 5;
int up[21][N + 1];
int dp[N + 1];
int a[N + 1];
int n,m,q,timer,cnt;
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
int trs,dsz,psz;
long long ans = 0; 
vector<pair<int,int>>bridges; 
bool vis[N + 1]; 
int comp[N + 1]; 
long long compsize[N + 1];
int st[N + 1],low[N + 1];
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
    cnt++; 
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
void dfs_calc(int u,int p){
    vis[u] = 1;
    dp[u] = comp[fa[u]]; 
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i]; 
        if(vis[v]) continue;
        dfs_calc(v,u);
        dp[u] += dp[v]; 
    }
    if(p) ans += (long long) (n - dp[u]) * dp[u] - 1; 
} 
int main(){
     scanf("%d%d",&n,&m); 
     for(int i = 1; i <= n; i++) fa[i] = i,comp[i] = 1; 
     for(int i = 0; i < m; i++){
         int u,v; scanf("%d%d",&u,&v);
         tadj[u].push_back(v);
         tadj[v].push_back(u); 
     }
     for(int i = 1; i <= n; i++){
         if(!a[i]){
              ++timer;
              cnt = 0; 
              dfs(i,0);
              compsize[timer] = cnt;  
         }
     }
     for(int i = 1; i <= n; i++) find(i); 
     if(timer == 2){
           long long val = compsize[1] * compsize[2]; 
           ans += (long long) (m - bridges.size()) * val; 
     }
     else if(timer == 1){
           for(int i = 0; i < bridges.size(); i++){
              int u = bridges[i].first;
              int v = bridges[i].second;
              adj[fa[u]].push_back(fa[v]);
              adj[fa[v]].push_back(fa[u]); 
           }
           for(int i = 1; i <= n; i++){
                if(!vis[i] and fa[i] == i){
                    dfs_calc(i,0); 
                }
           }
           long long val = (long long) n * (n - 1) / 2 - m;
           ans += (long long) (m - bridges.size()) * val;
     }
     cout<<ans<<endl; 
}
