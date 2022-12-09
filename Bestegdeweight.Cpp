#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=4e5+1;
const int sz1=1e6+1;
const int inf=1e7+5;
int n,m;
vector<array<ll,4>>edge;
vector<array<ll,4>>redge;
vector<array<ll,4>>oedge;
vector<array<ll,2>>adj[sz];
ll dp[18][sz];
ll up[18][sz];
ll d[sz];
int par[sz];
int co[sz];
ll ans[sz1];
ll bit[sz];
int find(int u){
    if(u==par[u]) return u;
    else return find(par[u]);
}
void unite(int u,int v){
    u=find(u); v=find(v);
    if(co[u]>co[v]) swap(u,v);
    co[v]+=co[u];
    par[u]=v;
}
array<ll,2>jump_mx(int x,int d){
    ll mx=0;
    for(int i=0;i<18;i++){
        if(d&(1<<i)){
            mx=max(dp[i][x],mx);
            x=up[i][x];
        }
    }
    return {x,mx};
}
array<ll,2>jump_mn(int x,int d){
    ll mn=1e9 + 10;
    for(int i=17;i>=0;i--){
        if(d&(1<<i)){
            mn=min(dp[i][x],mn);
            x=up[i][x];
        }
    }
    return {x,mn};
}
void dfs(int u){
    for(int i=1;i<18;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v[0]==up[0][u]) continue;
        dp[0][v[0]]=v[1];
        d[v[0]]=d[up[0][v[0]]=u]+1;
        dfs(v[0]);
    }
}
ll lca_mx(int  a, int b){
    if(d[a]<d[b]) swap(a,b);
    array<ll,2>x=jump_mx(a,d[a]-d[b]);
    if(x[0]==b) return x[1];
    a=x[0];
    ll mx=x[1];
    for(int i=17;i>=0;i--){
         int tA=up[i][a]; int tB=up[i][b];
         if(tA!=tB) {
             mx=max(mx,dp[i][a]);
             mx=max(mx,dp[i][b]);
             a=tA; b=tB;
         }
    }
    mx=max(mx,dp[0][a]);
    mx=max(mx,dp[0][b]);
    return mx;
} 
ll lca_mn(int  a, int b){
    if(d[a]<d[b]) swap(a,b);
    array<ll,2>x=jump_mn(a,d[a]-d[b]);
    if(x[0]==b) return x[1];
    ll mn=x[1];
    a=x[0];
    for(int i=17;i>=0;i--){
         int tA=up[i][a]; int tB=up[i][b];
         if(tA!=tB) {
             mn=min(mn,dp[i][a]);
             mn=min(mn,dp[i][b]);
             a=tA; b=tB;
         }
    }
    mn=min(mn,dp[0][a]);
    mn=min(mn,dp[0][b]);
    return mn;
} 
int lca(int a,int b){
     if(d[a]<d[b]) swap(a,b);
     int ds=d[a]-d[b];
     for(int i=0;i<=17;i++){
         if(ds&(1<<i)) a=up[i][a];
     }
     if(a==b) return a;
     for(int i=17;i>=0;i--){
          int ta=up[i][a];
          int tb=up[i][b];
          if(ta!=tb){
              a=ta; 
              b=tb;
          }
     }
     return up[0][a];
}
void push(){
    for(int i=1;i<=17;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=max(dp[i-1][up[i-1][j]],dp[i-1][j]);
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        par[i]=i;
        co[i]=1;
    }
    for(int i=1;i<=m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        edge.push_back({w,u,v,i});
    } 
    sort(edge.begin(),edge.end());
    for(auto e:edge){
        if(find(e[1])==find(e[2])){
            redge.push_back({e[1],e[2],e[0],e[3]});
            continue;
        }
        unite(e[1],e[2]);
        adj[e[1]].push_back({e[2],e[0]});
        adj[e[2]].push_back({e[1],e[0]});
        oedge.push_back({e[1],e[2],e[0],e[3]});
    }
    dfs(1);
    push();
    for(auto e:redge){
      ans[e[3]]=lca_mx(e[1],e[0]);
    }
    for(int i=0;i<=17;i++){
        for(int j=0;j<=n;j++) dp[i][j]=1e9 + 100;
    }
    for(auto e:redge){
        int anc=lca(e[0],e[1]);
        int ds=d[e[0]]-d[anc];
        int dy=d[e[1]]-d[anc];
        int u=e[0]; int v=e[1];
        for(int i=17;i>=0;i--){
             if(ds&(1<<i)){
                  dp[i][u]=min(dp[i][u],e[2]);
                  u=up[i][u];
             }
        }
        for(int i=17;i>=0;i--){
             if(dy&(1<<i)){
                  dp[i][v]=min(dp[i][v],e[2]);
                  v=up[i][v];
             }    
        }
    }
    for(int i=17;i>0;i--){
        for(int j=1;j<=n;j++){
            dp[i-1][j]=min(dp[i][j],dp[i-1][j]);
            dp[i-1][up[i-1][j]]=min(dp[i-1][up[i-1][j]],dp[i][j]);
        }
    }
    for(auto e:oedge) ans[e[3]]=lca_mn(e[1],e[0]);
    for(int i = 1; i <= m; i++){
          if(ans[i] <= 1e9) cout<<ans[i] - 1<<' ';
          else cout<<-1<<' ';
    }
}
