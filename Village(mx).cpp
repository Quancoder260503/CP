#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int mod=1e9+7;
int p,n,ans_mx,ans_mn,timer,c;
ll ans;
int trs[sz];
vector<int>adj[sz];
bool vis[sz];
int cnt[sz];
int d[sz];
int up[17][sz];
int st[sz],en[sz];
int to[sz];
int oc[sz];
int ord[sz];
vector<int>dp;
int dfs(int u, int p) {
  to[timer++]=u;
  trs[u]=1;
  for(auto v : adj[u]) if(v != p) {
        d[v]=d[up[0][v]=u]+1;
        trs[u]+=dfs(v,u);
    }
    return trs[u];
}
int jump(int x, int d){
    for(int i=0;i<=16;i++){
        if((d>>i)&1) x=up[i][x];
    } return x ;
}
int lca(int  a, int  b){
    if(d[a]<d[b]) swap(a,b);
    a=jump(a,d[a]-d[b]);
    if(a==b) return a;
    for(int i=16;i>=0;i--){
         int tA=up[i][a]; 
         int tB=up[i][b];
         if(tA!=tB) {a=tA; b=tB;}
    } return up[0][a];
} 
int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    timer=0;
    dfs(1,0);
    for(int i=1;i<=16;i++){
        for(int j=1;j<=n;j++) up[i][j]=up[i-1][up[i-1][j]];
    }
    for(int i=0;i<n;i++){
        int u=to[i];
        int v=to[(i+n/2)%n];
        //cout<<u<<' '<<v<<endl;
        ans+=d[u]+d[v]-2*d[lca(u,v)];
        ord[v]=u;
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++) cout<<ord[i]<<' ';
}
