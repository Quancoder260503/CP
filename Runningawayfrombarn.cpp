#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<map>
#include<vector>
#include<utility>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
ll n,m,q,s,t,k,L;
ll up[17][sz];
ll val[sz];
ll d[sz];
ll timer=1;
ll ans[sz];
vector<array<ll,2>>adj[sz];
vector<ll>height[sz];
void dfs(int u){
    for(int i=1;i<=16;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v[1]==up[0][u]) continue;
        d[v[1]]=d[up[0][v[1]]=u]+1;
        val[v[1]]=v[0]+val[u];
        dfs(v[1]);
    }
}
int main(){
      cin>>n>>L;
      for(int i=2;i<=n;i++){
          ll u,v;cin>>u>>v;
          adj[i].push_back({v,u});
          adj[u].push_back({v,i});
      } 
        dfs(1);
        for(int i=1;i<=n;i++){
            int mx=i;
            for(int j=16;j>=0;j--){
                if(up[j][mx]!=0 and val[i]-val[up[j][mx]]<=L){
                    mx=up[j][mx];
                }
            }ans[i]++;
             ans[up[0][mx]]--;
        }
        for(int i=n;i>=1;i--) ans[up[0][i]]+=ans[i];
        for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
}