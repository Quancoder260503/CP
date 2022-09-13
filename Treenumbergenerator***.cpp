#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
int n,x,k,i,q,j,w,m,mod;
ll num[sz];
ll up[19][sz];
ll val[19][sz];
ll vald[19][sz];
ll dp[sz];
ll mul[sz];
vector<ll>adj[sz];
int timer=1; 
int jump(int x,int d){
    for(int i=0;i<=18;i++){
        if((d>>i)&1) x=up[i][x];
    }
    return x;
}
void dfs(int u){
    for(int i=1;i<=18;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v==up[0][u]) continue;
        dp[v]=dp[up[0][v]=u]+1;
        val[0][v]=vald[0][v]=num[u];
        dfs(v);
    }
}
int lca(int a ,int b){
    if(dp[a]<dp[b]) swap(a,b);
    a=jump(a,dp[a]-dp[b]);
    if(a==b) return a;
    for(int i=18;i>=0;i--){
        int ta=up[i][a]; int tb=up[i][b];
        if(ta!=tb) a=ta,b=tb;
    } return up[0][a];
}
void push(){
    for(int i=1;i<=18;i++){
        for(int j=1;j<=n;j++){
            val[i][j]=(val[i-1][j]*mul[(1<<(i-1))]%mod+val[i-1][up[i-1][j]])%mod;
            vald[i][j]=(vald[i-1][j]+vald[i-1][up[i-1][j]]*mul[1<<(i-1)]%mod)%mod;
        }
    }
}
ll jumpup(int x, int d){
    ll ans=0;
    for(int i=0;i<=18;i++){
        if((d>>i)&1){
            ans=ans%mod*mul[1<<i]%mod;
            ans=(ans+val[i][x])%mod;
            x=up[i][x];
        }
    }
    return ans;
}
ll jumpdown(int x, int d){
    ll ans=num[x];
    ll prevbit=1;
    for(int i=0;i<=18;i++){
        if((d>>i)&1){
            ans=(ans+vald[i][x]*mul[prevbit]%mod)%mod;
            prevbit+=(1<<i);
            x=up[i][x];
        }
    }
    return ans;
}
int main(){
    cin>>n>>mod>>q;
    for(int i=0;i<n-1;i++){
         ll u,v;cin>>u>>v;
         adj[v].push_back(u);
         adj[u].push_back(v);
    }
    mul[0]=1;
    for(int i=1;i<=n;i++){
        mul[i]=((ll) mul[i-1]*10)%mod;
    }
    for(int i=1;i<=n;i++) cin>>num[i];
    up[0][1]=1;
    dfs(1); 
    push();
    for(int i=1;i<=q;i++){
        ll u,v;cin>>u>>v;
        int anc=lca(u,v);
        int ancv=jump(v,dp[v]-dp[anc]-1);
        ll res=0;
        ll  go_up=(num[u]*mul[dp[u]-dp[anc]])%mod;
        if(v!=anc and u!=anc){
            res=(res+go_up+jumpup(u,dp[u]-dp[anc]))%mod;
            res=res%mod*mul[dp[v]-dp[anc]]%mod;
            res=(res+jumpdown(v,dp[v]-dp[ancv]))%mod;
        }
        else if(u==anc) res=jumpdown(v,dp[v]-dp[anc])%mod;
        else if(v==anc) res=(go_up+jumpup(u,dp[u]-dp[anc]))%mod;
        cout<<res<<endl;
    }
}
