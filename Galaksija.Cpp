#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
#define blksz 500;
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
const int N = 1e5 + 10;
const int inf = 1e7 + 5;
const int mod = 1e9 + 7;
long long n,m,k,q,p,d; 
vector<int>dv[N + 1]; 
map<long long,vector<int>>dp[N + 1];
long long A[N + 1]; 
long long dep[N + 1]; 
int fa[N + 1];
int ord[N + 1]; 
long long ans = 0;
int sz[N + 1]; 
struct edge{
     int u,v,w,id;
} edges[N + 1];
int find(int u){
      return fa[u] == u ? u : fa[u] = find(fa[u]); 
}
void merge(int u,int v,int w){
      int fu = find(u); int fv = find(v); 
      if(fu == fv) return;
      if(sz[fu] < sz[fv]){ 
         swap(fu,fv);
         swap(u,v); 
      } 
      for(auto it : dp[fv]){ 
           for(auto vec : it.second){
                ans += (1ll) * dp[fu][dep[vec] xor w xor dep[v] xor dep[u]].size(); 
           }
      }
      int depth = dep[v]; 
      for(auto it : dp[fv]){
            for(auto vec : it.second){
                 dep[vec] = dep[vec] xor depth xor dep[u] xor w;
                 dp[fu][dep[vec]].push_back(vec); 
            }
      }
      sz[fu] += sz[fv]; 
      fa[fv] = fu; 
      dp[fv].clear(); 
      sz[fv] = 0; 
}
signed main(){
      scanf("%d",&n); 
      for(int i = 1; i <= n; i++){
         dep[i] = 0;
         fa[i] = i;
         sz[i] = 1;
         dp[i][0].push_back(i); 
      }
      for(int i = 0; i < n - 1; ++i){
           scanf("%d%d%d",&edges[i].u,&edges[i].v,&edges[i].w); 
           edges[i].id = i;
      }
      for(int i = 0; i < n - 1; i++){ 
           scanf("%d",&ord[i]); 
      }
      vector<long long>res;
      res.push_back(0);
      for(int j = n - 2; j >= 0; j--){
            int i = --ord[j]; 
            merge(edges[i].u, edges[i].v, edges[i].w); 
            res.push_back(ans);
      }
      reverse(res.begin(),res.end()); 
      for(int i = 0; i < res.size(); i++){ 
            printf("%lld\n",res[i]); 
      }
      return 0;
}
