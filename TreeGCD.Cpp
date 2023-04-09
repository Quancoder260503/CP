#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
#define blksz 500;
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
const int N = 3e5 + 10;
const int inf = 1e7 + 5;
const int mod = 1e9 + 7;
long long n,m,k,q,p,d;
vector<int>adj[N + 1];  
vector<int>dv[N + 1]; 
map<pair<int,int>,int>dp[N + 1];
long long A[N + 1]; 
void dfs(int u,int p,int d){
      for(int i = 0; i < dv[u].size(); i++){
           int cur = dv[u][i]; 
           dp[u][{cur,d % cur}] += 1; 
      }
      for(int i = 0; i < adj[u].size(); i++){
           int v = adj[u][i];
           if(v == p) continue;
           dfs(v,u, d + 1); 
           if(dp[u].size() < dp[v].size()) swap(dp[v],dp[u]);
           for(auto it : dp[v]){
                 auto pii = it.first;
                 int dis = (-pii.second % pii.first + 2 * d  + pii.first) % pii.first; 
                 if(dp[u].count({pii.first,dis})){
                      A[pii.first] += (1ll) * it.second * dp[u][{pii.first,dis}]; 
                 }
           }
           for(auto it : dp[v]){
                dp[u][it.first] += it.second; 
           }
      } 
}
signed main(){
      scanf("%d",&n); 
      for(int i = 1; i < n; i++){
           int u,v; scanf("%d%d",&u,&v);
           adj[u].push_back(v);
           adj[v].push_back(u); 
      }
      for(int i = 1; i <= n; i++){
           for(int j = i; j <= n; j += i){
                dv[j].push_back(i); 
           }
      }
      dfs(1,0,0); 
      long long ans = 0;
      for(int i = n; i > 0; i--){
           for(int j = 2 * i; j <= n; j += i){
               A[i] = A[i] - A[j];
           }
           ans += (1ll) * A[i] * i; 
      }
      cout << ans << endl;
      return 0;
}
