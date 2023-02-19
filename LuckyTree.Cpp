#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 100;
const int INF = 1e7 + 10; 
long long n,m,q,dsz,M,res;
int timer = 1;
vector<int>adj[N + 1];
int fa[N + 1], comp[N + 1];
bool vis[N + 1];
int up[22][N + 1],dp[N + 1],val[N + 1];
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
    vis[u] = 1;
    long long sqr = 0; 
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(v == p) continue; 
        dfs(v,u);
    }
    res += (long long) (n - comp[u] - 1) * (n - comp[u]) * comp[u];
}
int main(){
      scanf("%d",&n);
      vector<pair<int,int>>edges;
      for(int i = 1; i <= n; i++) fa[i] = i, comp[i] = 1; 
      for(int i = 0; i < n - 1; i++){
           int u,v; string s;
           cin>> u >> v >> s; 
           bool exist = 1;
           for(int j = 0; j < s.length(); j++){
                if(s[j] == ' ') break;
                if(s[j] == '4') continue;
                if(s[j] == '7') continue;
                exist = 0;
                break; 
           }
           if(exist) edges.push_back({u,v});
           else unite(u,v); 
      }
      for(int i = 0; i < edges.size(); i++){
           int u = edges[i].first; int v = edges[i].second;
           u = find(u); v = find(v); 
           adj[u].push_back(v);
           adj[v].push_back(u); 
      }
      for(int i = 1; i <= n; i++) if(!vis[i] and fa[i] == i) dfs(i,0);
      printf("%lld",res); 
}
