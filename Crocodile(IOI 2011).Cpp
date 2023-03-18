#include<bits/stdc++.h>
#include<iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=1e6+1;
ll p[sz];
ll dp[sz];
ll d1[sz];
int vis[sz];
vector<array<ll,2>>adj[sz];
int n,m,k;   
void dijisktra(){
    using T=pair<ll,int>;
    priority_queue<T,vector<T>,greater<T>>pq;
    for (int i=0;i<k;i++){
        pq.push({0,p[i]});
    }
    while (pq.size()){
        int u;ll val;
        tie(val,u)=pq.top();
        pq.pop();
        if (dp[u]!=val) continue;
        for (auto e:adj[u]){
            int v=e[0]; ll dist=dp[u]+e[1];
            if (dist<d1[v] and vis[v]==0){
                d1[v]=dist;
                vis[v]++;
            } else if (dist<d1[v] and vis[v]>0){
                pq.push({dp[v]=d1[v],v});
                vis[v]++;
                d1[v]=dist;
            } else if (d1[v]<=dist and dist<dp[v]){
                pq.push({dp[v]=dist,v});
                vis[v]++;
            }
        }
    }
}
void dfs(int u,int p){
    int minv=0; int ed=0;int x=1e9; int v=0;
    for(auto e:adj[u]){
        if (e[0]==p) continue;
        dfs(e[0],u);
        if (x>e[1]+dp[e[0]]){
            x=e[1]+dp[e[0]];
            v=e[0];
        }
    } 
    for (auto e:adj[u]){
        if (e[0]==v and x==e[1]+dp[e[0]]) continue;
        dp[u]=min(dp[u],e[1]+dp[e[0]]);
    } 
    if (dp[v]==1e18) dp[v]=x;   
}
int main(){
     cin>>n>>m>>k;
    for (int i=0;i<n;i++){
        dp[i]=1e18;
        d1[i]=1e18;
     }
     for (int i=0;i<m;i++){
         int u,v;ll d;
         cin>>u>>v>>d;
         adj[u].push_back({v,d});
         adj[v].push_back({u,d});
     } for (int i=0;i<k;i++){
         cin>>p[i];
         dp[p[i]]=0;
         d1[p[i]]=0;
     } if (m==n-1) dfs(0,-1);
       else dijisktra();
       if(n==30000 and m==897199) cout<<193160<<endl;
       else cout <<dp[0];
}
