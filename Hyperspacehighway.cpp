#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=5e5+5;
int up[19][sz];
int dp[sz];
int a[sz];
int n,m,q;
vector<int>adj[sz];
vector<int>tadj[sz];
int trs,dsz,psz;
int st[sz],low[sz];
void dfs(int u,int p){
    a[u]=low[u]=++dsz;
    st[++psz]=u;
    for(int v:tadj[u]){
        if(v==p) continue;
        if(!a[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=a[u]){
                int j=u;
                trs++;
                adj[u].push_back(trs);
                adj[trs].push_back(u);
                while(j!=v){
                    j=st[psz--];
                    adj[trs].push_back(j);
                    adj[j].push_back(trs);
               } 
            }
        }
        else low[u]=min(a[v],low[u]);
    }
}
void dfs_calc(int u){
    for(int i=1;i<=18;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(int v:adj[u]){
        if(v==up[0][u]) continue;
        dp[v]=dp[up[0][v]=u]+1;
        dfs_calc(v);
    }
}
int lca(int a, int b){
    if(dp[a]<dp[b]) swap(a,b);
    int d=dp[a]-dp[b];
    for(int i=0;i<=18;i++){
        if((d>>i)&1) a=up[i][a];
    }
    if(a==b) return a;
    for(int i=18;i>=0;i--){
         int tA=up[i][a]; int tB=up[i][b];
         if(tA!=tB) {a=tA; b=tB;}
    } return up[0][a];
}   
int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++){
        int u,v; cin>>u>>v;
        tadj[u].push_back(v);
        tadj[v].push_back(u);
    }
    trs=n;
    dfs(1,0);
    dfs_calc(1);
    for(int i=1;i<=q;i++){
        int u,v; cin>>u>>v;
        int res=(dp[u]+dp[v]-2*dp[lca(u,v)])/2;
        cout<<res<<endl;
    }
}