#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=5e4+1;
const int mod=998244353;
int n,x,k,i,j,w,q,m;
ll a[sz];
vector<array<ll,2>>up[17][sz];
ll dp[17][sz][6];
vector<ll>oc;
vector<array<ll,2>>node;
ll xval[6];
void push(){
     for(int i=1;i<=16;i++){
        for(int j=0;j<=n;j++){
            oc.clear(); int cnt=0;
            for(auto t:up[i-1][j]){
                for(auto u:up[i-1][t[0]]){
                      auto it=find(oc.begin(),oc.end(),u[0]);
                      int v=it-oc.begin();
                      if(it==oc.end()){
                          dp[i][j][cnt]=t[1]+u[1];
                          cnt++;
                          oc.push_back(u[0]);
                      } else {
                          dp[i][j][v]=min(t[1]+u[1],dp[i][j][v]);
                      }
                  }
            } 
            for(auto v:oc){
                auto it=find(oc.begin(),oc.end(),v);
                int x=it-oc.begin();
                up[i][j].push_back({v,dp[i][j][x]});
           } 
       }
   }
}    
ll jump(int x,int y,int d){
    ll res=LLONG_MAX;
    node.clear();
    oc.clear();
    node.push_back({x,0});
    for(int i=16;i>=0;i--){
        if(d>>i&1){
            oc.clear(); int cnt=0;
            for(auto u:node){
               for(auto v:up[i][u[0]]){
                   auto it=find(oc.begin(),oc.end(),v[0]);
                   int v0=it-oc.begin();
                   if(it==oc.end()){
                       xval[cnt]=v[1]+u[1];
                       cnt++;
                       oc.push_back(v[0]);
                   } else xval[v0]=min(xval[v0],v[1]+u[1]);
               } 
            } 
              node.clear();
              for(auto v:oc){
                  auto it=find(oc.begin(),oc.end(),v);
                  int x=it-oc.begin();
                  node.push_back({v,xval[x]});
              }
         }
    } 
     for(auto v:node){
        if(v[0]==y) res=min(res,v[1]);
    } return res;
}
int main(){
     cin>>k>>n>>m>>q;
     for(int i=0;i<m;i++){
         ll u,v,w; cin>>u>>v>>w;
         if(u>v) swap(u,v);
         if((u/k)+1==(v/k)){
             up[0][u].push_back({v,w});
          }
     } 
       push();
       for(int i=0;i<q;i++){
           ll u,v;cin>>u>>v;
           ll x=(v/k)-(u/k);
           if(x==0) {cout<<-1<<endl;continue;}
           ll res=jump(u,v,x);
           if(res==LLONG_MAX) cout<<-1<<endl;
           else cout<<res<<endl;
       }
}

