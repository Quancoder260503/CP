#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
bool on_stack[sz];
vector<ll>g[sz];
bool visited[sz];
int n,m;
void dfs(int node){
     visited[node]=true;
     for (int u:g[node]){
         if (on_stack[u]) continue;
         if (!visited[u]){
             dfs(u);
         }
     }
}
int connect(){
    int ans=0;
    for (int i=1;i<=n;i++){
        visited[i]=0;
    }
    for (int i=1;i<=n;i++){
        if (on_stack[i]) continue;
        if (!visited[i]){
            ans+=1;
            dfs(i);
        }
    } if (ans==1){
        return 1;
    }else {
        return 0;
    }
}    
int main(){
    cin>>n>>m;
    for (int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    } if (connect()) cout <<"YES"<<endl;
    for (int i=1;i<n;i++){
        int u;cin>>u;
        on_stack[u]=true;
        if (connect()) cout <<"YES"<<endl;
        else cout <<"NO"<<endl;
    }
 } 