#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=1e5+1;
ll timer=1;
int n,q,m;
ll up[19][sz];
ll dp[sz];
ll a[sz];
int st[sz]; int en[sz];
vector<ll>adj[sz];
ll tree[sz<<2];
ll lzadd[sz<<2];
const int mod=1e9+7;
ll jump(int x,int d){
    for(int i=0;i<=18;i++){
        if((d>>i)&1) x=up[i][x];
    } return x;
}
void dfs(int u){
     st[u]=timer++;
     for(int i=1;i<=18;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v==up[0][u]) continue;
        dp[v]=dp[up[0][v]=u]+1;
        dfs(v);
    } 
    en[u]=timer-1;
}
ll lca(ll a, ll b){
    if(dp[a]<dp[b]) swap(a,b);
    a=jump(a,dp[a]-dp[b]);
    if (a==b) return a;
    for(int i=18;i>=0;i--){
         int tA=up[i][a]; int tB=up[i][b];
         if(tA!=tB) a=tA,b=tB;
    } return up[0][a];
}   
void push_down(int p,int l,int mid,int r){
    if(lzadd[p]!=0){
        lzadd[2*p]+=lzadd[p]; lzadd[2*p+1]+=lzadd[p];
        tree[2*p]+=(ll) lzadd[p]*(mid-l+1); 
        tree[2*p+1]+=(ll) lzadd[p]*(r-mid);
        lzadd[p]=0;
    }
}
void update(ll val,int L,int R,int l=1,int r=n,int p=1){
    if(L>r or R<l) return;
    if(L<=l and r<=R){
        tree[p]+=(ll) val*(r-l+1);
        lzadd[p]+=val;
        return;
    }
    int mid=(l+r)>>1;
    push_down(p,l,mid,r);
    update(val,L,R,l,mid,2*p);
    update(val,L,R,mid+1,r,2*p+1);
    tree[p]=tree[2*p]+tree[2*p+1];
}
ll query(int L,int R,int l=1,int r=n,int p=1){
    if(L>r or R<l) return 0;
    if(L<=l and r<=R) return tree[p];
    int mid=(l+r)>>1;
    push_down(p,l,mid,r);
    return query(L,R,l,mid,2*p)+query(L,R,mid+1,r,2*p+1);
}
int main(){   
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=0;i<n-1;i++){
        ll u,v;cin>>u>>v;
        adj[v].push_back(u);
        adj[u].push_back(v);
    } dfs(1);
      for(int i=1;i<=n;i++) update(a[i],st[i],st[i]);
      int root=1;
      for(int i=1;i<=q;i++){
          int t;cin>>t;
          if(t==1){ int v;cin>>v;root=v;}
          else if(t==2){
                int u,v;ll x; cin>>v>>u>>x;
                int sub=0; int ori=0;
                  if(st[root]<=st[u] and en[u]<=en[root]) sub++;
                  if(st[root]<=st[v] and en[v]<=en[root]) sub++;
                  if(sub==2) ori=lca(u,v);
                  else if(sub==1) ori=root;
                  else{
                     int uanc=lca(u,root);int vanc=lca(v,root);int anc=lca(u,v);
                     if(dp[uanc]>=dp[vanc]) ori=uanc;
                     else ori=vanc;
                     if(dp[ori]<dp[anc]) ori=anc;
                 }
                 if(ori==root) update(x,st[1],en[1]);
                 else if(st[root]<st[ori] and en[ori]<=en[root]) update(x,st[ori],en[ori]);
                 else if(st[ori]<st[root] and en[root]<=en[ori]){
                     update(x,st[1],en[1]);
                     ll p=jump(root,dp[root]-dp[ori]-1);
                     update(-x,st[p],en[p]);
                 }
                 else update(x,st[ori],en[ori]);
             }
          else if(t==3){
                int u;cin>>u; ll res=0;
                int anc=lca(u,root);
                if(anc!=u) res=query(st[u],en[u]);
                else{
                  ll p=jump(root,dp[root]-dp[u]-1);
                  ll subr=query(st[1],en[1]);
                  ll subl=query(st[p],en[p]);
                  res=subr-subl;
                }
                cout<<res<<endl;
          }
      }
}  