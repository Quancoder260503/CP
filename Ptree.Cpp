#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 4e5 + 10;
const int mod = 1e9 + 7;
const int inv = 5e8 + 4;
const int MAXC  = 20; 
long long n,m,k,q,component,ans,p;
long long a[N + 1];
int timer = 1;
vector<int>S; 
bool vis[N + 1]; 
int in[N + 1], low[N + 1]; 
int fa[N + 1], res[N + 1]; 
int col[N + 1]; 
int trs[N + 1];
int lst[N + 1];
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
int tr[250][250][250];
long long dp[250][250][250];
void dfs(int u,int p){
     dp[u][0][1] = a[u]; 
     trs[u] = 1;
     fa[u] = p; 
     int curr = 0; 
     for(int i = 0; i < adj[u].size(); i++){
          int v = adj[u][i];
          if(v == p) continue; 
          dfs(v,u); 
          curr++; 
          tadj[u].push_back(v);
          for(int j = 0; j <= trs[u]; j++){
               dp[u][curr][j] = dp[u][curr - 1][j];  
               tr[u][curr][j] = 0; 
          }
          for(int j = 0; j <= trs[u]; j++){
              for(int k = 0; k <= trs[v]; k++){
                   if(dp[u][curr][j + k] < dp[u][curr - 1][j] + dp[v][lst[v]][k]){
                        dp[u][curr][j + k] = dp[u][curr - 1][j] + dp[v][lst[v]][k]; 
                        tr[u][curr][j + k] = k; 
                   }
              }
          }
          trs[u] += trs[v];
     }
     lst[u] = curr; 
}
void trace(int u,int p,long long tot){
      if(!tot) return; 
      vis[u] = 1;
      for(int i = tadj[u].size() - 1; i >= 0; i--){
          int v = tadj[u][i];
          if(v == p) continue; 
          long long w = tr[u][i + 1][tot];
          ////cout<<v<<' '<<tot<<' '<<w<<endl;
          if(w > 0) trace(v,u,w);
          tot = tot - w; 
      }
}
int main(){
     scanf("%d%d",&n,&p);
     for(int i = 1; i <= n; i++) cin>>a[i]; 
     for(int i = 0; i < n - 1; i++){
          int u,v;  scanf("%d%d",&u,&v);
          adj[u].push_back(v);
          adj[v].push_back(u); 
     }
     memset(dp,-0x3f, sizeof(dp));  
     dfs(1,0);
     pair<long long,int> min_f = {-0x3f,0};
    // cout<<dp[2][lst[2]][p]<<endl; 
     for(int i = 1; i <= n; i++){
          min_f = max(min_f,{dp[i][lst[i]][p],i}); 
     }
     memset(vis,0,sizeof(vis)); 
     trace(min_f.second,0,p);
     for(int i = 1; i <= n; i++){
         if(vis[i]) cout<<i<<' '; 
     }
     cout<<endl; 
}
