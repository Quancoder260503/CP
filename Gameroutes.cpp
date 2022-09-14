#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
vector<ll>g[100010];
ll d[100010];
ll indegree[100010];
bool visited[100010];
vector<ll>tps;
const int s=1e9+7;
void dfs(int node){
     visited[node]=true;
     for (auto u:g[node]){
         d[u]=(d[node]+d[u])%s;
         indegree[u]--;
         if (indegree[u]==0){
             dfs(u);
         }
     }
}   
int main(){
    int n,m;
    cin>>n>>m;
    for (int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        indegree[v]++;
    }
    d[1]=1;
    for (int i=1;i<=n;i++){
        if (!visited[i] and indegree[i]==0){
            dfs(i);
        }
    } cout <<d[n]%s;
}