#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+5;
ll n,k,m,q,T,p,start,cnt,res;
ll timer=1;
int compsz[sz];
int par[sz];
int ans[sz];
vector<ll>to1;
ll a[sz];
vector<array<ll,2>>dp[sz];
vector<ll>adj[sz];
void dfs(int u,int p){
    vector<array<ll,2>>child;
    for(auto v:adj[u]){
        if(v==p) continue;
        dfs(v,u);
        for(auto it:dp[v]) child.push_back(it);
    }
    sort(child.begin(),child.end());
    for(int i=0;i<child.size();i++){
        int j=i-1;
        ll dis=0; ll dis1=0;
        while(j+1<child.size() and child[i][0]==child[j+1][0]){ 
             j++;
             if(child[j][1]>=dis){
                dis1=dis;
                dis=child[j][1];
            }
            else if(child[j][1]>=dis1) dis1=child[j][1];
        }
        if(a[u]%child[j][0]==0){
            res=max(res,dis+dis1+1);
            dp[u].push_back({child[j][0],dis+1});
            while(a[u]%child[j][0]==0){
                a[u]/=child[j][0];
            }
        } else res=max(res,dis);
         i=j;
    }
    for(int i=2;i*i<=a[u];i++){
         if(a[u]%i==0){
             dp[u].push_back({i,1});
             res=max(res,timer);
             while(a[u]%i==0) a[u]/=i;
         }
     }
     if(a[u]>1){
         res=max(res,timer);
         dp[u].push_back({a[u],1});
     }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++){
        ll u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    cout<<res<<endl;
}