#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
ll corx[sz];
ll cory[sz];
ll s[sz];
bool visited[sz];
double dp[1001][1001];
int n;
void dfs(int node){
     visited[node]=true;
     for(int u=1;u<=n;u++){
          if (!visited[u]){
              if ( dp[node][u]<=s[node]){
                     dfs(u);
              }
          }  
     }
}
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        int u,v,t;
        cin>>u>>v>>t;
        corx[i]=u;
        cory[i]=v;
        s[i]=t;
    }for (int i=1;i<=n;i++){
         for (int j=1;j<=n;j++){
             dp[i][j]=hypot(corx[i]-corx[j],cory[i]-cory[j]);
         }
     } int ans=0;
    for (int i=1;i<=n;i++){
            dfs(i);
            int x=0;
            for (int i=1;i<=n;i++){
                if (visited[i]) x=x+1;
                 visited[i]=0;
            } ans=max(x,ans);
        }cout <<ans;
}  