#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int inf=1e7+5;
int n,m,src,d,cnt,ans;
int a[sz];
vector<int>adj[sz];
vector<int>adj1[sz];
bool vis[sz];
int at[sz];
int to[sz];
int dp[sz];
int trs[sz];
void dfs(int u,int p){
     trs[u]=1;
     for(int i=0;i<adj[u].size();i++){
          int v=adj[u][i];
          if(v==p) continue;
          dfs(v,u);
          trs[u]+=trs[v];
     }
}
int centroid(int u,int p){
     for(int i=0;i<adj[u].size();i++){
          int v = adj[u][i];
          if(v==p) continue;
          if( trs[v]*2 > n ) return centroid(v,u);
     }
     return u;
}
void dfs1(int u,int p){
     int cnt = 0; 
     queue<int>q;
     queue<int>qe;
     for(int i=0;i<adj[u].size();i++){
          int v = adj[u][i];
          if (v == p) continue;
          dfs1(v,u);
     }
     for(int i=0;i<adj[u].size();i++){
          int v=adj[u][i];
          if(v==p) continue;
          if(dp[v]%2 == 0) qe.push(v); 
          if(to[v]) q.push(v);
     }
     while (q.size()){
          int v=q.front();
          q.pop();
          auto it=find(adj[u].begin(),adj[u].end(),v);
          adj[u].erase(it);
     }
     for(int i = 0; i < adj[u].size(); i++){
          int v = adj[u][i];
          if(v==p) continue;
          if(adj[v].size()==1) q.push(v),ans+=2;
     }
     if(q.size()){
        to[u]=q.front();
        at[to[u]]=u;
        int cur=to[u];
        q.pop();
        q.push(u);
        while(q.size()){
             int  v = q.front(); to[cur]=v;
             at[v]=cur;
             cur=v; 
             q.pop();
        }
     }
}
int main(){
      cin>>n;
      for(int i=1;i<n;i++){
           int u,v; cin>>u>>v;
           adj1[u].push_back(v);
           adj1[v].push_back(u);
           adj[u].push_back(v);
           adj[v].push_back(u);
      }
      dfs(1,0);
      int c=centroid(1,0);
      dfs1(c,0);
      int l = 0;
      for(int i=1;i<=n;i++){
           if(!to[i]){
              l=i;
              ans+=2;
           }
      }
      if(adj1[l].size()>0){
          to[l]=adj1[l][0];
          int r=at[adj1[l][0]];
          to[r]=l;
      }
      cout<<ans<<endl;
      for(int i=1;i<=n;i++) cout<<to[i]<<' ';
} 
