#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> info; 
const int N = 5e5 + 5;
const int mod = 1e9 + 7; 
int a[N + 1];
int n,m,q;
long long tot;
set<int>adj[N + 1];
int fa[N + 1];
set<int>ver; 
struct dsu{
   int fa[N + 1];
   void init(){
        for(int i = 1; i <= n; i++) fa[i] = i; 
   }
   int find(int u){
     if(u == fa[u]) return u;
     return fa[u] = find(fa[u]);
   }
   bool unite(int u,int v){
     u = find(u); v = find(v);
     if(u == v) return 0;
     fa[u] = v;
     return 1;
   }
} dsu1,dsu2; 
void bfs(int i){
    if(!ver.count(i)) return;
    ver.erase(i);
    queue<long long>q;
    q.push(i);
    while(q.size()){
        int t = q.front();
        q.pop();
        vector<long long>add;
        for(auto it = ver.begin(); it != ver.end(); it++){ 
             if(!adj[t].count(*it)) add.push_back(*it);
        }
        for(int j = 0; j < add.size(); j++){
             q.push(add[j]);
             if(dsu1.unite(i,add[j])) tot--;
             ver.erase(add[j]);
        }
    } 
    return; 
}
int main(){
      scanf("%d%d",&n,&m);
      dsu1.init(); dsu2.init(); 
      vector<pair<int,pair<int,int>>>edge;
      int xorsum = 0; 
      for(int i = 1; i <= m; i++){
           int u,v,w;
           scanf("%d%d%d",&u,&v,&w);
           adj[u].insert(v);
           adj[v].insert(u);
           xorsum = xorsum xor w;
           edge.push_back({w,{u,v}}); 
      }
      tot = (1ll) * n * (n - 1) / 2;
      for(int i = 1; i <= n; i++) ver.insert(i); 
      for(int i = 1; i <= n; i++) bfs(i); 
      sort(edge.begin(),edge.end());
      long long ans = 0;
      if(tot > m ){
           xorsum = 0; 
      }
      for(int i = 0; i < edge.size(); i++){
           int u = edge[i].second.first; 
           int v = edge[i].second.second; 
           int w = edge[i].first;
           if(dsu1.find(u) != dsu1.find(v)){
                 ans += w;
                 dsu1.unite(u,v); 
                 dsu2.unite(u,v); 
           }
           else if(dsu2.find(u) != dsu2.find(v)){
                 xorsum = min(xorsum,w);  
           }
      }
      printf("%lld\n", ans + xorsum); 
      return 0; 
}
