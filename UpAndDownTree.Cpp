#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
const int M = 110;
const long long INF = 1e7 + 5; 
long long n,m,k;
long long a[N + 1];
vector<int>adj[N + 1]; 
int dp[N + 1][2];
int height[N + 1]; 
int up[23][N + 1];
void dfs_calc(int u,int p){
    if(!adj[u].size()){
        dp[u][0] = dp[u][1] = 1;
        height[u] = k;
        return;
    }
   // height[u] = INF;
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i]; 
        dfs_calc(v,u);
        height[u] = max(height[v] - 1, height[u]);
        if(height[v] > 0) dp[u][0] += dp[v][0]; 
    }
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(height[v] > 0) dp[u][1] = max(dp[u][1], dp[u][0] - dp[v][0] + dp[v][1]);
        else dp[u][1] = max(dp[u][1], dp[u][0] + dp[v][1]); 
    }
}
 
int main(){
      scanf("%d%d",&n,&k);
      for(int i = 2; i <= n; i++){
           int v; scanf("%d",&v);
           adj[v].push_back(i); 
      }
      dfs_calc(1,0);
      printf("%d\n",dp[1][1]); 
      return 0; 
}
