#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
typedef long long ll;
const int sz=2e5+1;
int p,k,n,mx_d;
ll ans;
int trs[sz];
int cnt[sz];
std::vector<int>adj[sz];
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
void path(int u,int p,bool t, int d=1){
    if(d>k) return;
    mx_d=std::max(mx_d,d);
    if(t) cnt[d]++;
    else ans+=cnt[k-d];
    for(auto v:adj[u]){
        if(v==p or vis[v]) continue;
        path(v,u,t,d+1);
    }
}
void build(int u,int p){
    int n=dfs(u,p);
    int c=centroid(u,p,n);
    vis[c]=1;
    mx_d=0;
    for(auto v:adj[c]){
        if(vis[v]) continue;
        path(v,c,0);
        path(v,c,1);
    }
     std::fill(cnt+1,cnt+mx_d+1,0);
     for(auto v:adj[c]){
         if(!vis[v]) build(v,c);
     }
}
int main(){
     std::cin>>n>>k;
     for(int i=1;i<n;i++){
         int u,v;
         std::cin>>u>>v;
         adj[u].push_back(v);
         adj[v].push_back(u);
     }
     cnt[0]=1;
     build(1,0);
     std::cout<<ans<<std::endl;
}
