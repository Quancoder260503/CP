#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
vector<pair<ll,int>>g[100005];
int n,m;
const int inf =1e16;
ll dis[100005];
void dijisktra(int src,vector<ll>&dis,vector<ll>&d){
    using T=pair<ll,int>;
    priority_queue<T,vector<T>,greater<T>>pq;
    dis[src]=0;
    d[src]=1;
    pq.push({0,src});
    while(!pq.empty()){
        int u=pq.top().second;
        ll val=pq.top().first;
        pq.pop();
        if (dis[u]!=val) continue;
        for (auto v:g[u]){
            int node=v.first;
            ll alt=v.second+val;
            if (src==node) continue;
            if (dis[node]==alt){
                d[node]+=d[u];
            }
            else if (dis[node]>alt){
                dis[node]=alt;
                d[node]=d[u];
                pq.push({alt,node});    
            }
       }
   } 
}
int main() {
    cin>>n>>m;
    for (int i=0;i<m;i++){
        int u,v;
        ll d;
        cin >>u>>v>>d;
        g[u].push_back({v,d});
        g[v].push_back({u,d});
    }
    const int inf=1e16;
    vector<ll>d1(n+1);vector<ll>d2(n+1);vector<ll>c1(n+1);vector<ll> c2(n+1);
    for(int i=1;i<=n;i++){
        d1[i]=inf;
        d2[i]=inf;
    }
    dijisktra(1,d1,c1);
    dijisktra(n,d2,c2);
    vector<ll>res;
    for (int i=2;i<n;i++){
        if (d1[i]+d2[i]!=d1[n] or c1[i]*c2[i]!=c1[n] ){
            res.push_back(i);
        }
    }  cout <<res.size()<<endl;
    for (int i:res){
            cout <<i<<endl;
     }
}
