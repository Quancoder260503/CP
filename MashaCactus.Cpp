#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int sz1=1e6+1;
const int inf=1e18;
int n,m;
int cnt=1;
int in[sz],out[sz];
int bit[sz];
int up[19][sz];
vector<int>adj[sz];
vector<array<int,3>>dp[sz];
int h[sz];
int f[sz];
int sum(int i) {
	int c=0;
	for(++i; i > 0 ; i -= (i & -i))
		c+= bit[i];
	return c;
}
int query(int l,int r){
    return sum(r)-sum(l-1);
}
void add(int i,int dif)
{
	for(++i; i < sz ; i += (i & -i))
		bit[i] += dif;
}
void dfs(int u){
     in[u]=cnt++;
     for(int i=1;i<=18;i++){
         up[i][u]=up[i-1][up[i-1][u]];
     }
     for(auto v:adj[u]){
          if(v==up[0][u]) continue;
          h[v]=h[u]+1;
          dfs(v);
     }
     out[u]=cnt;
}
int lca(int u,int v){
     if(h[u]<h[v]) swap(u,v);
     int d=h[u]-h[v];
     for(int i=0;i<=18;i++){
         if(d&(1<<i)) u=up[i][u];
     }
     if(u==v) return u;
     for(int i=18;i>=0;i--){
         int tu=up[i][u];
         int tv=up[i][v];
         if(tv!=tu){
              v=tv;
              u=tu;
          }
     }
     return up[0][u];
}
void dfs1(int u){
     int ac=0;
     for(auto v:adj[u]){
          if(v==up[0][u]) continue;
          dfs1(v);
          ac+=f[v];
     }
     f[u]=ac;
     for(auto v:dp[u]){
          int x=v[0]; int y=v[1]; int w=v[2];
          f[u]=max(f[u],sum(in[x])+sum(in[y])+w+ac);
     }
     int sub=ac-f[u];
     add(in[u],sub);
     add(out[u],-sub);
}
int main(){
    cin>>n>>m;
    for(int i=2;i<=n;i++){
         cin>>up[0][i];
         adj[up[0][i]].push_back(i);
    }
    dfs(1);
    for(int i=1;i<=m;i++){
          int u,v,w; cin>>u>>v>>w;
          dp[lca(u,v)].push_back({u,v,w});
    }
    dfs1(1);
    cout<<f[1]<<endl;
}
