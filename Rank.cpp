#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+5;
int n,x,k,i,j,w,q,y,ans;
int cnt[sz];
int par[sz];
int vis[sz];
vector<ll>adj[sz];
void dfs(int u,int anc){
     vis[u]=1;
     if(u==anc){cnt[u]=1;return;}
     for(auto v:adj[u]){
           if(!vis[v]) dfs(v,anc);
     }
}
int main(){
    cin>>n>>k;
    for(int i=1;i<=k;i++){
         int a,b,sa,sb;cin>>a>>b>>sa>>sb;
         if(sa>sb) adj[a].push_back(b);
         else adj[b].push_back(a);
    }
    for(int i=1;i<=n;i++){
        for(int i=1;i<=n;i++) vis[i]=0;
        for(auto v:adj[i]){
            if(!vis[i]) dfs(v,i);
        }
    }
    for(int i=1;i<=n;i++){
        if(cnt[i]) ans++;
    }  cout<<ans<<endl;
} 
