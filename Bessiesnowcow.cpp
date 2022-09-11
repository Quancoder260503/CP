#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
const int mod=998244353;
int n,x,k,i,q,j,w,m;
int st[sz],en[sz];
int timer=1;
vector<ll>adj[sz];
map<ll,ll>col[sz];
struct node{
    ll val;
    ll subval;
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
void update(ll x,int L,int R,int l=1,int r=n,int p=1){
    if(L>r or R<l) return;
    if(L<=l and r<=R){
        tree[p].val+=x;
        tree[p].subval+=(r-l+1)*x;
        return;
    }
    int mid=(l+r)>>1;
   // push_down(p);
    update(x,L,R,l,mid,2*p);
    update(x,L,R,mid+1,r,2*p+1);
    tree[p].subval=tree[2*p].subval+tree[2*p+1].subval+tree[p].val*(r-l+1);
}
ll query(int L,int R,int l=1,int r=n,int p=1){
    if(L>r or R<l) return 0 ;
    if(L<=l and r<=R) return tree[p].subval;
    int mid=(l+r)>>1;
   // push_down(p);
    return query(L,R,l,mid,2*p)+query(L,R,mid+1,r,2*p+1)+tree[p].val*(min(R,r)-max(L,l)+1);
}
int main(){
     cin>>n>>q;
     for(i=0;i<n-1;i++){
         ll u,v;cin>>u>>v;
         adj[u].push_back(v);
         adj[v].push_back(u);
     }
    dfs(1,0);
    for(int i=0;i<q;i++){
        int t;cin>>t;
        if(t==2){
            int x;cin>>x;
            ll res=query(st[x],en[x]);
            cout<<res<<endl;
        } else{
            int u,v;cin>>u>>v;
            auto it=col[v].upper_bound(st[u]);
            if(it!=col[v].begin() and en[prev(it)->second]>=en[u]) continue;
            while (it!=col[v].end() and en[it->second]<=en[u]){
                    update(-1,st[it->second],en[it->second]);
                    col[v].erase(it++);
                }
                col[v][st[u]]=u;
                update(1,st[u],en[u]);
        }
    }
}