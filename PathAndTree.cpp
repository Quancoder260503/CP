#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef long long ll;
const int sz=3e5+5;
ll n,k,m,q,T,p,ans,start;
ll dp[sz];
ll edgeid[sz];
ll weight[sz];
ll e[sz];
vector<ll>point;
vector<array<ll,3>>adj[sz];
void dijisktra(int src){
    using T=array<ll,2>;
    priority_queue<T,vector<T>,greater<T>>pq;
    for(int i=1;i<=n;i++) dp[i]=LLONG_MAX;
    dp[src]=0;
    pq.push({0,src});
    while (pq.size()){
        array<ll,2>t=pq.top();
        pq.pop();
        if(dp[t[1]]!=t[0]) continue;
        for(auto v:adj[t[1]]){
            if(dp[v[1]]==dp[t[1]]+v[0] and weight[v[1]]>v[0]){
                edgeid[v[1]]=v[2];
                weight[v[1]]=v[0];
            }
            else if(dp[v[1]]>dp[t[1]]+v[0]){
                weight[v[1]]=v[0]; 
                edgeid[v[1]]=v[2]; 
                dp[v[1]]=dp[t[1]]+v[0];
                pq.push({dp[v[1]],v[1]});
            }
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        ll u,v,w;cin>>u>>v>>w;
        e[i]=w;
        adj[u].push_back({w,v,i});
        adj[v].push_back({w,u,i});
    }
     cin>>start;
     dijisktra(start);
     for(int i=1;i<=n;i++){
         if(i!=start){ans+=e[edgeid[i]];point.push_back(edgeid[i]);}
     }
     cout<<ans<<endl;
     for(auto p:point) cout<<p<<" ";
}
