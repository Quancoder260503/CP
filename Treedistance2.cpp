#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
vector<ll>c[sz];
ll dp[sz];
ll res[sz];
ll sub_size[sz];
const int s=1e9+7;
int n;
##compute the subsize of the child node(every time we get a new root , the distance from the new root to every node in the subtree will be incremented by one)
## the sum of distance will be equal to sum of the subsize of the children and the sum of the distance of children node.
## everytime we rerooting , note that the distance from the original root to the new root will be abandoned, so that we have to minus the result of the current root by the
sum of the next root and plus (n-subsize of the node) as the distance from the new root to the children of the current root will be incremented by one;
void dfs(int node,int p){
    sub_size[node]=1;
    for (int u:c[node]){
        if (u==p) continue;
        dfs(u,node);
        sub_size[node]+=sub_size[u];
        dp[node]=dp[u]+sub_size[u]+dp[node];
    }    
}
void dfs1(int node, int p){
    res[node]=res[p]-sub_size[node]+n-sub_size[node];
    if (node==1) res[node]=dp[1];
    for(int u:c[node]){
        if (u==p) continue;
        dfs1(u,node);
    }
}
int main(){
    cin>>n;
    for (int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        c[u].push_back(v);
        c[v].push_back(u);
    } dfs(1,0); 
      dfs1(1,0);
      for(int i=1;i<=n;i++){
         cout <<res[i]<<" ";
     }
}   