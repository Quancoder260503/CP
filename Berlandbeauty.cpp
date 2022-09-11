#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=5001;
const int inf=1e6+1;
ll n,k,m,q,add,dis;
int timer=1;
vector<ll>adj[sz];
vector<array<ll,3>>queries;
vector<array<ll,3>>query;
int curweight;
int ds[sz];
int dp[sz];
int par[sz];
int ans[sz];
int val[sz][sz];
const int mod=998244353;
void dfs(int u){
    for(auto v:adj[u]){
        if(v==par[u]) continue;
        dp[v]=dp[par[v]=u]+1;
        dfs(v);
    }
}
int lca(int x,int y){
     if(dp[x]<dp[y]) swap(x,y);
     while(dp[x]>dp[y]) x=par[x];
     while (x!=y){
         x=par[x];
         y=par[y];
     }
    return x;
}
void jumpupd(int x,int y){
     while(x!=y){
         if(ds[x]>curweight){
             if(ds[x]==inf) ds[x]=curweight;
             else add++;
         }
         x=par[x];
     }
}
int main(){
   cin>>n;
   for(int i=1;i<n;i++){
        ll u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        queries.push_back({u,v,i});
   }
    dfs(1);
    cin>>q;
    for(int j=1;j<=n;j++) ds[j]=inf;
    sort(queries.begin(),queries.end());
    for(int i=1;i<=q;i++){
        ll u,v,w;cin>>u>>v>>w;
        query.push_back({w,u,v});
    }
     sort(query.rbegin(),query.rend());
     for(auto q:query){
         int anc=lca(q[1],q[2]);
         dis=0;
         curweight=q[0];
         jumpupd(q[1],anc);
         dis+=add; add=0;
         jumpupd(q[2],anc);
         dis+=add; add=0; 
         if(dis==dp[q[1]]+dp[q[2]]-2*dp[anc]){
             cout<<-1<<endl;
             exit(0);
         }
    }
    for(int i=1;i<=n;i++){
       if(ds[i]==inf) ds[i]--;
    }
    for(auto q:queries){
        if(dp[q[0]]<dp[q[1]]) swap(q[0],q[1]);
        ans[q[2]]=ds[q[0]];
    }
    for(int i=1;i<n;i++) cout<<ans[i]<<" ";
}