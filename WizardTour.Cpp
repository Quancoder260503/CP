#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 4e5 + 10;
const int mod = 1e9 + 7;
long long n,m,k,q;
long long a[N + 1];
long long dp[N + 1]; 
bool vis[N + 1]; 
long long g[2001][2001];
vector<int>adj[N + 1];
vector<array<int,3>>ans; 
bool dfs(int u,int p){
    vis[u] = 1; 
    vector<int>acc;
    for(int i = 0; i < adj[u].size(); i++){
         int v = adj[u][i];
         if(v == p) continue; 
         if(vis[v]){
             if(u < v) acc.push_back(v);       
         }
         else{
            bool chk = dfs(v,u); 
            if(chk) acc.push_back(v);
         }
    }
    for(int i = 0; i < acc.size() / 2; i++){
         ans.push_back({acc[2 * i],u,acc[2 * i + 1]});
    }
    if(acc.size() % 2 == 0) return true; 
    if(p) ans.push_back({acc[acc.size() - 1],u,p}); 
    return false; 
}
int main(){
     scanf("%d%d",&n,&m);  
     for(int i = 0; i < m; i++){
          int u,v; scanf("%d%d",&u,&v); 
          adj[u].push_back(v);
          adj[v].push_back(u); 
     }
     for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i,0); 
     cout<<ans.size()<<endl; 
     for(int i = 0; i < ans.size(); i++){
          array<int,3> x = ans[i];
          cout<<x[0]<<' '<<x[1]<<' '<<x[2]<<endl; 
     }
}
