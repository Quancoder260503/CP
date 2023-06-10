#include <bits/stdc++.h>
using namespace std;
const int sz=1e3+1;
const int inf=1e6+10;
typedef long long ll;
int n,m,res;
vector<array<int,3>>adj[sz];
int dpl[sz];
int dpr[sz];
int vis[sz];
int to[sz];
int ans = 0;
vector<int>co;
void dfs(int u, int p,int l,int r){
     if(u == n){
         ans = max(ans, r - l + 1);
         return;
     }
     for(int i = 0; i < adj[u].size(); i++){
          array<int,3> v  = adj[u][i];
          if(v[0] == p) continue;
          int lb = max(l,v[1]);
          int rb = min(r,v[2]);
          if( lb > rb ) continue;
          if(ans !=  - 1 and ans > rb - lb + 1) continue;
          if(vis[v[0]] and dpl[v[0]] <= lb and rb <= dpr[v[0]]) continue;
          dpl[v[0]] = lb; dpr[v[0]] = rb;
          vis[v[0]] = 1;
          dfs(v[0],u,lb,rb);
     }
}
int main(){
      scanf("%d%d",&n,&m);
      for(int i = 1; i <= m; i++){
          int u,v,l,r;
          scanf("%d%d%d%d",&u,&v,&l,&r);
          adj[u].push_back({v,l,r});
          adj[v].push_back({u,l,r});
      }
       ans = -1;
       dfs(1,0,-inf,inf);
       if(ans < 0) cout<<"Nice work, Dima!"<<endl;
       else cout<<ans<<endl;
}
