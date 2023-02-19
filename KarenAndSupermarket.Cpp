#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e3 + 10;
const long long INF = 1e17 + 10; 
long long n,m,q,dsz,M,res;
int timer = 1;
vector<int>adj[N + 1];
int up[22][N + 1];
long long cost[N + 1];
long long rec[N + 1]; 
long long disc[N + 1]; 
vector<long long>dp[N + 1][2];
vector<long long>calc(vector<long long>&a, vector<long long>&b){
     vector<long long>merge(a.size() + b.size() - 1,INF);
     for(int i = 0; i < a.size(); i++){
          for(int j = 0; j < b.size(); j++){
               merge[i + j] = min(merge[i + j],a[i] + b[j]);
          }
     }
     return merge; 
}
void dfs(int u){
      dp[u][0] = {0,cost[u]};
      dp[u][1] = {INF,disc[u]}; 
      for(int i = 0; i < adj[u].size(); i++){
           int v = adj[u][i];
           dfs(v);
           dp[u][0] = calc(dp[v][0],dp[u][0]);
           dp[u][1] = calc(dp[v][1],dp[u][1]); 
      }
      for(int i = 0; i < dp[u][1].size(); i++){
           dp[u][1][i] = min(dp[u][1][i], dp[u][0][i]); 
      }
}
int main(){
     scanf("%d%lld",&n,&m);
     for(int i = 1; i <= n; i++){
           scanf("%lld%lld",&cost[i],&rec[i]);
           disc[i] = cost[i] - rec[i];
           if(i == 1) continue;
           int x; scanf("%d",&x);
           adj[x].push_back(i); 
     }
     dfs(1);
     long long ans = 0; 
     for(int i = n; i > 0; i--){
         if(dp[1][1][i] <= m){
             ans = i;
             break; 
         }
     }
     printf("%lld",ans); 
     return 0; 
}
