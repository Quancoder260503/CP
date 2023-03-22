#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int sz = 1e6 + 10;
const int N = 3e5 + 10;
const int M = 1e6 + 10;
const long long INF = 1e17; 
const int mod = 998244353;
long long a[N + 1];
long long dp[N + 1];
long long n,x;
int timer = 1;
vector<pii>adj[N + 1];
long long ans[N + 1]; 
int in[N + 1];
int out[N + 1]; 
char s[N + 1];
int tree[(N + 1) << 2 ]; 
void dfs(int u,int p){
      in[u] = timer++; 
      for(int i = 0; i < adj[u].size(); i++){
           auto v = adj[u][i];
           if(v.first == p) continue;
           dp[v.first] = dp[u] + v.second;
           dfs(v.first,u); 
      }
      out[u] = timer - 1; 
}
// dis(u,v) <= a[u]
// dp[u] - a[u] <= dp[v] 
void upd(int L,int R,long long val,int l = 1, int r = n,int p = 1){
      if(L > r or R < l) return;
      if(L <= l and r <= R){
           tree[p]++; 
           return; 
      } 
      int mid = (l + r) >> 1; 
      upd(L,R,val,l,mid,2 * p);
      upd(L,R,val,mid + 1,r, 2 * p + 1);
      tree[p] = tree[2 * p + 1] + tree[2 * p];
}
long long query(int L,int R,int l = 1, int r = n, int p = 1){
      if(L > r or R < l) return 0;
      if(L <= l and r <= R) return tree[p];
      int mid = (l + r) >> 1; 
      return query(L,R,l,mid,2 * p) + query(L,R,mid + 1,r,2 * p + 1);
}
int main(){
      scanf("%lld",&n);
      for(int i = 1; i <= n; i++) scanf("%lld", a + i); 
      for(int i = 2; i <= n; i++){
            int u,w; scanf("%d%d",&u,&w);        
            adj[u].push_back({i,w});
            adj[i].push_back({u,w}); 
      }
      dfs(1,0);
      vector<pair<long long,pair<bool,int>>>queries; 
      for(int i = 1; i <= n; i++){
            queries.push_back({dp[i] - a[i],{0,i}});  
            queries.push_back({dp[i],{1,i}}); 
      }    
      sort(queries.begin(),queries.end());
      for(int i = 0; i < queries.size(); i++){
            int u = queries[i].second.second; 
            int type = queries[i].second.first;
            //cout << queries[i].first <<' ' << type << ' ' << u << endl; 
            if(type == 0){
                  upd(in[u],in[u],1); 
            }
            else{
                 ans[u] = query(in[u] + 1,out[u]); 
            }
      }
      for(int i = 1; i <= n; i++){
           printf("%lld ",ans[i]); 
      }
      return 0; 
}
