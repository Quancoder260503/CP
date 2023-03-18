#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<queue>
#include<utility>                                                                                                   
using namespace std;
typedef long long ll;
const int inf=1e16;
int main(){
    ll dp[1005][1005];
    int n,m,c;
    cin>>n>>m>>c;
    vector<ll>sl(m);
    for (int i=0;i<m;i++){
        int v;cin>>v;
        sl.push_back(v);
    }for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            if (i==j) dp[i][j]=0;
            else dp[i][j]=inf;
        }
    } 
    for (int i=0;i<c;i++){
        int u,v,d;
        cin>>u>>v>>d;
        dp[u][v]=d;
        dp[v][u]=dp[u][v];
    } for (int k=1;k<=n;k++){
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++){
               dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
               dp[j][i]=dp[i][j];
            }
        }
    } double ans=inf;
      int node=0;
    for (int i=1;i<=n;i++){
        double sum=0;
        for (int v:sl){
            sum+=dp[i][v];
        } sum=double(sum)/double(m);
        if (sum<ans){
            ans=sum;
            node=i;
        }
   } cout <<node;
