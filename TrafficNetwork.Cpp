#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int N = 5e5 + 10;
long long n,m,comp,k,s,t;
vector<pii>adj[2][N + 1];
vector<pii>tadj[N + 1];
deque<int>S;
int in[N + 1];
long long val[N + 1];
int low[N + 1]; 
bool vis[N + 1];
int fa[N + 1];
int pos[N + 1]; 
int timer = 1; 
long long dp[10][N + 1]; 
void dijsktra(int src,int id){
      using T = pair<long long,int>;
      priority_queue<T,vector<T>,greater<T>>pq;
      pq.push({0,src}); 
      for(int i = 1; i <= n; i++) dp[id][i] = LLONG_MAX;
      dp[id][src] = 0; 
      while(pq.size()){
            int node; long long weight; 
            tie(weight,node) = pq.top();
            pq.pop();
            if(dp[id][node] != weight) continue; 
            for(int i = 0; i < adj[id][node].size(); i++){
                    int v = adj[id][node][i].first;
                    int weightx = adj[id][node][i].second; 
                    if(dp[id][v] > dp[id][node] + weightx){
                       dp[id][v] = dp[id][node] + weightx;
                       pq.push({dp[id][v],v}); 
                  }
            }
      }
} 
void solve(){
       scanf("%d%d%d%d%d",&n,&m,&k,&s,&t); 
       for(int i = 1; i <= n; i++){
           adj[1][i].clear(); 
           adj[0][i].clear(); 
       }
       for(int i = 0; i < m; i++){
            int u,v,w ; scanf("%d%d%d",&u,&v,&w);
            adj[0][u].push_back({v,w});
            adj[1][v].push_back({u,w}); 
       }
       dijsktra(s,0);
       dijsktra(t,1);
       long long ans = dp[0][t]; 
       for(int i = 0; i < k; i++){
            int u,v,w; 
            scanf("%d%d%d",&u,&v,&w); 
            if(dp[1][u] != LLONG_MAX && dp[0][v] != LLONG_MAX){
                  ans = min(ans, dp[1][u] + dp[0][v] + w);
            }
            if(dp[0][u] != LLONG_MAX && dp[1][v] != LLONG_MAX){
                  ans = min(ans, dp[0][u] + dp[1][v] + w);
            }
       }
       if(ans < LLONG_MAX) printf("%lld\n",ans); 
       else printf("%d\n",-1); 
}
int main(){
       int t; scanf("%d",&t);
       while(t--){
            solve(); 
       }
}
