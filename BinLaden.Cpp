#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
int n,m;
vector<pair<int,ll>>g[100005];
const int inf =1e9;
int  dijisktra(int src,int n,int m){
    vector<ll>dis((m+1)*n+1,inf);
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
    } ll ans=inf; 
    for (int i=1;i<=n;i++){
        ans=min(ans,dis[i]);
    } return ans;
}
int main() {
  int n,m;
    cin>>m>>n;
    int k=1;
    int comp=(m+1)*n;
    for (int i=0;i<2*m+1;i++){
            if (i%2==0){
            for (int j=0;j<n;j++){
                int d;cin>>d;
                  if (k+n>comp) continue;
                  g[k].push_back({k+n,d});
                  g[k+n].push_back({k,d});
                  k=k+1;
            } 
            }  else{
                int temp=k;
                for (int j=0;j<n-1;j++){
                int d;cin>>d;
                    g[k].push_back({k+1,d});
                    g[k+1].push_back({k,d});
                    k=k+1;
            }  k=temp;     
        }
     } cout <<dijisktra(comp,n,m);
  }  
