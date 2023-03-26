#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5;
const int M = 110;
const long long INF = 1e17; 
long long n,m,k;
long long dp[N + 1];
long long a[N + 1];
vector<int>canvisit;
vector<int>adj[N + 1]; 
long long ans;
int up[23][N + 1];
int dfs_calc(int u,int p){
      vector<int>farleaf;
      for(int i = 0; i < adj[u].size(); i++){
           int v = adj[u][i];
           if(v == p) continue;
           farleaf.push_back(dfs_calc(v,u) + 1); 
      }
      sort(farleaf.rbegin(),farleaf.rend());
      int i;
      for(i = 0; i + 1 < farleaf.size(); i++){
            int tot = farleaf[i] + farleaf[i + 1]; 
            if(tot <= k) {
                 return farleaf[i]; 
            }
            ans++; 
      }
      return (farleaf.size() ? farleaf[i] : 0); 
}
int main(){
      scanf("%d%d",&n,&k);
      for(int i = 1; i < n; i++){
           int u,v; scanf("%d%d",&u,&v);
           adj[u].push_back(v);
           adj[v].push_back(u); 
      } 
      int root = 0; 
      for(int i = 1; i <= n; i++){
           if(adj[i].size() > 1){
                root = i;
                break; 
           }
      }
      ans = 1;
      dfs_calc(root,0); 
      printf("%lld\n",ans); 
      return 0; 
}
