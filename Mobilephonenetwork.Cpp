#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 5e5 + 1;
const int N = 5e5 + 1;
const long long INF = 1e16 + 5;
const int mod = 1e9 + 7; 
long long n,m,k,q,b,c,d;
typedef pair<long long,pair<long long,bool>>queries;
vector<pair<long long,long long>>adj[N + 1];
long long a[N + 1];
long long dp[31][N + 1];
long long depth[N + 1];
int up[31][N + 1];
int comp[N + 1];
int fa[N + 1];
bool use[N + 1];
int find(int u){
     if(u == fa[u]) return u;
     return fa[u] = find(fa[u]);
}
void unite(int u,int v){
     u = find(u); v = find(v);
     if(u == v) return;
     if(comp[u] > comp[v]) swap(u,v);
     fa[u] = v;
     comp[v] += comp[u];
}
long long jump(int x,int d){
    for(int i = 0; i < 31 ; i++){
        if( (d >> i) & 1) x = up[i][x];
    } 
    return x;
}
void dfs(int u){
     for(int i = 1;i < 31; i++){
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for(int i = 0; i < adj[u].size(); i++){
        auto v = adj[u][i];
        if(v.first == up[0][u]) continue;
        depth[v.first] = depth[up[0][v.first] = u] + 1;
        use[v.first] = v.second; 
        dfs(v.first);
    } 
}
int lca(int a, int b){
    if(depth[a] < depth[b]) swap(a,b);
    a = jump(a,depth[a] - depth[b]);
    if(a == b) return a;
    for(int i = 30; i >= 0; i--){
         int tA = up[i][a]; int tB = up[i][b];
         if(tA != tB) a = tA, b = tB;
    } 
    return up[0][a];
}
void valjump(int x,int d,long long w){
     for(int i = 0; i < 31; i++){
          if((d >> i) & 1){ 
               dp[i][x] = min(dp[i][x], w); 
               x = up[i][x];
          }
     }
}
int main(){
    scanf("%d%d%d",&n,&k,&m);
    for(int i = 1; i <= n; i++) fa[i] = i; 
    for(int i = 0; i < k; i++){
         int u,v; scanf("%d%d",&u,&v);
         adj[u].push_back({v,1});
         adj[v].push_back({u,1});
         unite(u,v); 
    }
    vector<pair<long long,pair<long long,long long>>>redges;
    long long ans = 0;
    for(int i = 0; i < m; i++){
         long long u,v,w; scanf("%lld%lld%lld",&u,&v,&w);
         if(find(u) == find(v)) redges.push_back({w,{u,v}});
         else{
             unite(u,v);
             adj[u].push_back({v,0});
             adj[v].push_back({u,0});
         }
    }
    for(int i = 0; i < 31; i++){
        for(int j = 1; j <= n; j++){
            dp[i][j] = INF;
        }
    }
    dfs(1);
    for(int i = 0; i < redges.size(); i++){
          auto v = redges[i];  
          int x = v.second.first; int y = v.second.second;
          int anc = lca(x,y);
          valjump(x,depth[x] - depth[anc],v.first);
          valjump(y,depth[y] - depth[anc],v.first);
    }
    for(int i = 30; i > 0; i--){
         for(int j = 1 ; j <= n; j++){
              dp[i - 1][up[i - 1][j]] = min(dp[i - 1][up[i - 1][j]],dp[i][j]);
              dp[i - 1][j] = min(dp[i - 1][j],dp[i][j]); 
         }
    }
    for(int i = 1; i <= n; i++){
        if(use[i]){ 
            if(dp[0][i] >= INF){
                  cout<<-1<<endl;
                  return 0;
            }
            ans += dp[0][i]; 
        }
    }
    printf("%lld",ans);
}
