#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
ll a[sz];
ll start[sz];
ll en[sz];
vector<ll>adj[sz];
ll n,q;
ll timer=0;
void dfs(int u,int p){
    start[u]=timer++;
    for (auto v:adj[u]){
        if (v==p) continue;
        dfs(v,u);
    }en[u]=timer-1;
}
template<class T> struct Seg{
    const T ID=0;
    int n;vector<T>seg;
    T comp(T a,T b){ return a+b;}
    void init(ll p){n=p;seg.assign(2*n,ID);}
    void pull(ll p){seg[p]=comp(seg[2*p],seg[2*p+1]);}
    void upd(ll p,ll val){
        seg[p+=n]=val;
        for (p/=2;p;p/=2){
            pull(p);
        }
    } T query(ll l,ll r){
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
    for (int i=1;i<=n;i++){
        cin>>a[i];
    } for (int i=1;i<=n-1;i++){
        ll u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    } dfs(1,0);
      st.init(n);
      for (int i=1;i<=n;i++){
          st.upd(start[i],a[i]);
      }     
      for (int i=1;i<=q;i++){
          int t;cin>>t;
          if (t==1){
              ll s,x;cin>>s>>x;
              st.upd(start[s],x);
          } else {
              ll s;cin>>s;
              cout <<st.query(start[s],en[s])<<endl;
          }
      }
}