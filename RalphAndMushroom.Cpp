#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 5;
const int M = 1e6 + 5;
const int mod = (1 << 32); 
long long n,m,k,q,bridges,comp;
vector<int>adj[N + 1];
vector<pair<int,long long>>tadj[N + 1];
vector<pair<pair<int,int>,long long>>edges;
vector<int>S;
int up[21][N + 1];
int in[N + 1];
long long a[N + 1],val[N + 1];
int out[N + 1],low[N + 1]; 
bool vis[N + 1];
long long dp[N + 1];
int timer = 1; 
int fa[N + 1]; 
bool f(long long mid,long long val){
    return (val >= (long long) mid * (mid + 1) / 2); 
}
long long search(long long val){
     long long r = 1e9 + 1; 
     long long l = 0; 
     while (l < r){
         int mid = (r - l + 1) / 2 + l;
         if(f(mid,val)) l = mid; 
         else r = mid - 1; 
     }
     return l; 
}
void dfs(int u){
     in[u] = low[u] = timer++;
     vis[u] = 1;
     S.push_back(u);
     for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(!in[v]) dfs(v);
            if (vis[v]) low[u] = min(low[u],low[v]);
     }
     if(in[u] == low[u]){
        long long sum = 0; 
        while(1){
             int v = S.back();
             S.pop_back();
             fa[v] = u; 
             vis[v] = 0; 
             if(u == v) break; 
        }   
    }
}
long long calc(int u){
    if(dp[u]) return dp[u];
    dp[u] = val[u]; 
    for(int i = 0; i < tadj[u].size(); i++){
         auto v = tadj[u][i]; 
         dp[u] = max(dp[u], v.second + calc(v.first) + val[u]);
    }
    return dp[u];
}
int main(){
     scanf("%d%d",&n,&m);
     for(int i = 0; i < m; i++){
          int u,v; long long w; scanf("%d%d%lld",&u,&v,&w);
          edges.push_back({{u,v},w});
          adj[u].push_back(v);
     }
     for(int i = 1; i <= n; i++) if(!in[i]) dfs(i);
     memset(vis,0,sizeof(vis));
     for(int i = 0; i < edges.size(); i++){
          auto x = edges[i].first;
          long long w = edges[i].second; 
          int u = x.first; int v = x.second;
          if(fa[u] == fa[v]){
               long long k = search(w);
               w = (long long) (k + 1) * w - (long long) k * (k + 1) * (k + 2) / 6;
               val[fa[u]] += w;
          }
          else tadj[fa[u]].push_back({fa[v],w}); 
     }
     scanf("%d",&q);
     long long ans = calc(fa[q]);
     cout<<ans<<endl; 
}
