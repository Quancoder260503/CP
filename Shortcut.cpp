#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
vector<pair<int,ll>>g[sz];
vector<ll>a[sz];
ll d[sz];
ll dp[sz];
int par[sz];
ll cows[sz];
int n,m,t;
ll sum;
experience (avoid multyplying with relatively large value (overflow))
#mistake( store all the node and then use dfs (might recompute the value over again))
#solve ( find out how many cow from the chosen one to the descendent node of the chosen one)
void dijisktra(){
    using T=pair<ll,int>;
    priority_queue<T,vector<T>,greater<T>>pq;
    d[1]=0;
    par[1]=0;
    pq.push({0,1});
    while(pq.size()){
        ll val;int node;
        tie(val,node)=pq.top();
        pq.pop();
        for(auto u:g[node]){
            int v=u.first;
            ll  dist=u.second+val;
            if (dist==d[v]) par[v]=min(node,par[v]);  
            else if (dist<d[v]){
                d[v]=dist;
                par[v]=node;
                pq.push({d[v],v});
            }
        }
    }
}
void dfs(int node,int p){
    int sum=cows[node];
    for (auto u :a[node]){
        if (u==p) continue;
        dfs(u,node);
        sum+=dp[u];
    }dp[node]=sum;
}
int main(){
    cin>>n>>m>>t;
    for(int i=1;i<=n;i++){
        cin>>cows[i];
    } for(int i=0;i<m;i++){
        int u,v,d;
        cin>>u>>v>>d;
        g[u].push_back({v,d});
        g[v].push_back({u,d});
    } for(int i=1;i<=n;i++){
        d[i]=LLONG_MAX;
    } dijisktra();  
    for (int i=2;i<=n;i++){
        a[i].push_back(par[i]);
        a[par[i]].push_back(i);
    }
    dfs(1,0);
    ll ans=0;
    for (int i=1;i<=n;i++){
        ans=max(ans,dp[i]*(d[i]-t));
    } cout <<ans;
}
