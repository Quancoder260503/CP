#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 100;
const int INF = 1e7 + 10; 
long long n,m,q,dsz,E;
bool invalid; 
int timer = 1;
vector<int>adj[N + 1];
int fa[N + 1];
bool cyc[N + 1]; 
int up[23][N + 1],dp[N + 1],val[N + 1];
int lf[N + 1],ri[N + 1]; 
int in[N + 1],to[N + 1];
int deg[N + 1],deg1[N + 1],deg3[N + 1];
vector<pair<int,pair<int,int>>>edges; 
int find(int u){
     if(u == fa[u]) return u;
     return fa[u] = find(fa[u]); 
}
void dfs_calc(int u){
    if(!val[u]) val[u] = val[up[0][u]]; 
    for(int i = 1; i < 23 ; i++){
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i]; 
        if(v == up[0][u]) continue;
        dp[v] = dp[up[0][v] = u] + 1;      
        dfs_calc(v);
    }
}
int lca(int a, int b){
    if(dp[a] < dp[b]) swap(a,b);
    int d = dp[a] - dp[b];
    for(int i = 0; i < 23 ; i++){
        if( (d >> i) & 1) a = up[i][a];
    }
    if(a == b) return a;
    for(int i = 22; i >= 0; i--){
         int tA = up[i][a]; int tB = up[i][b];
         if(tA != tB) {
            //cout<<tA<<' '<<tB<<' '<<i<<endl; 
            a = tA; b = tB;
         }
    } 
  //  cout<<a<<' '<<b<<endl; 
    return up[0][a];
} 
void init(int N, int M,std::vector<int> U, std::vector<int> V, std::vector<int> W){
         for(int i = 0; i < M; i++){ 
              U[i]++; V[i]++; 
              edges.push_back({W[i],{U[i],V[i]}});
             // cout<<U[i]<<' '<<V[i]<<' '<<W[i]<<endl; 
         }
         sort(edges.begin(),edges.end());
         E = N;
         for(int i = 0; i <= N; i++) fa[i] = i;
         for(int i = 0; i < M; i++){
              int u = edges[i].second.first; int v = edges[i].second.second;  
              int x = find(u); int y = find(v);
              deg[u]++; deg[v]++; 
              if(deg[u] == 2) deg1[x]--;  if(deg[v] == 2) deg1[y]--;
              if(deg[u] == 1) deg1[x]++;  if(deg[v] == 1) deg1[y]++;
              if(deg[u] == 3) deg3[x]++;  if(deg[v] == 3) deg3[y]++; 
              E++; 
              if(x == y){
                   fa[x] = fa[E] = E;
                   adj[E].push_back(x);
                   deg1[E] += deg1[x];
                   deg3[E] += deg3[y]; 
              }
              else{
                   if(x < y) swap(x,y); 
                 //  if(i == 1) cout<<deg1[x]<<' '<<deg1[y]<<endl; 
                   fa[x] = fa[y] = fa[E] = E; 
                   deg1[E] += deg1[x] + deg1[y];
                   deg3[E] += deg3[x] + deg3[y]; 
                   adj[E].push_back(x);
                   adj[E].push_back(y); 
              }
              if(!deg1[E] or deg3[E]) val[E] = edges[i].first; 
         }
         //cout<<up[0][9]<<endl; 
         dfs_calc(E);
}
int getMinimumFuelCapacity(int X, int Y){
      int anc = lca(++X,++Y);
   //   cout<<anc<<endl;
      return val[anc] == 0 ? -1 : val[anc];     
}
int main(){ 
     init(5, 6, {0, 0, 1, 1, 1, 2}, {1, 2, 2, 3, 4, 3}, {4, 4, 1, 2, 10, 3});
     int ans = getMinimumFuelCapacity(4,2);
     printf("%d",ans);
}
