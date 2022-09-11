#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=4e5+1;
ll n,q;
ll timer=1;
vector<ll>adj[sz];
ll col[sz];
ll st[sz],en[sz];
struct node{
    ll val;
    ll lzadd;
    node(){};
} tree[sz<<2];
void dfs(int u,int p){
    st[u]=timer++;
    for(auto v:adj[u]){
        if(v==p) continue;
        dfs(v,u);
    }
    en[u]=timer-1;
}
void push_down(int p){
    if(tree[p].lzadd!=0){
        tree[2*p].lzadd=tree[2*p+1].lzadd=tree[p].lzadd;
        tree[2*p].val=tree[2*p+1].val=tree[p].lzadd;
        tree[p].lzadd=0;
    }
}
void update(ll c,int L,int R,int l=1,int r=n,int p=1){
    if(l>R or r<L) return;
    if(L<=l and r<=R){
        tree[p].val=c;
        tree[p].lzadd=c;
        return;
    }
    int mid=(l+r)>>1;
    push_down(p);
    update(c,L,R,l,mid,2*p);
    update(c,L,R,mid+1,r,2*p+1);
    tree[p].val=(tree[2*p+1].val|tree[2*p].val);
}
ll query(int L,int R,int l=1,int r=n,int p=1){
    if(l>R or r<L) return 0;
    if(L<=l and r<=R) return tree[p].val;
    int mid=(l+r)>>1;
    push_down(p);
    return (query(L,R,l,mid,2*p)|query(L,R,mid+1,r,2*p+1));
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){cin>>col[i];col[i]--;}
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++) update((ll) 1<<col[i],st[i],st[i]);
    for(int i=1;i<=q;i++){
        int t;cin>>t;
        if(t==1){
            int v,c;cin>>v>>c;
            c--;
            update((ll) 1<<c,st[v],en[v]);
        }
        else{
            int u;cin>>u;
            ll res=query(st[u],en[u]);
            int t=__builtin_popcountll(res);
            cout<<t<<endl;
        }
    }
}