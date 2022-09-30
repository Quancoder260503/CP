#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int mod=1e9+7;
int p,n,mx_d,q,k;
ll cur0,cur1,ans;
int trs[sz];
vector<array<ll,2>>adj[sz];
map<ll,ll>mp;
int dp[sz];
ll a[sz];
bool vis[sz];
int cnt[sz];
int d[sz];
int dfs(int u, int p) {
  trs[u] = 1;
  for(auto v : adj[u]) if(v[0] != p and !vis[v[0]]) {
        trs[u] += dfs(v[0], u);
    }
  return trs[u];
}
int centroid(int u, int p, int n) {
    for(auto v : adj[u]) 
        if(v[0] != p and !vis[v[0]]) {
          if(trs[v[0]] > n / 2) return centroid(v[0], u, n);
   }
  return u;
}
void path(int u,int p,bool c,ll d,ll depth=1){
    if(d>k) return;
    if(c){
        if(mp[d]==0) mp[d]=depth;
        else mp[d]=min(depth,mp[d]);
    }
    else{
        if(k==d) ans=min(ans,depth);
        else if(mp[k-d]!=0) ans=min(ans,mp[k-d]+depth);
    }
    for(auto v:adj[u]){
        if(v[0]==p or vis[v[0]]) continue;
        path(v[0],u,c,d+v[1],depth+1);
    }
}
void build(int u,int p){
    int n=dfs(u,p);
    int c=centroid(u,p,n);
    vis[c]=1;
    for(auto v:adj[c]){
         if(vis[v[0]]) continue;
         path(v[0],c,0,v[1]);
         path(v[0],c,1,v[1]);
    } 
    mp.clear();
    mp[0]=1;
    for(auto v:adj[c]){
        if(!vis[v[0]]) build(v[0],c);
    }
} 
int main(){
    cin>>n>>k;
    ans=LLONG_MAX;
    for(int i=1;i<n;i++){
        int u,v,w;cin>>u>>v>>w;
        ++u;++v;
        adj[v].push_back({u,w});
        adj[u].push_back({v,w});
    }
    build(1,0);
    if(ans!=LLONG_MAX) cout<<ans<<endl;
    else cout<<-1<<endl;
}

