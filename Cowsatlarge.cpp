#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
int n,k;
const int sz=1e5+1;
vector<int>g[sz];
ll d[sz];
ll par[sz];
bool pass[sz];
vector<int>leafs;
bool visited[sz];
vector<int>path;
bool flag;
vector<ll> bfs(vector<int>a){
    vector<ll>d(n+1,LLONG_MAX);
    queue<int>q;
    for (auto i:a){
        d[i]=0;
        q.push(i);
    }
    while (q.size()){
     int v=q.front();
     q.pop();
     for (auto u:g[v]){
        if (d[u]!=LLONG_MAX) continue;
        par[u]=v;
        d[u]=d[v]+1;
        q.push(u);
      } 
   } return d;    
}
int main(){
    cin>>n>>k;
    for (int i=1;i<=n;i++){
        d[i]=LLONG_MAX;
    }
    vector<int>a;
    a.push_back(k);
    for (int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    } vector<ll>d1=bfs(a);
    a.clear();
    for (int i=1;i<=n;i++){
        if (g[i].size()==1){
            a.push_back(i);
        } 
    }vector<ll>d2=bfs(a);
     queue<int>q;
     q.push(k);
     int ans=0;
     while(q.size()){
         int cur=q.front();
         q.pop();
         if (d1[cur]>=d2[cur]){
             ans++;
             continue;
         }
       if (visited[cur]) continue;
       visited[cur]=1;
       for (auto u:g[cur]){
           q.push(u);
      }
   } cout <<ans; 
} 
