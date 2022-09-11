#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<map>
#include<vector>
#include<utility>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
ll n,m,q,s,t,k,ans;
ll up[17][sz];
ll lb[sz];
ll opt[sz];
bool use[sz];
ll node[sz];
ll ds[sz],d[sz];
vector<ll>anc[sz];
vector<array<ll,4>>edge;
vector<array<ll,3>>redge;
vector<array<ll,3>>adj[sz];
ll dir[sz],compsize[sz],parent[sz];
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
void dijisktra(ll dis[sz] ,int src){
    using T=pair<ll,ll>;
    priority_queue<T,vector<T>,greater<T>>pq;
    pq.push({0,src});
    dis[src]=0;
    while(pq.size()){
        ll val;int u;
        tie(val,u)=pq.top();
        pq.pop();
        for(auto v:adj[u]){
              if(dis[v[0]]>dis[u]+v[1]){
                dis[v[0]]=dis[u]+v[1];
                pq.push({dis[v[0]],v[0]});
                if(find(v[0])==find(u)) continue;
                unite(v[0],u);
                use[v[2]]=1;
                anc[u].push_back(v[0]);
        }
      }
   }
}
ll jump(ll x, ll d){
    for(int i=0;i<=16;i++){
        if((d>>i)&1) x=up[i][x];
    } return x ;
}
void dfs(int u){
    for(int i=1;i<=16;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:anc[u]){
        if(v==up[0][u]) continue;
        d[v]=d[up[0][v]=u]+1;
        dfs(v);
    }
}
int lca(ll a, ll b){
    if(d[a]<d[b]) swap(a,b);
    a=jump(a,d[a]-d[b]);
    if(a==b) return a;
    for(int i=16;i>=0;i--){
         int tA=up[i][a]; int tB=up[i][b];
         if(tA!=tB) {a=tA; b=tB;}
    } return up[0][a];
}
void upd(int u, int v, ll w){
    int r=lca(u,v);
    int gx=u; int gy=v;
    while ( u != r ){
         if(lb[gx]==gx and gx!=t) opt[u]=min(opt[u],ds[t]-ds[gx]+ds[gy]+w);
         u=up[0][u];
    } 
    while ( v != r ){
        if(lb[gy]==gy and gy!=t) opt[v]=min(opt[v],ds[t]-ds[gy]+w+ds[gx]);
        v=up[0][v];
    }
}
int main(){
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        edge.push_back({u,v,i,w});
        adj[u].push_back({v,w,i});
        adj[v].push_back({u,w,i});
    } cin>>k;
      init(n);
      for(int i=1;i<=n;i++) ds[i]=opt[i]=INT_MAX;
      for(int i=1;i<=k;i++) cin>>node[i];
      for(int i=2;i<=k;i++){
          unite(node[i],node[i-1]);
          for(auto v:adj[node[i-1]]){
              if(v[0]==node[i]){
                  use[v[2]]=1;
              }
          } anc[node[i-1]].push_back(node[i]);
      }
      dijisktra(ds,s);
      dfs(s);
      for(int i=1;i<=n;i++) lb[i]=lca(i,t);
      for(auto e:edge) {if(!use[e[2]]) upd(e[0],e[1],e[3]);}
      for(int i=2;i<=k;i++){
          if(opt[node[i]]>=INT_MAX) cout<<-1<<endl;
          else cout<<opt[node[i]]<<endl;
      }
}