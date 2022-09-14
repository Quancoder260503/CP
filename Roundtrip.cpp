#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
vector<ll>g[100005];
ll parent[100005];
bool visited[100005];
int sv=0;
int ev=0;

void dfs(int node,int p){
    visited[node]=1;
    parent[node]=p;
    for (int u:g[node]){
        if (u==p) continue;
        if (!visited[u]){
            dfs(u,node);
        } else{
             if (parent[u]!=node){
                sv=node;
                ev=u;
            } 
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
        g[v].push_back(u);
    } for (int i=1;i<=n;i++){
        if (!visited[i]){
            dfs(i,1);
        }
    }
    if (sv==0){
        cout <<"IMPOSSIBLE";
    } else{
        vector<ll>res;
        res.push_back(sv);
        res.push_back(ev);
        while (res.back()!=sv){
            res.push_back(parent[res.back()]);
        }  cout <<res.size()<<endl;
        for (int i=0;i<res.size();i++){
              cout <<res[i]<<" ";
        }
    }
}