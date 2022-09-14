#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
ll corx[sz];
ll cory[sz];
vector<ll>g[sz];
bool visited[sz];
int n;
ll sx,sy,sx1,sy1;
void dfs(int node){
     visited[node]=true;
     for (int u:g[node]){
         if (!visited[u]){
             sx=min(sx,corx[u]);
             sy=min(sy,cory[u]);
             sx1=max(sx1,corx[u]);
             sy1=max(sy1,cory[u]);
             dfs(u);
         }
     }
}
int main(){
  int n,m;
    cin>>n>>m;
    for (int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        corx[i]=x;
        cory[i]=y;
    } for (int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    } ll ans=LLONG_MAX; 
    for (int i=1;i<=n;i++){
        if (!visited[i]){
            sx=corx[i];sy=cory[i];sx1=corx[i];sy1=cory[i];
            dfs(i); 
            if (sy1==sy and sx1==sx) continue;
            if  (sy1==sy) ans=min(ans,sx1);
            else if (sx1==sx) ans=min(ans,sy1);
            ll temp=(sy1-sy)+(sx1-sx);
            ans=min(ans,temp*2);
        }
    } cout <<ans;
}   