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
bool onstack[100005];
vector<ll>res;
void dfs(int node){
    visited[node]=true;
    onstack[node]=true;
    for (int u:g[node]){
        if (onstack[u]){
            vector<ll>res;
            res.push_back(node);
            while (res.back()!=u){
                    res.push_back(parent[res.back()]);
          } 
        res.push_back(node);
        cout<<res.size()<<endl;
        reverse(res.begin(),res.end());
        for (int i:res){
            cout <<i<<" ";
        } exit(0);
     }     
       else{
           if (!visited[u]){
              parent[u]=node;
              dfs(u);
          } 
      } 
   } onstack[node]=false;
}
int main(){
    int n,m;
    cin>>n>>m;
    for (int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
    } for (int i=1;i<=n;i++){
        if (!visited[i]){
            dfs(i);
        }      
    } cout <<"IMPOSSIBLE";
 }
