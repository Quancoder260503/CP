#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+5;
ll n,k,m,q;
int timer=1;
int trs[sz],dp[sz];
ll tour[sz];
int st[sz],a[sz],en[sz];
array<ll,3> edge[sz<<1];
ll dp1[sz];
vector<array<ll,2>>adj[sz];
ll ds[sz];
const int mod=998244353;
struct node{
    ll lzadd;
    ll val;
    ll rootval;
    node(){};
} tree[sz<<2];
void build(int l=1,int r=n,int p=1){
    if(l==r){
        tree[p].val=dp1[tour[l]];
        tree[p].rootval=dp1[tour[l]]+a[tour[l]];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,2*p);
    build(mid+1,r,2*p+1);
    tree[p].val=min(tree[2*p+1].val,tree[2*p].val);
    tree[p].rootval=min(tree[2*p+1].rootval,tree[2*p].rootval);
}
void dfs(int u,int p){
    tour[timer]=u;
    st[u]=timer++;
    for(auto v:adj[u]){
        if(v[0]==p) continue;
        dp[v[0]]=dp[u]+1;
        dp1[v[0]]=dp1[u]+v[1];
        dfs(v[0],u);
    } en[u]=timer-1;
}
void push_down(int p){
    if(tree[p].lzadd!=0){
        tree[2*p].val+=tree[p].lzadd;
        tree[2*p].rootval+=tree[p].lzadd;
        tree[2*p+1].val+=tree[p].lzadd;
        tree[2*p+1].rootval+=tree[p].lzadd;
        tree[2*p].lzadd+=tree[p].lzadd;
        tree[2*p+1].lzadd+=tree[p].lzadd;
        tree[p].lzadd=0;
    }
}
void update(bool act,ll x,int L,int R,int l=1 ,int r=n,int p=1){
    if(l>R or L>r) return;
    if(L<=l and r<=R){
        if(act) tree[p].val+=x;
        tree[p].lzadd+=x;
        tree[p].rootval+=x;
        return;
    } int mid=(l+r)>>1;
      push_down(p);
      update(act,x,L,R,l,mid,2*p);
      update(act,x,L,R,mid+1,r,2*p+1);
      if(act) tree[p].val=min(tree[2*p].val,tree[2*p+1].val);
      tree[p].rootval=min(tree[2*p].rootval,tree[2*p+1].rootval);
}
ll query(int L,int R,int l=1,int r=n,int p=1){
    if(l>R or L>r) return 0 ;
    if(L<=l and r<=R) return tree[p].val;
    int mid=(l+r)>>1;
    push_down(p);
    ll x0=query(L,R,l,mid,2*p)+query(L,R,mid+1,r,2*p+1);
    return x0;
}
ll query1(int L,int R,int l=1,int r=n,int p=1){
    if(l>R or L>r) return LLONG_MAX;
    if(L<=l and r<=R) return tree[p].rootval;
    int mid=(l+r)>>1;
    push_down(p);
    ll x0=query1(L,R,l,mid,2*p);
    ll x1=query1(L,R,mid+1,r,2*p+1);
    return min(x0,x1);
}
int anc(int x,int y){
    if(dp[x]>dp[y]) swap(x,y);
    if(st[x]<=st[y] and en[x]>=en[y]) return x;
    else return -1;
}
int main(){
    cin>>n>>q;
    for(int i=1;i<n;i++){
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
        adj[edge[i][0]].push_back({edge[i][1],edge[i][2]});
    }
    dfs(1,0);
    for(int i=n;i<=2*n-2;i++){
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
        a[edge[i][0]]=edge[i][2];
    }
    build();
    for(int i=0;i<q;i++){
        int t;ll u,x,v,res;cin>>t;
        if(t==1){
            cin>>x>>v;
            if(x>=n){
                ll u=edge[x][0];
                ll value=-edge[x][2]+v;
                update(0,value,st[u],st[u]);
                edge[x][2]=v;
            } else{
                ll u=edge[x][1];
                ll value=-edge[x][2]+v;
                update(1,value,st[u],en[u]);
                edge[x][2]=v;
            }
        } else{
               res=0;
               cin>>u>>v;
               int p=anc(u,v);
               ll res=-query(st[u],st[u])+query(st[v],st[v]);
               if(u!=p) res+=query1(st[u],en[u]);  
               cout<<res<<endl;
        }
    } 
}
 