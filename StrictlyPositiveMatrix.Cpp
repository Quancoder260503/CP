#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int N = 5e4 + 10;
long long n,m,comp;
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
deque<int>S;
int in[N + 1];
long long val[N + 1];
int low[N + 1]; 
bool vis[N + 1];
long long dp[N + 1];
int fa[N + 1]; 
int timer = 1; 
void dfs(int u){
     in[u] = low[u] = timer++;
     S.push_back(u);
     for(int i = 0; i < adj[u].size();i++){
            int v = adj[u][i];
            if(vis[v]) continue;
            if(!in[v]){
                 dfs(v);
                 low[u] = min(low[u],low[v]);
            }
            else low[u] = min(low[u],in[v]);
     }
     if(in[u] == low[u]){ 
        comp++;
        while(1){
             int v = S.back();
             S.pop_back();
             vis[v] = 1; 
             if(u == v) break; 
        }   
    }
}
int main(){
     scanf("%d%",&n);
     for(int i = 0; i < n; i++){
          for(int j = 0; j < n; j++){
               int x; scanf("%d",&x);
               if(x) adj[i + 1].push_back(j + 1); 
          }
     }
     for(int i = 1; i <= n; i++) if(!in[i]) dfs(i);
     cout<< (comp == 1 ? "YES" : "NO") <<endl; 
}
