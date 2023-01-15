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
vector<pair<long long,pair<int,int>>>edges;
vector<pair<long long,pair<int,int>>>krus;
vector<pair<long long,long long>>adj[N + 1];
long long a[N + 1];
long long dp[N + 1];
int up[31][N + 1];
int comp[N + 1];
int fa[N + 1];
int pa[N + 1]; 
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
void dijsktra(vector<int>&portals){
     using T = pair<long long,int>;
     priority_queue<T,vector<T>,greater<T>>pq;    
     memset(dp,INF,sizeof(dp));
     for(int i = 0; i < portals.size();i++){
          pq.push({0,portals[i]});
          pa[portals[i]] = portals[i];
          dp[portals[i]] = 0; 
     }
     while(pq.size()){
          long long w; int u;
          tie(w,u) = pq.top();
          pq.pop();
          if(dp[u] != w) continue; 
          for(int i = 0; i < adj[u].size(); i++){
               auto v = adj[u][i]; 
               if(dp[v.first] > dp[u] + v.second){
                     dp[v.first] = dp[u] + v.second;
                     pa[v.first] = pa[u];
                     pq.push({dp[v.first],v.first}); 
               }
          }
     }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i = 0; i < m; i++){
         int u,v; long long w; scanf("%d%d%lld",&u,&v,&w);
         adj[u].push_back({v,w});
         adj[v].push_back({u,w});
         edges.push_back({w,{u,v}}); 
    }
    scanf("%d",&k);
    vector<int>portals;
    bool on = false;
    for(int i = 0; i < k; i++){
         int x; scanf("%d",&x);
         if(x == 1) on = true;
         portals.push_back(x);
    }
    dijsktra(portals); 
    for(int i = 0; i < m; i++){
         int u = edges[i].second.first; int v = edges[i].second.second;
         long long weight = edges[i].first;
         if(pa[v] != u and pa[u] != v){
             weight = weight +  dp[u]; 
             weight = weight +  dp[v]; 
         }
         ///cout<<weight<<' '<<u<<' '<<v<<endl; 
         krus.push_back({weight,{u,v}});
    }
   //for(int i = 1; i <= n; i++) cout<<dp[i]<<' ';
    sort(krus.begin(),krus.end()); 
    long long ans = 0;
    for(int i = 1; i <= n; i++) fa[i] = i;
    for(int i = 0; i < krus.size(); i++){
         int u = pa[krus[i].second.first];
         int v = pa[krus[i].second.second];
         if(find(u) == find(v)) continue;
         ans += krus[i].first;
         unite(u,v); 
    }
    if(!on) ans+= dp[1];
    printf("%lld",ans); 
}
