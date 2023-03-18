#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
int n,m,k;
vector<pair<int,ll>>g[100005];
const int inf =1e9;
int  dijisktra(int src,int n,int k){
    vector<vector<ll>>dp(n+1,vector<ll>(k+1,inf));
    using T=pair<ll,pair<int,int>>;
    priority_queue<T,vector<T>,greater<T>>pq;
    dp[src][0]=0;
    pq.push({0,{src,0}});
    while(!pq.empty()){
        int node;ll val;int use;
        val=pq.top().first;
        node=pq.top().second.first;
        use=pq.top().second.second;
        pq.pop();
        if (dp[node][use]!=val) continue;
        for (auto u:g[node]){
            int v=u.first;
            ll cost=u.second;
            if (use>k) continue;
            if (dp[v][use]>dp[node][use]+cost){
                dp[v][use]=dp[node][use]+cost;
                pq.push({dp[v][use],{v,use}});
            if (use+1>k) continue;
            if (dp[v][use+1]>dp[node][use]){
                dp[v][use+1]=dp[node][use];
                pq.push({dp[v][use+1],{v,use+1}});
            }
        }
    }
  } return dp[n][k];
}
int main() {
      cin>>n>>m>>k;
      for (int i=0;i<m;i++){
          int u,v; ll d;
          cin>>u>>v>>d;
          g[u].push_back({v,d});
          g[v].push_back({u,d});
      } cout <<dijisktra(1,n,k);
 }
