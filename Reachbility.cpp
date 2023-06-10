#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=5e3+1;
const int inf=1e7+5;
int n,m,src,d,cnt;
int a[sz];
bool vis[sz];
vector<int>adj[sz];
vector<array<int,2>>arr;
bool vis1[sz];
void dfs(int u){
     vis[u]=1;
     for(auto v:adj[u]){
         if(vis[v]) continue;
         dfs(v);
     }
}
void dfs1(int u){
     vis1[u]=1;
     cnt++;
     for(auto v:adj[u]){
         if(vis[v] or vis1[v]) continue;
         dfs1(v);
     }
}
int main(){
     cin>>n>>m>>src;
     for(int i=1;i<=m;i++){
          int u,v; cin>>u>>v;
          adj[u].push_back(v);
     }
     dfs(src);
     for(int i=1;i<=n;i++){
          if(vis[i]) continue;
          for(int j=1;j<=n;j++) vis1[j]=0;
          dfs1(i);
          arr.push_back({cnt,i});
          cnt=0;
     }
     sort(arr.rbegin(),arr.rend()); 
     memset(vis1,0,sizeof(vis1));
     int ans=0;
     for(int i=0;i<arr.size();i++){
          int v=arr[i][1];
          if(!vis1[v]){
              //cout<<v<<endl;
              dfs1(v),ans++;
          }
     }
     cout<<ans<<endl;
}
