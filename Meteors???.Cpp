#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 6e5 + 100;
const int INF = 1e7 + 10; 
long long n,m,q,dsz,M;
int timer = 1;
vector<int>adj[N + 1];
int fa[N + 1], in[N + 1];
int up[22][N + 1],dp[N + 1],val[N + 1];
struct node{
     pair<int,int>mx = {-INF,0};
     pair<int,int>mn = {INF,0}; 
     int lzadd = -1; 
     pair<int,int> max = {-INF,0};
     pair<int,int> min = {INF,0}; 
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
void setup(int l = 1, int r = n,int p = 1){
     if(l == r){
          tree[p].mx = tree[p].mn = {in[l],l};
          return; 
     }
     int mid = (l + r) >> 1; 
     setup(l, mid, 2 * p);
     setup(mid + 1, r, 2 * p + 1);
     tree[p].mx = max(tree[2 * p].mx,tree[2 * p + 1].mx); 
     tree[p].mn = min(tree[2 * p].mn,tree[2 * p + 1].mn); 
}
void adjust(int p,int act){
     if(act == 1){
          tree[p].max = tree[p].mx;
          tree[p].min = tree[p].mn;
          tree[p].lzadd = act;
     }
     if(act == - 1){
          tree[p].max = {-INF,0};
          tree[p].min = {INF,0};
          tree[p].lzadd = act; 
     }
}
void push_down(int p){
      if(tree[p].lzadd == 1){
           adjust(2 * p, 1); 
           adjust(2 * p + 1, 1);
           tree[p].lzadd = 0; 
      }
      if(tree[p].lzadd == - 1){
           adjust(2 * p, -1); 
           adjust(2 * p + 1, -1);
           tree[p].lzadd = 0; 
      }
}
void activate(int act,int L, int R,int l = 1,int r = n, int p = 1){
     if(L > r or R < l) return;
     if(L <= l and r <= R){
          adjust(p,act); 
          return; 
     }
     int mid = (l + r) >> 1;
     push_down(p); 
     activate(act,L, R, l, mid, 2 * p);
     activate(act,L, R, mid + 1, r, 2 * p + 1);
     tree[p].max = max(tree[2 * p].max, tree[2 * p + 1].max);
     tree[p].min = min(tree[2 * p].min, tree[2 * p + 1].min); 
}
void dfs_calc(int u){
    in[u] = timer++; 
    for(int i = 1; i < 22 ; i++){
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
    for(int i = 0; i < 22 ; i++){
        if( (d >> i) & 1) a = up[i][a];
    }
    if(a == b) return a;
    for(int i = 21; i >= 0; i--){
         int tA = up[i][a]; int tB = up[i][b];
         if(tA != tB) {
            a = tA; b = tB;
         }
    } 
    return up[0][a];
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
      for(int i = M; i > 0; i--) if(!in[i]) dfs_calc(i);
      setup(); 
      for(int i = 0; i < q; i++){
           int t; scanf("%d",&t);
           if(t == 1){
                int l,r; scanf("%d%d",&l,&r);
                activate(1,l,r);
           }
           if(t == 2){
                int l,r; scanf("%d%d",&l,&r);
                activate(-1,l,r);
           }
           if(t == 3){
               int x; scanf("%d",&x);
               int pa = tree[1].max.second;
               int pb = tree[1].min.second;
               int anc = lca(pa,pb);
               anc = lca(anc,x); 
               if(!pa or !pb or !val[anc]){
                     printf("%d \n",-1); 
                     continue; 
               }
               printf("%d \n",val[anc]); 
           }
      }
}
