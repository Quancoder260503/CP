#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 6e5 + 100;
const int INF = 1e7 + 10; 
long long n,m,q,dsz,M;
int timer = 1;
vector<int>adj[N + 1];
vector<int>adj1[N + 1]; 
int fa[N], up[23][N + 1], up1[23][N + 1]; 
int fa1[N], dp[N + 1], dp1[N + 1]; 
int in[N + 1],in1[N + 1],out[N + 1],out1[N + 1];
int val[N + 1],val1[N + 1], rot[N + 1];
int ord[N + 1]; 
struct edge{
     int u,v; 
} edges[N + 1];
struct query{
     int l,r;
} queries[N + 1]; 
struct tree{
     int l,r,val; 
} tree[N * 30]; 
int find(int u){
      if(u == fa[u]) return u;
      return fa[u] = find(fa[u]); 
}
int find1(int u){
      if(u == fa1[u]) return u;
      return fa1[u] = find1(fa1[u]); 
}
void unite_min(int u,int v){
       u = find(u); v = find(v);
       if(u == v) return;
       ++M; 
       fa[M] = fa[u] = fa[v] = M;
       val[M] = min(val[u],val[v]);
       adj[M].push_back(u);
       if(u != v) adj[M].push_back(v);
}
void unite_max(int u,int v){
       u = find1(u); v = find1(v);
       if(u == v) return;
       ++M; 
       fa1[M] = fa1[u] = fa1[v] = M;
       val1[M] = max(val1[u],val1[v]);
       adj1[M].push_back(u);
       if(u != v) adj1[M].push_back(v);
}
void dfs_calc(int u){
    in[u] = timer++; 
    for(int i = 1; i < 23 ; i++){
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i]; 
        if(v == up[0][u]) continue;
        dp[v] = dp[up[0][v] = u] + 1;
        dfs_calc(v);
    }
    out[u] = timer - 1;
}
void dfs_calc1(int u){
    in1[u] = timer++; 
    for(int i = 1; i < 23 ; i++){
        up1[i][u] = up1[i - 1][up1[i - 1][u]];
    }
    for(int i = 0; i < adj1[u].size(); i++){
        int v = adj1[u][i]; 
        if(v == up1[0][u]) continue;
        dp1[v] = dp1[up1[0][v] = u] + 1;
        dfs_calc1(v);
    }
    out1[u] = timer - 1;
}
bool cmp(edge &a, edge &b){
     return min(a.u,a.v) > min(b.u,b.v); 
}
bool cmp1(edge &a, edge &b){
     return max(a.u,a.v) < max(b.u,b.v); 
}
void update(int &cur,int pre,int value,int pos,int l, int r){
     cur = timer++;
     tree[cur].l = tree[pre].l; tree[cur].r = tree[pre].r;
     tree[cur].val = value + tree[pre].val; 
     if(l == r) return;
     int mid = (l + r) >> 1; 
     if(pos > mid) update(tree[cur].r, tree[pre].r,value,pos,mid + 1,r); 
     else update(tree[cur].l, tree[pre].l,value,pos,l,mid); 
}
long long query(int roota, int rootb ,int lb, int rb, int l,int r){
     if(l == lb and  rb == r) return tree[roota].val - tree[rootb].val;
     int mid = (l + r) >> 1; 
     if(mid >= rb) return query(tree[roota].l,tree[rootb].l,lb,rb,l,mid);
     if(mid + 1 <= lb) return query(tree[roota].r,tree[rootb].r,lb,rb,mid + 1,r); 
     long long f = query(tree[roota].l,tree[rootb].l,lb,mid,l,mid);
     long long s = query(tree[roota].r,tree[rootb].r,mid + 1,rb,mid + 1,r); 
     return f + s; 
}
vector<int> check_validity(int N, vector<int> X,vector<int> Y,vector<int> S,vector<int> E,vector<int> L,vector<int> R){
      int Q = L.size(); int K = X.size(); 
      for(int i = 1; i <= N; i++) fa[i] = val[i] = i;
      for(int i = 1; i <= N; i++) fa1[i] = val1[i] = i; 
      for(int i = 0; i < K; i++){
           edges[i].u = ++X[i]; edges[i].v = ++Y[i];         
      }
      sort(edges,edges + K,cmp); 
      M = N; 
      for(int i = 0; i < K; i++) unite_min(edges[i].u,edges[i].v);
      dfs_calc(M); 
      M = N; timer = 1;  
      sort(edges,edges + K,cmp1); 
      for(int i = 0; i < K; i++) unite_max(edges[i].u,edges[i].v); 
      dfs_calc1(M);
      timer = 1;
      vector<int>res;
      for(int i = 1; i <= N; i++) ord[in[i]] = in1[i];
      for(int i = 1; i <= M; i++){
           update(rot[i],rot[i - 1],1, ord[i] ,1 , M);
      }
      for(int i = 0; i < Q; i++){
            int l = ++L[i]; int r = ++R[i]; int u = ++S[i]; int v = ++E[i];
            if(u < l or v > r){
                 res.push_back(0);
                 continue;
            }
            for(int j = 22; j >= 0; j--){
                 if(up[j][u] > 0  and val[up[j][u]] >= l){
                       u = up[j][u];
                 }
            }
            for(int j = 22; j >= 0; j--){
                 if(up1[j][v] > 0 and val1[up1[j][v]] <= r){
                      v = up1[j][v];
                 }
            }
            if(query(rot[out[u]],rot[in[u] - 1],in1[v],out1[v], 1 , M)) res.push_back(1);
            else res.push_back(0); 
      }
      return res;
}
