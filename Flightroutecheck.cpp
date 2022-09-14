#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
vector<ll>c[sz];
vector<ll>c1[sz];
bool visited[sz];
void dfs(int node){
    visited[node]=true;
    for (auto u:c[node]){
        if (!visited[u]){
            dfs(u);
        }
    }  
}
void dfs1(int node){
     visited[node]=true;
    for (auto u:c1[node]){
        if (!visited[u]){
            dfs1(u);
        }
    }
}
int main(){
   int n,m;cin>>n>>m;
   for (int i=0;i<m;i++){
       int u,v;
       cin>>u>>v;
       c[u].push_back(v);
       c1[v].push_back(u);
   } dfs1(1);
    for (int i=2;i<=n;i++){
        if (!visited[i]){
            cout <<"NO"<<endl;
            cout <<i<<" "<<1;
            exit(0);
        }
    } for (int i=1;i<=n;i++){
        visited[i]=0;
    } dfs(1);
    for (int i=2;i<=n;i++){
        if (!visited[i]){
            cout <<"NO"<<endl;
            cout <<1<<" "<<i;
            exit(0);
        }
    } cout <<"YES";
} 