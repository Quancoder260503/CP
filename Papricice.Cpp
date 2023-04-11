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
set<int>dp[N + 1];
long long A[N + 1]; 
long long dep[N + 1]; 
int fa[N + 1];
int ord[N + 1]; 
int trs[N + 1]; 
long long ans = inf;
vector<int>adj[N + 1]; 
void dfs(int u,int p){
       trs[u] += 1;
       for(int i = 0; i < adj[u].size(); i++){
             int v = adj[u][i];
             if(v == p) continue; 
             dfs(v,u); 
             if(dp[u].size() < dp[v].size()) swap(u,v);
             for(auto it : dp[v]){
                  dp[u].insert(it); 
             }
             trs[u] += trs[v]; 
       }
       auto it = dp[u].lower_bound(2 * trs[u] - n); 
       ans = min(ans, abs(2 * trs[u] - n - *it)); 
       it = dp[u].lower_bound(n - 2 * trs[u]);
       ans = min(ans, abs(n - 2 * trs[u] - *it)); 
       dp[u].insert(trs[u]); 
}
signed main(){
      scanf("%d",&n); 
      for(int i = 0; i < n - 1; i++){
           int u,v; scanf("%d%d",&u,&v);
           adj[u].push_back(v);
           adj[v].push_back(u); 
      }
      dfs(1,0);
      printf("%d\n",ans); 
      return 0;
}
