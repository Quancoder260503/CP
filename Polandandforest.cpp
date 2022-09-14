
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
ll sub_size[sz];
const int s=1e9+7;
int n;
bool visited[sz];
void dfs(int node,int p){
    visited[node]=true;
    for (int u:c[node]){
        if (u==p) continue;
        dfs(u,node);
    }
}   
int main(){
   int n;
    cin>>n;
    for (int i=1;i<=n;i++){
        int d;
        cin>>d;
        c[i].push_back(d);
        c[d].push_back(i);
    } ll ans=0;
    for(int i=1;i<=n;i++){
        if (!visited[i]){
            ans+=1;
            dfs(i,0);
        }
    } cout <<ans;
}  