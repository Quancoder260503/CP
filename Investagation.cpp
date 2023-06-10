#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long  ll;
vector<pair<int,ll>>g[100005];
ll cnt[100005];
ll maxs[100005];
ll mins[100005];
vector<ll> dis(100005);
const int s=1e9+7;
void dijisktra(int src){
    using Q=pair<ll,ll>;
    priority_queue<Q,vector<Q>,greater<Q>>q;
    cnt[src]=1;
    dis[src]=0;
    q.push({0,src});
    while (!q.empty()){
        int node=q.top().second;
        ll value=q.top().first;
        q.pop();
        if (dis[node]!=value) continue;
        for (auto u:g[node]){
             int node1=u.first;
             ll sums=u.second+value;
             if (sums==dis[node1]){
                 cnt[node1]=(cnt[node1]+cnt[node])%s;
                 mins[node1]=min(mins[node1],mins[node]+1);
                 maxs[node1]=max(maxs[node1],maxs[node]+1);
             } else if(sums<dis[node1]){
                 cnt[node1]=cnt[node];
                 maxs[node1]=maxs[node]+1;
                 mins[node1]=mins[node]+1;
                 q.push({dis[node1]=sums,node1});
             }
          }
       }
} 
int main() {
    ll n,m;
    cin>>n>>m;
    for (ll i=0;i<m;i++){
        int u,v;
        ll d;
        cin>>u>>v>>d;
        g[u].push_back({v,d});
    } 
    for (int i=2;i<=n;i++){
        dis[i]=LLONG_MAX;
    }
    dijisktra(1);
    cout <<dis[n]<<" "<<cnt[n]<<" "<<mins[n]<<" "<<maxs[n];
} 
