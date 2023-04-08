#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
#define blksz 500
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
template <class T> using Tree = tree<T, null_type, less<T>,
	rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
const int N = 3e5 + 10;
const long long INF = 1e7 + 5;
const int mod = 1e9 + 7;
long long n,m,k,q,p;
vector<int>adj[N + 1]; 
multiset<int>dp[N + 1]; 
int a[N + 1];
long long dpf[N + 1]; 
void dfs(int u){
      for(int i = 0; i < adj[u].size(); i++){
             int v = adj[u][i]; 
             dfs(v); 
             if(dp[v].size() > dp[u].size()) swap(dp[v],dp[u]); 
             for(auto it: dp[v]){ 
                 dp[u].insert(it); 
             }
      }
      if(dp[u].size()){
           auto it = dp[u].upper_bound(a[u] - 1); 
           if(it != dp[u].end()) dp[u].erase(it); 
      }
      dp[u].insert(a[u]); 
}
signed main(){
      scanf("%d",&n);
      for(int i = 1; i <= n; i++){ 
          int u; scanf("%d%d",&a[i],&u);
          if(u > 0){
             adj[u].push_back(i); 
          }
      } 
      dfs(1);
      cout << dp[1].size() << endl; 
      return 0;
}
