#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
int n,m,b,e,p;
const int sz=4e4+1;
vector<int>g[sz];
experience: doesnt always need to think how to track the road :(((
we only need to comppute the shortest road so if an arbitiary x is not a meet point than simply that 
the formula are greater (doesnt need to be consider) 
vector<ll>bfs(int src){
    vector<ll>dis(n+1,LLONG_MAX);
    dis[src]=0;
    queue<int>q;
    q.push(src);
    while (q.size()){
        int u=q.front();
        q.pop();
        for (auto v:g[u]){
            if (dis[v]!=LLONG_MAX) continue;
            dis[v]=dis[u]+1;
            q.push(v);
        }
    } return dis;
}
int main(){
    cin>>b>>e>>p>>n>>m;
    for (int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    } vector<ll>d1=bfs(1);
      vector<ll>d2=bfs(2);
      vector<ll>dn=bfs(n);
      ll ans=LLONG_MAX;
      for (int i=1;i<=n;i++){
          ans=min(ans,d1[i]*b+d2[i]*e+dn[i]*p);
      } cout <<ans;
}
