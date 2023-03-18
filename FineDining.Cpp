#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
vector<pair<int,int>>g[100005];
void dijisktra(int src , vector<ll>&dis){
    using Q=pair<int,ll>;
    priority_queue<Q,vector<Q>,greater<Q>>q;
    dis[src]=0;
    q.push({0,src});
    while (!q.empty()){
        int node=q.top().second;
        ll value=q.top().first;
        q.pop();
        if (dis[node]!=value) continue;
        for (pair<ll,ll> u:g[node]){
            if (u.second+value<dis[u.first]){
                dis[u.first]=value+u.second;
                q.push({dis[u.first],u.first});
            }
        }
    }
}
int main() {
    int n,m,k;
    cin>>n>>m>>k;
    for (ll i=0;i<m;i++){
        int u,v;
        ll d;
        cin>>u>>v>>d;
        g[u].push_back({v,d});
        g[v].push_back({u,d});
    } vector<ll>dis(n+1,LLONG_MAX);
      dijisktra(n,dis);
      for (int i=0;i<k;i++){
          int s,y;
          cin>>s>>y;
          g[n+1].push_back({s,dis[s]-y});
      } vector<ll>dis1(n+2,LLONG_MAX);
        dijisktra(n+1,dis1);
        for (int i=1;i<n;i++){
            if (dis[i]>=dis1[i]){
                cout <<1<<endl;
            }else{
                cout <<0<<endl;
            }
        }
  }
  
