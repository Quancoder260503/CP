#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e5+7;
ll n,q,l,r,m,cnt;
ll timer=1;
int dp[sz];
int up[19][sz];
int val[19][sz];
int par[sz];
int tree[sz<<2];
/// vital experience when tackling problems: 
/// if meet tle with correct algorithm:
//// try increasing the size if the technical limitation is large
//// avoid using too many functinon
int find(int x){
    if(x==par[x]) return x;
    else return par[x]=find(par[x]);
}
vector<array<int,2>>adj[sz];
void dfs(int u){
    for(int i=1;i<19;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v[0]==up[0][u]) continue;
        val[0][v[0]]=v[1];
        dp[v[0]]=dp[up[0][v[0]]=u]+1;
        dfs(v[0]);
    }
}
array<int,2>jump(int x,int d){
    int dis=0;
    for(int i=0;i<19;i++){
        if((d>>i)&1){
            dis=max(dis,val[i][x]);
            x=up[i][x];
        }
    }
    return {x,dis};
}
int lca(int a, int b){
    if(dp[a]<dp[b]) swap(a,b);
    array<int,2>t=jump(a,dp[a]-dp[b]);
    if(t[0]==b) return t[1];
    a=t[0];
    int dis=t[1];
    for(int i=18;i>=0;i--){
         int tA=up[i][a]; int tB=up[i][b];
         if(tA!=tB) {
             dis=max(dis,val[i][a]);
             dis=max(dis,val[i][b]);
             a=tA; b=tB;
         }
    } dis=max(dis,val[0][a]);
      dis=max(dis,val[0][b]);
      //cout<<a<<" "<<b<<" "<<dis<<endl;
      return dis;
}  
void update(int val,int L,int R,int l=1,int r=n,int p=1){
    if(L>r or R<l) return;
    if(l==r){
        tree[p]=val;
        return;
    }
    int mid=(l+r)>>1;
    update(val,L,R,l,mid,2*p);
    update(val,L,R,mid+1,r,2*p+1);
    tree[p]=max(tree[2*p],tree[2*p+1]);
}
int query(int L,int R,int l=1,int r=n,int p=1){
    if(L>r or R<l) return 0;
    if(L<=l and r<=R) return tree[p];
    int mid=(l+r)>>1;
    return max(query(L,R,l,mid,2*p),query(L,R,mid+1,r,2*p+1));
}
void gogo(){
     cin>>n>>m>>q;
     for(int i=1;i<=n;i++) par[i]=i;
     for(int i=1;i<=n;i++){
         adj[i].clear(); 
         up[0][i]=val[0][i]=0;
     }
     cnt=0;
     for(int i=1;i<=m;i++){
         if(cnt==n) break;
         int u,v;cin>>u>>v;
         int uroot=find(u); int vroot=find(v);
         if(uroot==vroot) continue;
         par[vroot]=uroot;
         cnt++;
         adj[u].push_back({v,i});
         adj[v].push_back({u,i});
     }
     dfs(1);
     for(int i=1;i<17;i++){
         for(int j=1;j<=n;j++) val[i][j]=max(val[i-1][j],val[i-1][up[i-1][j]]);
     }
     for(int i=1;i<n;i++){
         int dis=lca(i,i+1);
        // cout<<dis<<endl;
         update(dis,i,i);
     }
     for(int i=1;i<=q;i++){
         int u,v;cin>>u>>v;
         if(u==v){
             cout<<0<<" ";
             continue;
         }
         int res=query(u,v-1);
         cout<<res<<" ";
     }
     cout<<endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t ;cin>>t;
    while(t--){
         gogo();
    }
}