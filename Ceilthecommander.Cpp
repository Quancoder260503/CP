#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=4e5+1;
const int sz1=1e6+900000;
const int mod = 1e9 + 7;
const int inf=1e7+5;
int n,m,k,t;
set<int>adj[sz];
int trs[sz];
char ans[sz];
int dfs(int u,int p){
    trs[u] = 1;
    for(auto v : adj[u]){
         if(v == p) continue; 
         trs[u] +=dfs(v,u);
    }
    return trs[u];
}
int centroid(int u,int p,int size){
    for(auto v: adj[u]){
         if(v == p) continue;
         if(trs[v] > size / 2) return centroid(v,u,size);
    }
    return u;
}
void dfs1(int u,int p,char ch = 'A'){
    int n = dfs(u,p);
    int c = centroid(u,p,n);
    if(p == -1) p = c;
    ans[c] = ch;
    vector<int>tmp(adj[c].begin(),adj[c].end());
    for(auto v:tmp){
        adj[c].erase(v);adj[v].erase(c);
        dfs1(v,c,ch + 1);
    }
}
int main(){
      scanf("%d",&n); 
      for(int i = 1; i < n; i++){           
            int u,v; scanf("%d%d",&u,&v);
            adj[u].insert(v);
            adj[v].insert(u);
      }      
      dfs1(1,0);
      for(int i = 1; i <= n; i++) cout<<ans[i]<<' ';
}
