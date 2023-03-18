#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
int main() {
     int n;
    ll m,q;
    cin>>n>>m>>q;
    ll dp[1005][1005];
    for (int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if (i!=j){
            dp[i][j]=1e18;
        }
       }     
    }
    for (int i=0;i<m;i++){
        int u,v;
        ll d;
        cin>>u>>v>>d;
        dp[u][v]=min(d,dp[u][v]);
        dp[v][u]=dp[u][v];
    }for (int k=1;k<=n;k++){
       for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
                dp[i][j]=min(dp[i][k]+dp[k][j],dp[i][j]);
                dp[j][i]=dp[i][j];         
            }
        }
    } 
    for (int i=0;i<q;i++){
        int u,v;
        cin>>u>>v;
        if (dp[u][v]==1e18){
            cout<<-1<<endl;
        } else{
            cout <<dp[u][v]<<endl;
        }
    }
