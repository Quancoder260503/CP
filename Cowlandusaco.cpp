#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int trsz=8e5+1;
ll a[sz];
ll start[sz];
ll tin[sz];
ll en[sz];
ll euler_tour[sz];
ll segtree[trsz];
vector<ll>adj[sz];
ll n,q;
ll timer=0;
ll timer1=0;
void dfs(int u,int p){
    start[u]=timer1++;
    tin[u]=timer;
    euler_tour[timer++]=u;
    for (auto v:adj[u]){
        if (v==p) continue;
        dfs(v,u);
        euler_tour[timer++]=u;
    }
    en[u]=timer1-1;
}
int mn_tin(int x, int y) {
	if (x == -1) return y;
	if (y == -1) return x;
	return (tin[x] < tin[y] ? x : y);
}
void build(int node = 1, int l = 0, int r = timer - 1) {
	if (l == r) segtree[node] = euler_tour[l];
	else {
		int mid = (l + r) / 2;
		build(node * 2, l, mid);
		build(node * 2 + 1, mid + 1, r);
		segtree[node] = mn_tin(segtree[node * 2], segtree[node * 2 + 1]);
	}
}
int query1(int a, int b, int node = 1, int l = 0, int r = timer - 1) {
	if (l > b || r < a) return -1;
	if (l >= a && r <= b) return segtree[node];
	int mid = (l + r) / 2;
	return mn_tin(query1(a, b, node * 2, l, mid), query1(a, b, node * 2 + 1, mid + 1, r));
}
int lca(int a, int b) {
	if (tin[a] > tin[b]) swap(a, b);
	return query1(tin[a], tin[b]);
}
template<class T> struct Seg{
    const T ID=0;
    int n;vector<T>seg;
    T comp(T a,T b){ return a^b;}
    void init(ll p){n=p;seg.assign(2*n,ID);}
    void pull(ll p){seg[p]=comp(seg[2*p],seg[2*p+1]);}
    void upd(ll p,ll val){
        seg[p+=n]^=val;
        for (p/=2;p;p/=2){
            pull(p);
        }
    } T query(int l,int r){
        T ra=ID; T rb=ID;
        for (l+=n,r+=n+1;l<r;l/=2,r/=2){
            if(l&1) ra=comp(ra,seg[l++]);
            if(r&1) rb=comp(rb,seg[--r]);
        } return comp(ra,rb);
    }
};
Seg<ll>st;
int main(){
    cin>>n>>q;
    for  (int i=0;i<n;i++){
        cin>>a[i];
    }   for (int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        --u;--v;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }   
     dfs(0,-1);
     build();
     st.init(n+1);
     for (int i=0;i<n;i++){
         st.upd(start[i],a[i]);
         st.upd(en[i]+1,a[i]);
    }
    for (int i=1;i<=q;i++){
         int t,u,v;
         cin>>t>>u>>v;
         --u;
         if (t==1){
             st.upd(start[u],v);
             st.upd(en[u]+1,v);
             a[u]=v;
         }else {
             --v;
             ll k=lca(u,v);
             ll x=st.query(0,start[u])^a[k]^st.query(0,start[v]);
             cout <<x<<endl;
         }
     }
}