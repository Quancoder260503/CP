#include <bits/stdc++.h>
#include<cstdio>
using namespace std;
typedef long long ll;
const int sz=3e5+3;
vector<ll>adj[sz];
vector<array<ll,2>>queries[sz];
ll ans[sz],dp[sz],val[sz];
ll n,q;
ll sum=0;
void dfs(int u,int p){
    for(auto v:queries[u]){
        val[dp[u]]+=v[1];
        if(dp[u]+v[0]+1<n) val[dp[u]+v[0]+1]-=v[1];
    }
    sum+=val[dp[u]];
    ans[u]=sum;
    for(auto v:adj[u]){
        if(v==p) continue;
        dp[v]=dp[u]+1;
        dfs(v,u);
    }
    sum-=val[dp[u]];
    for(auto v:queries[u]){
        val[dp[u]]-=v[1];
        if(dp[u]+v[0]+1<n) val[dp[u]+v[0]+1]+=v[1];
    }
}
int main(){
   scanf("%d", &n);
   for(int i=0;i<n-1;i++){
       int u , v;
       scanf("%d%d",&u,&v);
       adj[u].push_back(v);
       adj[v].push_back(u);
   }
   scanf("%d", & q);
   dfs(1,0);
    for(int i=1;i<=q;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        //cout<<u<<" "<<v<<" "<<w<<endl;
        queries[u].push_back({v,w});
    }
    dfs(1,0);
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
}