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
int en[sz],st[sz];
vector<int>adj[sz];
ll dp[sz];
int up[17][sz];
int treemx[sz<<2];
int mxnode[sz<<2];
int mnnode[sz<<2];
int treemn[sz<<2];
void dfs(int u){
    st[u]=timer++;
    for (int i=1;i<=16;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v==up[0][u]) continue;
        dp[v]=dp[up[0][v]=u]+1;
        dfs(v);
    }
    en[u]=timer-1;
}
int jump(int x,int d){
    for(int i=0;i<=16;i++){
        if((d>>i)&1) x=up[i][x];
    }
    return x;
}
int lca(int x,int y){
    if(dp[x]<dp[y]) swap(x,y);
    x=jump(x,dp[x]-dp[y]);
    if(x==y) return x;
    for(int i=16;i>=0;i--){
        int tx=up[i][x];int ty=up[i][y];
        if(tx!=ty) x=tx,y=ty;
    }
    return up[0][x];
}
void build(int l=1,int r=n,int p=1){
    if(l==r){
        treemn[p]=treemx[p]=st[l];
        mnnode[p]=l; mxnode[p]=r;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,2*p);
    build(mid+1,r,2*p+1);
    treemn[p]=min(treemn[2*p],treemn[2*p+1]);
    treemx[p]=max(treemx[2*p],treemx[2*p+1]);
    if(treemn[2*p]>treemn[2*p+1]) mnnode[p]=mnnode[2*p+1];
    else mnnode[p]=mnnode[2*p];
    if(treemx[2*p]>treemx[2*p+1]) mxnode[p]=mxnode[2*p];
    else mxnode[p]=mxnode[2*p+1];
}
array<int,2>querymx(int L,int R,int l=1,int r=n,int p=1){
    if(L>r or R<l) return {0,0};
    if(L<=l and r<=R) return {treemx[p],mxnode[p]};
    int mid=(l+r)>>1;
    array<int,2>left=querymx(L,R,l,mid,2*p);
    array<int,2>right=querymx(L,R,mid+1,r,2*p+1);
    if(left[0]>right[0]) return left;
    else return right;
}
array<int,2> querymn(int L,int R,int l=1,int r=n,int p=1){
    if(L>r or R<l) return {INT_MAX,0};
    if(L<=l and r<=R) return {treemn[p],mnnode[p]};
    int mid=(l+r)>>1;
    array<int,2>left=querymn(L,R,l,mid,2*p);
    array<int,2>right=querymn(L,R,mid+1,r,2*p+1);
    if(left[0]<right[0]) return left;
    else return right;
}
int main(){
   cin>>n>>q;
   for(int i=2;i<=n;i++){
        int x; cin>>x;
        adj[x].push_back(i);
   }
    dfs(1);
    build();
    for (int i=1;i<=q;i++){
        int u,v;cin>>u>>v;
        array<int,2>x=querymx(u,v);
        array<int,2>y=querymn(u,v);
        int ancl,ancr,anc1,anc2;
        array<int,2>xleft=querymx(u,x[1]-1); array<int,2>yleft=querymn(u,x[1]-1);
        ancl=lca(xleft[1],yleft[1]);
        array<int,2>xright=querymx(x[1]+1,v); array<int,2>yright=querymn(x[1]+1,v);
        ancr=lca(xright[1],yright[1]);
        if(x[1]!=u and x[1]!=v) anc1=lca(ancr,ancl);
        else if(x[1]==u) anc1=ancr;
        else if(x[1]==v) anc1=ancl;
        xleft=querymx(u,y[1]-1);yleft=querymn(u,y[1]-1);
        ancl=lca(xleft[1],yleft[1]);
        xright=querymx(y[1]+1,v); yright=querymn(y[1]+1,v);
        ancr=lca(xright[1],yright[1]);
        if(y[1]!=u and y[1]!=v) anc2=lca(ancr,ancl);
        else if(y[1]==u) anc2=ancr;
        else if(y[1]==v) anc2=ancl;
        if(dp[anc1]<dp[anc2]) cout<<y[1]<<" "<<dp[anc2]<<endl;
        else cout<<x[1]<<" "<<dp[anc1]<<endl;
    }
}