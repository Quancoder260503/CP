#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
vector<ll>g[100005];
vector<ll>g1[100005];
bool visited[100005];
void dfs1(int node){
    for (auto u:g[node]){
        visited[node]=true;
        if (!visited[u]){
          dfs1(u);  
        }
    }
}
void dfs2(int node){
    for(auto u:g1[node]){
        visited[node]=true;
        if (!visited[u]){
            dfs2(u);
        }
    }
}
int main(){
    int n,m;
    cin>>n>>m; 
    bool k=true;
    for (int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g1[v].push_back(v);
    } dfs1(1);
    visited[1]=true;
    for (int i=1;i<=n;i++){
        if (!visited[i]){
            cout <<"NO"<<endl;
            cout <<i<<" "<<1;
            k=false;
            exit(0);
        }
    }
    fill_n(visited,n+1,0);
    visited[1]=true;
    for (int i=1;i<=n;i++){
        if (!visited[i]){
            k=false;
            cout <<"NO"<<endl;
            cout <<1<<" "<< i;
            exit(0);
        }
    }
    if (k){
        cout<<"YES";
    }
}