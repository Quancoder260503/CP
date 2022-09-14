#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
vector<ll>c[sz];
ll dp[sz][2];
const int s=1e9+7;
# find a,b (the diameter of the tree)
# denote dp[i][0] as the distance from ith node to A and dp[i][1] as the distance from ith node to B
# the ansewer of ith node is the max between dp[i][0] and dp[i][1];
int dfs(int node,int p,int d,int i){
    dp[node][i]=d;
    int opt=-1;
    for (int u:c[node]){
        if (u==p) continue;
        int x=dfs(u,node,d+1,i);
        if (opt==-1 or dp[opt][i]<dp[x][i]) opt=x;
    } if (opt==-1) return node;
    else return opt;
}
int main(){
   int n;
    cin>>n;
    for (int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        c[u].push_back(v);
        c[v].push_back(u);
    } int node=dfs(1,0,0,0);
      int nodeA=dfs(node,0,0,0);
      dfs(nodeA,0,0,1);
      for (int i=1;i<=n;i++){
          cout <<max(dp[i][0],dp[i][1])<<" ";
      }
}    