#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
const int inf=1e7+1;
int n,m,k;
vector<int>dpl;
vector<int>dpr;
vector<array<int,2>>ap;
vector<int>adj[sz];
int p[sz];
void bfs(int src, vector<int>&dp){
     queue<int>q;
     q.push(src);
     dp[src]=0;
     while (q.size()){
         int u=q.front();
         q.pop();
         for(int i=0;i<adj[u].size();i++){
              int v=adj[u][i];
              if(dp[v]>dp[u]+1){
                   dp[v]=dp[u]+1;
                   q.push(v);
              }
         }
     }
}
int main(){
     cin>>n>>m>>k;
     for(int i=1;i<=k;i++) cin>>p[i];
     for(int i=1;i<=m;i++){
          int u,v; cin>>u>>v;
          adj[u].push_back(v);
          adj[v].push_back(u);
     }
     dpl.resize(n+1);
     dpr.resize(n+1);
     for(int i=1;i<=n;i++) dpl[i]=dpr[i]=inf;
     bfs(1,dpl);
     bfs(n,dpr);
     for(int i=1;i<=k;i++){
         int idx=p[i];
         ap.push_back({dpl[idx]-dpr[idx],p[i]});
     }
     sort(ap.begin(),ap.end());
     int ans=-inf;
     int cur_mx=-inf;
     for(int i=ap.size()-1;i>=0;i--){
          int idx=ap[i][1];
          ans=max(ans,dpl[idx]+cur_mx);
          cur_mx=max(cur_mx,dpr[idx]);
     }
     ans=min(ans+1,dpl[n]);
     cout<<ans<<endl;
}
