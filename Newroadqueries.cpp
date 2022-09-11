#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
ll n,m,q;
ll up[20][sz];
int dp[20][sz];
ll dep[sz];
ll compsize[sz];
ll parent[sz];
bool vis[sz];
vector<array<ll,2>>adj[sz];
void init(int n){
	for (int i = 1; i <= n; i++){
		parent[i] = i;
		compsize[i] = 1;
	}
}
int find(int a){
	if (a == parent[a]) return a;
	return parent[a] = find(parent[a]);
}
void unite(int a, int b){
	int roota = find(a), rootb = find(b);
	if (roota == rootb) return ;
	if (compsize[roota] > compsize[rootb]) swap(roota, rootb);
	parent[roota] = rootb;
	compsize[rootb] += compsize[roota];
}
void dfs(int u){
    vis[u]=1;
    for(auto v:adj[u]){
        if(v[1]==up[0][u]) continue;
        dep[v[1]]=dep[up[0][v[1]]=u]+1;
        dp[0][v[1]]=v[0];
        dfs(v[1]);
    }
}
array<int,2>jump(int x,int d){
    int res=0;
    for(int i=0;i<=19;i++){
        if((d>>i)&1){
            res=max(res,dp[i][x]);
            x=up[i][x];
        }
    } return {x,res};
}
ll lca(int u,int v){
    if(dep[u]<dep[v]) swap(u,v);
    array<int,2>x=jump(u,dep[u]-dep[v]);
    u=x[0];
    int res=x[1];
    if(u==v) return res;
    for(int i=19;i>=0;i--){
        int tu=up[i][u]; int tv=up[i][v];
        if(tu!=tv){ 
          res=max(res,dp[i][u]);
          res=max(res,dp[i][v]);
          u=tu,v=tv;
        }    
    }
      res=max(res,dp[0][v]);
      return max(res,dp[0][u]);
}
void push(){
    for(int i=1;i<=19;i++){
        for(int u=1;u<=n;u++){
            up[i][u]=up[i-1][up[i-1][u]];
        }    
    }
    for(int i=1;i<=19;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=max(dp[i-1][j],dp[i-1][up[i-1][j]]);
        }
    }
}
int main(){
    cin>>n>>m>>q;
    init(n);
    for(int i=1;i<=m;i++){
        ll u,v; cin>>u>>v;
        if(find(u)==find(v)) continue;
        unite(u,v);
        adj[u].push_back({i,v});
        adj[v].push_back({i,u});
    } 
      for(int i=1;i<=n;i++){
          if(!vis[i]) dfs(i);
      }
      push();
      for(int i=0;i<q;i++){
          ll u,v; cin>>u>>v;
          if(find(u)!=find(v)) cout<<-1<<endl;
          else cout<<lca(u,v)<<endl;
      }
}