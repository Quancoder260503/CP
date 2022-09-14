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
ld pref[sz];
ll dp[sz];
ld a[sz];
const int s=1e9+7;
ld sum=0;
void dfs(int node,int p,ld d){
     int opt=-1;
     for (int u:c[node]){
         if (u==p) continue;
         dp[u]=dp[node]+1;
         if (node==1) dfs(u,node,d/pref[node]);
         else dfs(u,node,d/(pref[node]-1));
         opt=1;
     } if (opt==-1){
        sum+=dp[node]*d;
    }       
} 
int main(){
    int n;
    cin>>n;
    for (int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        pref[u]+=1.0;
        pref[v]+=1.0;
        c[u].push_back(v);
        c[v].push_back(u);
    } dfs(1,0,1.0);
     cout <<fixed<<setprecision(15)<<sum;
}  