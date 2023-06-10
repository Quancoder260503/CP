#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e6+2;
int p,n,mx_d,q,anc,cur,timer;
int ans[sz];
int trs[sz];
vector<int>adj[sz];
set<pair<int,int>>s;
int dp[sz];
char a[sz];
bool vis[sz];
int cnt[sz];
int d[sz];
int st[sz],en[sz],to[sz];
void dfs(int u,int p){
    trs[u]=1;
    to[timer]=u;
    st[u]=timer++;
    for(auto v:adj[u]){
        if(v==p) continue;
        d[v]=d[u]+1;
        dfs(v,u);
        trs[u]+=trs[v];
    }
    en[u]=timer;
}
void dfs_hld(int u,int p,bool c){
    int mx=-1;
    int big=-1;
    for(auto v:adj[u]){
        if(v==p) continue;
        if(trs[v]>mx){
            mx=trs[v];
            big=v;
        }
    }
    for(auto v:adj[u]){
        if(v==p or v==big) continue;
        dfs_hld(v,u,0);
    }
    if(big!=-1) dfs_hld(big,u,1);
    for(auto v:adj[u]){
        if(v==p or v==big) continue;
        for(int i=st[v];i<en[v];i++){
             int x=d[to[i]];
             s.erase({-dp[x],x});
             dp[x]++;
             s.insert({-dp[x],x});
        }
    }
    int t=d[u];
    s.erase({-dp[t],t});
    dp[t]++;
    s.insert({-dp[t],t});
    ans[u]=s.begin()->second-d[u];
    if(!c){
        for(int i=st[u];i<en[u];i++){
            dp[d[to[i]]]=0;
        }
        s.clear();
    }
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n-1;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    timer=1;
    dfs(1,0);
    dfs_hld(1,0,1);
    for(int i=1;i<=n;i++) printf("%d \n",*(ans+i));
}
