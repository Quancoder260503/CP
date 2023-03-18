#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
const int sz1=1e6+1;
const int inf=1e18;
int n,m,q;
vector<array<ll,3>>edge;
vector<array<ll,3>>redge;
vector<array<ll,3>>adj[sz];
vector<pair<ll,ll>>adj1[sz];
ll dp[17][sz];
ll up[17][sz];
ll ds[sz][201];
ll d[sz];
bool vis1[sz];
bool vis[sz]; 
ll ans[sz1];
ll bit[sz];
void dfs(int u){
    vis1[u] = 1;
    for(int i=1;i<17;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(vis1[v[0]]) continue;
        dp[0][v[0]]=v[1];
        d[v[0]] = d[up[0][v[0]]=u]+1;
        vis[v[2]] = 1; 
        dfs(v[0]);
    }
}
int lca(int a,int b){
     if(d[a]<d[b]) swap(a,b);
     int ds=d[a]-d[b];
     for(int i=0;i<17;i++){
         if(ds&(1<<i)) a=up[i][a];
     }
     if(a==b) return a;
     for(int i=16;i>=0;i--){
          int ta=up[i][a];
          int tb=up[i][b];
          if(ta!=tb){
              a=ta; 
              b=tb;
          }
     }
     return up[0][a];
}
ll calc_dis(int x,int d){
     ll acc=0;
     for(int i=0;i<17;i++){
          if(d&(1<<i)){
               acc+=dp[i][x];
               x=up[i][x];
          }
     }
     return acc; 
}
void dijktra(int src,int ord){
    using Q=pair<ll,int>;
    priority_queue<Q,vector<Q>,greater<Q>>q;
    for(int i=1;i<=n;i++) ds[i][ord]=1e18;
    ds[src][ord]=0;
    q.push({0,src});
    while (!q.empty()){
        ll node=q.top().second;
        ll value=q.top().first;
        q.pop();
        if (ds[node][ord] != value) continue;
        for (array<ll,3> u:adj[node]){
            if ((long long) u[1]+value<ds[u[0]][ord]){
                ds[u[0]][ord]= (long long) (value + u[1]);
                q.push({ds[u[0]][ord],u[0]});
            }
        }
    }
}
ll dis(int a,int b){
     int anc=lca(a,b);
     ll dis0=calc_dis(a,d[a]-d[anc]);
     ll dis1=calc_dis(b,d[b]-d[anc]);
     return dis0+dis1;
}
int main(){
    scanf("%d%d",&n,&m); 
    for(int i=1;i<=m;i++){
        ll u,v,w;
        scanf("%lld%lld%lld",&u,&v,&w); 
        adj[u].push_back({v,w,i});
        adj[v].push_back({u,w,i});
        edge.push_back({i,u,v});
    }    
    dfs(1);
    for(int i=1;i<17;i++){
        for(int j=1;j<=n;j++){
              dp[i][j]=dp[i-1][j] + dp[i-1][up[i-1][j]];
         }
    }
    int cnt=0;
    //Faster way: 
    // compute the minimum distance from 1 speacial node to another ? 
    // run dfs -> for each node compute the shortest distance from 1 node to a speacial node
    for(auto e: edge){
         if(vis[e[0]]) continue; 
         dijktra(e[1],cnt++);
    }
    scanf("%d",&q); 
    for(int i=0;i<q;i++){
         int u,v; scanf("%d%d",&u,&v); 
         ll cur_dis = dis(u,v);
         for(int i=0;i < cnt; i++){
              cur_dis=min(cur_dis,(long long) (ds[u][i]+ds[v][i]));
         }
         printf("%lld\n",cur_dis); 
    }
}
