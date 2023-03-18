#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
int n,m,k;
vector<tuple<ll,int,ll>>g[100005];
const int inf =1e9;
void setup(){
    cin>>k;
    cin>>n;
    cin>>m;
    for (int i=1;i<=n;i++){
        g[i].clear();
    }
    for (int i=0;i<m;i++){
        int u,v;
        ll t,d;
        cin>>u>>v>>d>>t;
        g[u].push_back({v,d,t}); 
    }
}
int dijisktra(int src,int k,int n){
    vector<vector<ll>>dis(n+1,vector<ll>(k+1,inf));
    using Q=tuple<ll,int,ll>;
    priority_queue<Q,vector<Q>,greater<Q>>q;
    dis[src][0]=0;
    q.push({0,src,0});
    while (!q.empty()){
        int node;ll d;ll cost;
        tie(d,node,cost)=q.top();
        q.pop();
        if (node==n) return d;
        if (dis[node][cost]!=d) continue;
        for (auto u:g[node]){
              ll j;ll dist;int v;
              tie(v,dist,j)=u;
              if (cost+j>k) continue;
              if (dis[v][cost+j]>dis[node][cost]+dist){
                 q.push({dis[v][cost+j]=dis[node][cost]+dist,v,cost+j});
             }
          }
    } return -1;
}
int main() {
   int T;
   cin>>T;
    while(T--){
        setup();
        cout <<dijisktra(1,k,n)<<endl;
    }
    return 0;
}
