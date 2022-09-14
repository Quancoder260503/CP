#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=5001;
bool on_stack[sz];
vector<pair<int,ll>>g[sz];
ll par[sz];
int n,m,sum,k;
ll visited[sz];
void dfs(int node){
    visited[node]=true;
    for (auto u:g[node]){
        int v=u.first;
        ll z=u.second;
        if (visited[v]) continue;
        if (z>=k){
            sum++;
            dfs(v);
        }
    }    
} 
int main(){
   int n,m;
   cin>>n>>m;
   for (int i=0;i<n-1;i++){
      int u,v;
       ll d;
      cin>>u>>v>>d;
      g[u].push_back({v,d});
      g[v].push_back({u,d});
   } for (int i=0;i<m;i++){
       sum=0;
       for (int i=1;i<=n;i++){
           visited[i]=0;
       }
       int v;
       cin>>k>>v;
       dfs(v);
       cout <<sum<<endl;
   }
 