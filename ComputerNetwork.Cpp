#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
int n,m,k;
vector<pair<int,int>>g[100005];
double dp[1001][11];
void dijisktra(int src,int k ){
    using Q=pair<double,pair<ll,int>>;
    priority_queue<Q,vector<Q>,greater<Q>>pq;
    dp[src][0]=0;
    pq.push({0,{1,0}});
    while (!pq.empty()){
        double value=pq.top().first;
        int node=pq.top().second.first;
        int use=pq.top().second.second;
        pq.pop();
        if (dp[node][use]!=value) continue;
        for (pair<int,ll> u:g[node]){
             int v=u.first;
             ll val=u.second;
             int div=1;
             for (int i=use;i<=k;i++){
                   double temp=double(val)/double(div);
                   if (dp[v][i]>dp[node][use]+temp){
                        dp[v][i]=dp[node][use]+temp;
                        pq.push({dp[v][i],{v,i}}); 
                  }  div=div*2;
            }
        }
    }
} 
int main() {
    cin>>n>>m>>k;
    for (ll i=0;i<m;i++){
        int u,v,d;
        cin>>u>>v>>d;
        g[u].push_back({v,d});
        g[v].push_back({u,d});
    } const double inf =1e18;
    for (int i=2;i<=n;i++){
        for (int j=0;j<=k;j++){
            dp[i][j]=inf;
        }
    } dijisktra(1,k);
    cout <<dp[n][k];
}
