#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
vector<tuple<int,int,ll>>edge;
ll trace[100005];
ll dis[100005];
int main(){
    int n,m;
    cin>>n>>m;
    for (int i=0;i<m;i++){
        int u,v,d;
        cin>>u>>v>>d;
        edge.push_back({u,v,d});
    }
    const ll inf =1e18;
    for (int i=2;i<=n;i++){
        dis[i]=inf;
    } int neg;
    for (int i=1;i<=n;i++){
       neg=-1;
       for (auto e:edge){
            int u;int v; int val;
            tie(u,v,val)=e;
            if (dis[u]+val<dis[v]){
                  dis[v]=val+dis[u];
                  trace[v]=u;
                  neg=v;
              }
    } 
  }if (neg==-1){
       cout <<"NO";
  }else{
    cout <<"YES"<<endl;
    for (int i=1;i<=n;i++){
        neg=trace[neg];
    } vector<ll>res{trace[neg]};
    while (res.back()!=neg){
        res.push_back(trace[res.back()]);
    } res.push_back(res[0]);
        reverse(res.begin(),res.end());
     for (int i:res){
         cout <<i<<" ";
  }
 }       
} 