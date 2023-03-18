#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int sz = 4e5 + 1;
const int N = 2e5 + 10;
const int M = 1e6 + 10;
const int mod = (1 << 32);
long long n,m,k,q,x;
vector<pair<int,pii>>adj[N + 1];
int timer = 1;
vector<int>tadj[N + 1]; 
pair<int,int>pa[N + 1]; 
long long dp[N + 1]; 
long long ds[N + 1]; 
long long dep[N + 1];
long long up[23][N + 1]; 
long long trs[N + 1]; 
int in[N + 1],top[N + 1];
set<int>ans; 
int fa[N + 1]; 
bool vis[N + 1];
int chk[N + 1];
struct node{
    long long val = 0x3f3f3f3f;
    int lzadd = 0;
} tree[(N + 1) << 2];
// build shortest path tree 
int find(int n){
     if(fa[n] == n) return n;
     return fa[n] = find(fa[n]); 
}
void unite(int u,int v){
     u = find(u); v = find(v);
     if(u == v) return; 
     fa[v] = u; 
}
void dijsktra(int src){
      using T = pair<long long,int>;
      priority_queue<T,vector<T>,greater<T>>pq;
      pq.push({0,src}); 
      memset(dp,0x3f3f3f3f,sizeof(dp));
      dp[src] = 0; 
      while(pq.size()){
            int node; long long weight; 
            tie(weight,node) = pq.top();
            pq.pop();
            if(dp[node] != weight) continue; 
            for(int i = 0; i < adj[node].size(); i++){
                  int id = adj[node][i].first;
                  int v = adj[node][i].second.first;
                  int weightx = adj[node][i].second.second; 
                  if(dp[v] > dp[node] + weightx){
                       dp[v] = dp[node] + weightx;
                       pa[v] = {id,node};                       
                       pq.push({dp[v],v}); 
                  }
            }
      }
}
// Compute and push node from subtree
void push_down(int p){
     if(tree[p].lzadd > 0){
           ///if(2 * p == 248) cout<<p<<endl; 
           tree[p].lzadd = 0;
           tree[2 * p].lzadd = tree[2 * p + 1].lzadd = 1; 
           tree[2 * p].val = min(tree[2 * p].val, tree[p].val);
           tree[2 * p + 1].val = min(tree[2 * p + 1].val, tree[p].val);           
     }
     return;
}
void upd(int L,int R,long long val,int l = 1, int r = n,int p = 1){
      if(L > r or R < l) return;
      if(L <= l and r <= R){
          // if(val == 695 and r == 190) cout<<tree[p].val<<' '<<l<<' '<<in[25]<<' '<<p<<endl; 
           tree[p].val = min(tree[p].val, val);
           tree[p].lzadd = 1; 
           return; 
      } 
      push_down(p); 
      int mid = (l + r) >> 1; 
      upd(L,R,val,l,mid,2 * p);
      upd(L,R,val,mid + 1,r, 2 * p + 1);
      //tree[p].val = min(tree[2 * p + 1].val,tree[2 * p].val);
}
long long query(int L,int R,int l = 1, int r = n, int p = 1){
      if(L > r or R < l) return 0x3f3f3f3f;
      if(L <= l and r <= R) return tree[p].val;
      push_down(p);
      int mid = (l + r) >> 1; 
      return min(query(L,R,l,mid,2 * p),query(L,R,mid + 1,r,2 * p + 1));
}
long long dfs(int u,int p){
    trs[u] = 1;
    for(int i = 1; i < 23; i++){
          up[i][u] = up[i - 1][up[i - 1][u]]; 
    }
    for(int i = 0; i < tadj[u].size(); i++){
        int v = tadj[u][i]; 
        if(v == p) continue;
        dep[v] = dep[up[0][v] = u] + 1;
        trs[u] += dfs(v,u);
    } 
    return trs[u];
}
void dfs_hld(int u,int anc){
    in[u] = timer++;
    top[u] = anc;
    int hchi = 0;
    int hsize = 0;
    for(int i = 0; i < tadj[u].size(); i++){
        int v = tadj[u][i]; 
        if(v == up[0][u]) continue;
        if(hsize < trs[v]){
            hsize = trs[v];
            hchi = v;
        }
    }
    if(hchi == 0) return;
    dfs_hld(hchi,anc);
    for(int i = 0; i < tadj[u].size(); i++){
        int v = tadj[u][i]; 
        if(v == up[0][u] or v == hchi) continue;
        dfs_hld(v,v);
    }
}
void update(int x,int y,long long weight){
    while(top[x] != top[y]){
       if(dep[top[x]] < dep[top[y]]) swap(x,y);
       upd(in[top[x]], in[x],weight); 
       x = up[0][top[x]];
    }   
    if(dep[x] > dep[y]) swap(x,y);
    upd(in[x], in[y], weight); 
}
int jump(int x,int d){
     for(int i = 0; i < 23 ; i++){
        if( (d >> i) & 1) x = up[i][x];
    }
    return x;
}
int lca(int a, int b){
    if(dep[a] < dep[b]) swap(a,b);
    a = jump(a,dep[a] - dep[b]); 
    if(a == b) return a;
    for(int i = 22; i >= 0; i--){
         int tA = up[i][a]; int tB = up[i][b];
         if(tA != tB) {
            a = tA; b = tB;
         }
    } 
    return up[0][a];
}  
int main(){
     scanf("%d%d",&n,&m); 
     vector<pair<pii,pii>>edge;  
     for(int i = 1; i <= n; i++) fa[i] = i; 
     for(int i = 0; i < m; i++){
          int u,v,w; scanf("%d%d%d",&u,&v,&w);
          adj[u].push_back({i,{v,w}});
          adj[v].push_back({i,{u,w}});
          edge.push_back({{w,i},{u,v}}); 
     }
     dijsktra(1);   
     for(int i = 2; i <= n; i++){
          if(!pa[i].second) continue;
          int u = pa[i].second;
          int id = pa[i].first;
          unite(u,i); 
          vis[id] = 1;
          tadj[u].push_back(i);
          tadj[i].push_back(u);
     }
    // memset(ds,0x3f3f3f3f,sizeof(ds));   
     dfs(1,0);
     dfs_hld(1,0);   
     for(int i = 0; i < edge.size(); i++){ 
           int id = edge[i].first.second;
           if(vis[id]) continue; 
           int w = edge[i].first.first; 
           int u = edge[i].second.first; int v = edge[i].second.second; 
           int anc = lca(u,v);
           if(dep[u] > dep[v]) swap(u,v);
           if(u == anc){
                 int tov = jump(v,dep[v] - dep[u] - 1);
                 update(v,tov,dp[v] + w + dp[u]);
           }
           else{
                 int tov = jump(v,dep[v] - dep[anc] - 1);
                 int tou = jump(u,dep[u] - dep[anc] - 1);
                 update(u,tou,dp[u] + dp[v] + w);
                 update(v,tov,dp[v] + dp[u] + w); 
           }
     } 
     for(int i = 2; i <= n; i++){
         long long val = query(in[i],in[i]); 
         printf("%lld\n", (val >= 0x3f3f3f3f) ? -1 : val - dp[i]); 
     }
     return 0; 
}
