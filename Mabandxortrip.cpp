#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
ll n,q,l,r;
ll timer=1;
int a[sz];
int arr[sz][20];
ll dp[sz][20][2];
ll res[sz];
ll ans[sz][20][2];
vector<int>adj[sz];
void dfs(int u,int p){
    for(int i=0;i<20;i++) dp[u][i][arr[u][i]]=1;
    for(auto v:adj[u]){
        if(v==p) continue;
        dfs(v,u);
        for(int i=0;i<20;i++){
            if(!arr[u][i]){
                dp[u][i][0]+=(dp[v][i][0]);
                dp[u][i][1]+=(dp[v][i][1]); 
           }
           else{
                dp[u][i][0]+=(dp[v][i][1]);
                dp[u][i][1]+=(dp[v][i][0]);
            }
        }
    }
}
void dfs2(int u,int p){ 
    for(auto v:adj[u]){
        if(v==p) continue;
        dfs2(v,u);
        res[u]+=res[v];
    }
    for (int i=0;i<20;i++){
        ll mul=0; ll add0=0; ll add1=0;
        ll sadd0=0;ll sadd1=0;
        for(auto v:adj[u]){
            if(v==p) continue;
            mul+=(ll) (dp[v][i][0]*dp[v][i][1]);
            sadd0+=dp[v][i][0]*dp[v][i][0];
            sadd1+=dp[v][i][1]*dp[v][i][1];
            add0+=dp[v][i][0]; add1+=dp[v][i][1];
            
        }
        if(arr[u][i]) ans[u][i][1]+=((ll) add1*add1+add0*add0-sadd1-sadd0)/2;
        else ans[u][i][1]+=(ll) add0*add1-mul;
    } 
    for(int i=0;i<20;i++){
         res[u]+=(ll) (ans[u][i][1]+dp[u][i][1])*(1ll<<i);
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        for(int j=0;j<20;j++) arr[i][j]= (a[i]>>j)&1;
    }
 
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    dfs2(1,0);
    cout<<res[1]<<endl;
}