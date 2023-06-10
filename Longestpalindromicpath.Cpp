#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz = 5e5+10;
const int sz1 = (1<<22) + 1;
const int mod = 1e9 + 7;
const long long inf = 1e16;
int n,k,m,q,dis,lim;
ll timer=1;
long long val[sz1];
long long dp[sz];
long long trs[sz];
long long res[sz];
char a[sz];
long long d[sz];
long long in[sz];
long long at[sz];
long long out[sz];
vector<int>adj[sz];
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef map<long long,long long> Container;
const int sz = 5e5+10;
const int mod = 1e9 + 7;
int n,k,m,q,dis,lim;
ll timer=1;
long long dp[sz];
long long trs[sz];
long long res[sz];
char a[sz];
long long b[sz];
vector<int>adj[sz];
////TLE version 
void dfs(int u,int p){
     trs[u] = 1;
     for(int i = 0; i < adj[u].size(); i++){
          int v = adj[u][i];
          if(v == p) continue;
          dp[v] = dp[u] + 1; 
          dfs(v,u);
          trs[u] += trs[v];
     }
}
void dfs_hld(int u,int p,Container &set){
      int mx = -1;
      int big = -1;
      for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(v == p) continue;
            if(mx < trs[v]){
               mx = trs[v];
               big = v;
            }
      }
      if(big != - 1) dfs_hld(big,u,set);
      long long ans = 0;
      for(auto it:set){
           if(__builtin_popcountll(it.first) <= 1){
                ans = max(ans,it.second - dp[u]);
           }
      }
      for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(v  == p or v == big) continue;
            Container extract;
            dfs_hld(v,u,extract);
            for(auto it: set){
                 for(auto it1: extract){
                     int bit = __builtin_popcountll(it.first^it1.first);
                     if(bit <= 1){
                          ans = max(ans, it.second + it1.second - 2*dp[u]);  
                     }
                 }
            }
            for(auto it: extract){
                  set[it.first] = max(set[it.first],it.second);
            }
      }
      res[u] = ans; 
      for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(v == p) continue;
            res[u] = max(res[u],res[v]);
      }
      if(u > 1){
          Container temp; 
          for(auto it:set){
              temp[it.first ^(1<<(a[u] - 'a'))] = max(temp[it.first^(1<<(a[u] - 'a'))], set[it.first]);
          }
          set.clear();
          set = temp; 
          set[(1<<(a[u] - 'a'))] = max(set[1<<(a[u] - 'a')],dp[u]);
      }
}
int main(){
       scanf("%d",&n); 
       for(int i = 2; i <= n; i++){
             int u;  cin>>u>>a[i]; 
             adj[u].push_back(i);
       }
       dfs(1,0); 
       Container mp;
       dfs_hld(1,0,mp);
       for(int i = 1; i <= n; i++) cout<<res[i]<<' ';
}
///Accepted version
void dfs(int u,int p){
     trs[u] = 1;
     in[u] = timer++;
     at[in[u]] = u; 
     for(int i = 0; i < adj[u].size(); i++){
          int v = adj[u][i];
          if(v == p) continue;
          dp[v] = dp[u] + 1;
          d[v] = (1 << (a[v] - 'a')) ^ d[u];
          dfs(v,u);
          trs[u] += trs[v];
     }
     out[u] = timer;
}
void dfs_hld(int u,int p,bool keep){
      int mx = -1;
      int big = -1;
      for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(v == p) continue;
            if(mx < trs[v]){
               mx = trs[v];
               big = v;
            }
      }
      long long ans = 0;
      for(int i = 0; i < adj[u].size(); i++){
             int v = adj[u][i];
             if( v == p or v == big) continue;
             dfs_hld(v,u,0);
             res[u] = max(res[u], res[v]);
      }
      if(big != -1){
           dfs_hld(big,u,1);
           res[u] = max(res[u], res[big]);
      }
      for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(v == p or v == big) continue;
            for(int j = in[v]; j < out[v]; j++){
                 int curv = at[j];
                 res[u] = max(res[u], dp[curv] + val[d[curv]]  - 2*dp[u]);
                 for(int c = 0; c < 22; c++){
                     if(val[d[curv] ^ (1 << c)] <= 0) continue;
                     res[u] = max(res[u], dp[curv] + val[d[curv] ^ (1 << c)] - 2*dp[u]);
                 }
            }
            for(int j = in[v]; j < out[v]; j++){
                 int curv = at[j];
                 val[d[curv]] = max(val[d[curv]], dp[curv]);
            }
      }
      res[u] = max(res[u], val[d[u]] - dp[u]);
      for(int c = 0; c < 22; c++){ 
           res[u] = max(res[u], val[d[u] ^ (1 << c)] - dp[u]);
      }
      val[d[u]] = max(val[d[u]], dp[u]);
      if(!keep){
           for(int i = in[u]; i < out[u]; i++){
                 int curv = at[i];
                 val[d[curv]] = -inf;
           }
      }
}
int main(){
       scanf("%d",&n); 
       for(int i = 2; i <= n; i++){
             int u;  scanf("%d %c",&u,&a[i]); 
             adj[u].push_back(i);
       }
       dfs(1,0); 
       memset(val,-inf,sizeof(val));
       dfs_hld(1,0,1);
       for(int i = 1; i <= n; i++) printf("%d ",res[i]);
}
