#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
vector<ll>c[sz];
vector<ll>g(sz);
ll depth[sz];
vector<ll>ch;
const int s=1e9+7;
ll ans=0;
int e=0;
##idea:
#from an arbitiary node (call j) find the node farthest node of node j (call i)
#find the answer is the farthest node from node j 
void dfs(int node,int p,int depth){
     for (auto u:c[node]){
         if (u==p) continue;
         dfs(u,node,depth+1);
     }    
     if (depth>ans){
         e=node;
         ans=depth;
     };    
}   
int main(){
    int n;
    cin>>n;
    for (int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        c[u].push_back(v);
        c[v].push_back(u);
    } dfs(1,0,0);
      ans=0;
      dfs(e,0,0);
     cout <<ans;
}  