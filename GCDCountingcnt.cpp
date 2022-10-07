#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=2e5+5;
int p,k,n,mx_d,mx_a,cnt;
int trs[sz];
int a[sz];
int d[sz];
ll ans[sz];
int anc;
vector<int>adj[sz];
map<int,int>mp;
map<int,int>dp;
bool vis[sz];
int dfs(int u, int p) {
  trs[u] = 1;
  for(auto v : adj[u]) if(v != p and !vis[v]) {
        trs[u] += dfs(v, u);
    }
  return trs[u];
}
int centroid(int u, int p, int n) {
    for(auto v : adj[u]){
        if(v != p and !vis[v]) {
            if(trs[v] > n / 2){
                return centroid(v, u, n);
            }
        }
    }
    return u;
}
void path(int u,int p, int d){
    ans[d]++; mp[d]++;
    for(auto v:adj[u]){
        if(v==p or vis[v]) continue;
        path(v,u,__gcd(a[v],d));
    }
}
void build(int u,int p){
    int n=dfs(u,p);
    int c=centroid(u,p,n);
    vis[c]=1;
    mx_d=0;
    dp.clear();
    ans[a[c]]++;
    for(auto v:adj[c]){
        if(vis[v]) continue;
        mp.clear();
        path(v,c,__gcd(a[v],a[c]));
        for(auto &x:dp){
            for(auto &y:mp){
                int div=__gcd(x.first,y.first);
                ans[div]+=(ll) y.second*x.second;
            }
        }
        for(auto &y:mp) dp[y.first]+=y.second;
    }
     for(auto v:adj[c]){
         if(!vis[v]) build(v,c);
     }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mx_a=max(a[i],mx_a);
    }
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build(1,0);
    for(int i=1;i<=mx_a;i++){
        if(ans[i]) cout<<i<<' '<<ans[i]<<endl;
    }
}
