#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 6e5 + 100;
const int INF = 1e7 + 10; 
long long n,m,q,dsz,M;
int timer = 1;
vector<int>adj[N];
int fa[N];
int up[23][N],dp[N],val[N];
struct node{
     int lc = INF; int lc0; 
     int lzadd = -1; 
} tree[(N + 1) << 1]; 
int find(int u){
     if(u == fa[u]) return u;
     return fa[u] = find(fa[u]); 
}
void unite(int u,int v,int w){
     u = find(u); v = find(v);
     if(u == v) return;
     ++M; 
     fa[M] = fa[u] = fa[v] = M;
     val[M] = w;
     adj[M].push_back(u);
     if(u != v) adj[M].push_back(v);
}
void dfs_calc(int u){
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
    if(a == INF) return b;
    if(b == INF) return a;
    if(dp[a] < dp[b]) swap(a,b);
    int d = dp[a] - dp[b];
    for(int i = 0; i < 23 ; i++){
        if( (d >> i) & 1) a = up[i][a];
    }
    if(a == b) return a;
    for(int i = 22; i >= 0; i--){
         int tA = up[i][a]; int tB = up[i][b];
         if(tA != tB) {
            a = tA; b = tB;
         }
    } 
    return up[0][a];
} 
void setup(int l = 1, int r = n,int p = 1){
     if(l == r){
          tree[p].lc0 = l;
          return; 
     }
     int mid = (l + r) >> 1; 
     setup(l, mid, 2 * p);
     setup(mid + 1, r, 2 * p + 1);
     tree[p].lc0 = lca(tree[2 * p].lc0, tree[2 * p + 1].lc0); 
}
void push_down(int p){
      if(tree[p].lzadd == 1){
          tree[2 * p].lc = tree[2 * p].lc0;
          tree[2 * p + 1].lc = tree[2 * p + 1].lc0;
          tree[2 * p].lzadd = tree[2 * p + 1].lzadd = 1; 
          tree[p].lzadd = 0; 
      }
      if(tree[p].lzadd == - 1){
           tree[2 * p].lc = tree[2 * p + 1].lc = INF; 
           tree[2 * p].lzadd = tree[2 * p + 1].lzadd = -1; 
           tree[p].lzadd = 0; 
      }
}
void activate(bool act,int L, int R,int l = 1,int r = n, int p = 1){
     if(L > r or R < l) return;
     if(L <= l and r <= R){
          if(act){
            tree[p].lc = tree[p].lc0; 
            tree[p].lzadd = 1; 
          }
          else{
            tree[p].lc = INF;  
            tree[p].lzadd = -1; 
          }
          return; 
     }
     int mid = (l + r) >> 1;
     push_down(p); 
     activate(act,L, R, l, mid, 2 * p);
     activate(act,L, R, mid + 1, r, 2 * p + 1);
     tree[p].lc = lca(tree[2 * p].lc, tree[2 * p + 1].lc); 
}
int main(){
      scanf("%d%d",&n,&q);
      M = n; 
      vector<pair<int,pair<int,int>>>edges; 
      for(int i = 1; i <= n; i++) fa[i] = i; 
      for(int i = 0; i < n - 1; i++){
            int u,v,w; scanf("%d%d%d",&u,&v,&w);
            edges.push_back({w,{u,v}}); 
      }
      sort(edges.begin(),edges.end()); 
      for(int i = 0; i < edges.size(); i++){
           unite(edges[i].second.first,edges[i].second.second,edges[i].first); 
      }
      dfs_calc(M);
      setup(); 
      for(int i = 0; i < q; i++){
           int t; scanf("%d",&t);
           if(t == 1){
                int l,r; scanf("%d%d",&l,&r);
                activate(1,l,r);
           }
           if(t == 2){
                int l,r; scanf("%d%d",&l,&r);
                activate(0,l,r);
           }
           if(t == 3){
               int x; scanf("%d",&x);
               int pa = lca(tree[1].lc,x);
               if(tree[1].lc == INF or !val[pa]){
                       printf("%d \n",-1); 
                      continue; 
               }
                printf("%d \n",val[pa]); 
           }
      }
}
