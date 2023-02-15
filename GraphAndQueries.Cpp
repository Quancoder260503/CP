#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 100;
long long n,m,q,dsz;
int timer = 1;
vector<int>adj[N + 1];
int a[N + 1],low[N + 1]; 
pair<int,int>edges[N + 1];
pair<int,int>queries[N + 1];
int fa[N + 1],in[N + 1],out[N + 1];
int pa[N + 1];
bool del[N + 1];
pair<int,int>tree[(N + 1) << 2]; 
void dfs(int u,int p){
    in[u] = timer++; 
    for(int i = 0; i < adj[u].size(); i++){
          int v = adj[u][i];
          if(v == p) continue; 
          dfs(v,u); 
    }
    out[u] = timer - 1; 
}
int find(int u){
     if(u == fa[u]) return u;
     return fa[u] = find(fa[u]); 
}
void unite(int u,int v){
     u = find(u); v = find(v);
     if(u == v) return;
     ++n; 
     fa[n] = fa[u] = fa[v] = n;
     adj[n].push_back(u);
     if(u != v) adj[n].push_back(v);
}
void update(int val,int L, int R, int l = 1, int r = n,int p = 1){
    if(L > r or R < l) return; 
    if(l == r){
        tree[p] = {val,r};
        return; 
    }
    int mid = (l + r) >> 1; 
    update(val,L,R,l,mid,2 * p);
    update(val,L,R,mid + 1,r, 2 * p + 1);
    tree[p] = max(tree[2 * p],tree[2 * p + 1]); 
}
pair<int,int>query(int L, int R, int l = 1, int r = n,int p = 1){
    if(L > r or R < l) return {0,0}; 
    if(L <= l and r <= R) return tree[p]; 
    int mid = (l + r) >> 1; 
    pair<int,int> left = query(L,R,l,mid,2 * p);
    pair<int,int> right = query(L,R,mid + 1,r, 2 * p + 1);
    return max(left,right); 
}
int main(){
      scanf("%d%d%d",&n,&m,&q);
      for(int i = 1; i <= n; i++) scanf("%d",&a[i]); 
      for(int i = 1; i <= m; i++){
           scanf("%d%d",&edges[i].first,&edges[i].second); 
      }
      for(int i = 1; i <= q; i++){
           scanf("%d%d",&queries[i].first,&queries[i].second); 
           if(queries[i].first == 2) del[queries[i].second] = 1;  
      }
      for(int i = 1; i <= n; i++) fa[i] = i; 
      for(int i = 1; i <= m; i++){
           if(del[i]) continue; 
          // cout<<edges[i].first<<' '<<edges[i].second<<endl; 
           unite(edges[i].first,edges[i].second); 
      }
      for(int i = q; i > 0; i--){
            if(queries[i].first == 2){
                 int id = queries[i].second;
                 unite(edges[id].first,edges[id].second); 
            } 
            else pa[i] = find(queries[i].second); 
      }
      for(int i = n; i > 0; i--){
           if(!in[i]) dfs(i,0);
      }
     // for(int i = 1; i <= n; i++) cout<<in[i]<<' ';
      for(int i = 1; i <= n; i++) update(a[i],in[i],in[i]); 
      for(int i = 1; i <= q; i++){
          if(queries[i].first == 2) continue;
          int u = pa[i]; 
          //cout<<u<<' '<<in[u]<<' '<<out[u]<<endl;
          pair<int,int>ans = query(in[u],out[u]);
          printf("%d \n",ans.first); 
          update(0,ans.second,ans.second); 
      }
}
