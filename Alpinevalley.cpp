#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=1e5+1;
ll timer=1;
int n,q,m,e,s;
bool shop[sz];
ll up[17][sz];
ll ds[sz];
ll dp[17][sz];ll d[sz];
ll cnt[sz];
array<ll,2>edge[sz];
vector<array<ll,2>>adj[sz];
const int mod=1e9+7;
ll jump(int x,int d){
    for(int i=0;i<=16;i++){
        if((d>>i)&1) x=up[i][x];
    } return x;
}
void dfs(int u){
     for(int i=1;i<=16;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v[0]==up[0][u]) continue;
        d[v[0]]=d[up[0][v[0]]=u]+1;
        ds[v[0]]=ds[u]+v[1];
        dfs(v[0]);
    } 
}
ll lca(ll a, ll b){
    if(d[a]<d[b]) swap(a,b);
    a=jump(a,d[a]-d[b]);
    if (a==b) return a;
    for(int i=16;i>=0;i--){
         int tA=up[i][a]; int tB=up[i][b];
         if(tA!=tB) a=tA,b=tB;
    } return up[0][a];
}
void dfs1(int u){
    if (shop[u]) dp[0][u]=ds[u];
    else dp[0][u]=1e17;
    for(auto v:adj[u]){
         if(v[0]==up[0][u]) continue;
         dfs1(v[0]); 
         dp[0][u]=min(dp[0][u],dp[0][v[0]]);
    } 
}
void push(){
    for(int i=1;i<=16;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=1e17;
        }
    }
    for(int i=1;i<=16;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=min(dp[i-1][j],dp[i-1][up[i-1][j]]);
        }
    }
}
ll minpath(int r,int p){
    ll ans=1e17;
    int u=r;
    for(int i=16;i>=0;i--){
        if(lca(up[i][u],p)==p){
            ans=min(ans,dp[i][u]);
            u=up[i][u];
        }
    } ans=min(ans,dp[0][p]);
      return ans;
}
int main(){
    cin>>n>>s>>q>>e;
    for(int i=1;i<=n-1;i++){
        ll u,v,w;cin>>u>>v>>w;
        edge[i][0]=u;edge[i][1]=v;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    } for(int i=0;i<s;i++){
        ll x;cin>>x;
        shop[x]=1;
    } 
    dfs(e);
    dfs1(e);
    for(int i=1;i<=n;i++) dp[0][i]=dp[0][i]-2*ds[i];
    push();
    ll inf=1e15;
    for(int i=0;i<q;i++){
        int l,f;cin>>l>>f;
        ll u,v; u=edge[l][0]; v=edge[l][1];
        if(d[u]>d[v]) swap(u,v);
        if(lca(v,f)!=v) cout<<"escaped"<<endl;
        else{
           ll res=minpath(f,v);
           if(res>=inf) cout<<"oo"<<endl;
           else cout<<res+ds[f]<<endl;
        }
    }
}