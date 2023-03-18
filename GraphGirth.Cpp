#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2501;
vector<ll>adj[sz];
int n,m;
ll d[sz];
ll d1[sz];
ll ans;
ll bfs(int src){
    for(int i=1;i<=n;i++){
        d[i]=d1[i]=LLONG_MAX;
    }
    queue<int>q;
    q.push(src);
    d[src]=0;
    ans=LLONG_MAX;
    while (q.size()){
        int v=q.front();
        q.pop();
        for(auto u:adj[v]){
            if(d[u]==LLONG_MAX){
                d[u]=d[v]+1;
                q.push(u);
            } 
            else{
                if(d[v]-d[u]==1) continue;
                ans=min(ans,d[v]+d[u]+1-2*d[src]);
            }
        }
    } return ans;
}
int main(){
    cin>>n>>m;
    ll res=LLONG_MAX;
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    } for(int i=1;i<=n;i++){
        res=min(res,bfs(i));
    } if (res==LLONG_MAX) cout <<-1;
      else cout <<res;
}
